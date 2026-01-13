/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "MicROMController.h"
#include <QDebug>

MicROMController::MicROMController(QObject* parent)
    : QObject(parent)
{
    // Create send socket
    _sendSocket = new QUdpSocket(this);

    // Create receive socket and bind to response port
    _recvSocket = new QUdpSocket(this);
    if (_recvSocket->bind(QHostAddress::Any, _recvPort)) {
        connect(_recvSocket, &QUdpSocket::readyRead, this, &MicROMController::_readPendingDatagrams);
        qDebug() << "MicROMController: Listening on port" << _recvPort;
    } else {
        qWarning() << "MicROMController: Failed to bind to port" << _recvPort;
    }

    // Setup keepalive timer
    _keepaliveTimer = new QTimer(this);
    connect(_keepaliveTimer, &QTimer::timeout, this, &MicROMController::_sendKeepalive);
    _keepaliveTimer->start(KEEPALIVE_INTERVAL_MS);

    // Initial connection attempt
    _sendKeepalive();
}

MicROMController::~MicROMController()
{
    if (_keepaliveTimer) {
        _keepaliveTimer->stop();
    }
}

void MicROMController::setCameraIP(const QString& ip)
{
    if (_cameraIP != ip) {
        _cameraIP = ip;
        emit cameraIPChanged();
        // Reset connection state with new IP
        _connected = false;
        _keepaliveMisses = 0;
        emit connectedChanged();
        _sendKeepalive();
    }
}

void MicROMController::takePhoto()
{
    qDebug() << "MicROMController: Taking photo";
    _setLastError("");
    _sendCommand("IC_KSP");
}

void MicROMController::startVideo()
{
    qDebug() << "MicROMController: Starting video recording";
    _setLastError("");
    _pendingVideoStart = true;
    _pendingVideoStop = false;
    _sendCommand("IC_KSV");
}

void MicROMController::stopVideo()
{
    qDebug() << "MicROMController: Stopping video recording";
    _setLastError("");
    _pendingVideoStop = true;
    _pendingVideoStart = false;
    // Send the same command to toggle off
    _sendCommand("IC_KSV");
}

void MicROMController::setZoom(int value)
{
    if (value < 0) value = 0;
    if (value > 13) value = 13;  // Max zoom is 13 (14-15 don't work on camera)

    qDebug() << "MicROMController: Setting zoom to" << value;
    _sendCommand(QString("IC_MZS%1").arg(value));
    _zoom = value;
    emit zoomChanged();
}

void MicROMController::setGain(int value)
{
    if (value < 0) value = 0;
    if (value > 255) value = 255;

    qDebug() << "MicROMController: Setting gain to" << value;
    _sendCommand(QString("IC_GAS%1").arg(value));
    _gain = value;
    emit gainChanged();
}

void MicROMController::queryStatus()
{
    // Query current zoom, gain, and SD card presence
    // Note: IC_KQV (video status query) is not implemented by camera firmware
    _sendCommand("IC_MZQ");
    _sendCommand("IC_GAQ");
    _sendCommand("IC_SDPQ");  // Query SD card presence
}

void MicROMController::_sendCommand(const QString& command)
{
    QByteArray data = command.toLatin1();
    QHostAddress addr(_cameraIP);

    qint64 sent = _sendSocket->writeDatagram(data, addr, _sendPort);
    if (sent < 0) {
        qWarning() << "MicROMController: Failed to send command:" << command
                   << "Error:" << _sendSocket->errorString();
    } else {
        qDebug() << "MicROMController: Sent" << command << "to" << _cameraIP << ":" << _sendPort;
    }
}

void MicROMController::_sendKeepalive()
{
    _sendCommand("IC_ALVS");
    _keepaliveMisses++;

    if (_keepaliveMisses >= MAX_KEEPALIVE_MISSES && _connected) {
        _connected = false;
        emit connectedChanged();
        qDebug() << "MicROMController: Connection lost (no keepalive response)";
    }
}

void MicROMController::_readPendingDatagrams()
{
    while (_recvSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_recvSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        _recvSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << "MicROMController: Received:" << datagram << "from" << sender.toString();

        _parseResponse(datagram);
    }
}

void MicROMController::_setRecording(bool recording)
{
    if (_recording != recording) {
        _recording = recording;
        emit recordingChanged();
        qDebug() << "MicROMController: Recording state changed to" << _recording;
    }
}

void MicROMController::_setLastError(const QString& error)
{
    if (_lastError != error) {
        _lastError = error;
        emit lastErrorChanged();
        if (!error.isEmpty()) {
            qWarning() << "MicROMController: Error:" << error;
        }
    }
}

void MicROMController::_parseResponse(const QByteArray& data)
{
    QString response = QString::fromLatin1(data).trimmed();

    // Check for keepalive response
    if (response.startsWith("CI_ALVR")) {
        _keepaliveMisses = 0;
        if (!_connected) {
            _connected = true;
            emit connectedChanged();
            qDebug() << "MicROMController: Connected to camera";
            // Query initial status
            queryStatus();
        }
        return;
    }

    // Check for keepalive request from camera (we should respond)
    if (response.startsWith("CI_ALVS")) {
        _sendCommand("IC_ALVR");
        return;
    }

    // Parse gain response: CI_GAR<value> or CI_GAS<value>
    if (response.startsWith("CI_GAR") || response.startsWith("CI_GAS")) {
        bool ok;
        int value = response.mid(6).toInt(&ok);
        if (ok && value >= 0 && value <= 255) {
            if (_gain != value) {
                _gain = value;
                emit gainChanged();
            }
            qDebug() << "MicROMController: Gain is" << _gain;
        }
        return;
    }

    // Parse zoom response: CI_MZR<value> or CI_MZS<value>
    if (response.startsWith("CI_MZR") || response.startsWith("CI_MZS")) {
        bool ok;
        int value = response.mid(6).toInt(&ok);
        if (ok && value >= 0 && value <= 13) {  // Max zoom is 13
            if (_zoom != value) {
                _zoom = value;
                emit zoomChanged();
            }
            qDebug() << "MicROMController: Zoom is" << _zoom;
        }
        return;
    }

    // Parse SD card presence: CI_SDPR<0|1>
    if (response.startsWith("CI_SDPR") || response.startsWith("CI_SDPS")) {
        bool present = response.mid(7).startsWith("1");
        if (_sdCardPresent != present) {
            _sdCardPresent = present;
            emit sdCardPresentChanged();
        }
        qDebug() << "MicROMController: SD card present:" << _sdCardPresent;
        return;
    }

    // Video error response - MUST check before CI_KRV since CI_KRVERR starts with CI_KRV
    if (response.startsWith("CI_KRVERR") || (response.contains("KRV") && response.contains("ERR"))) {
        qDebug() << "MicROMController: Video error received:" << response;

        // Determine what failed based on pending flags
        if (_pendingVideoStart) {
            // Failed to start - recording stays false
            _setLastError("Failed to start video recording - check SD card");
            _setRecording(false);
            qDebug() << "MicROMController: Failed to start recording";
        } else if (_pendingVideoStop) {
            // Failed to stop - recording stays true (camera is still recording!)
            _setLastError("Failed to stop video recording");
            _setRecording(true);
            qDebug() << "MicROMController: Failed to stop recording - camera still recording";
        } else {
            // Unknown context - default to false and show generic error
            _setLastError("Video recording error - check SD card");
            qDebug() << "MicROMController: Video error with no pending context";
        }

        _pendingVideoStart = false;
        _pendingVideoStop = false;
        emit videoError();
        return;
    }

    // Parse video recording status response: CI_KRV (recording) or CI_KRV0/CI_KRV1
    // This is the camera's response to IC_KSV command
    if (response.startsWith("CI_KRV")) {
        QString suffix = response.mid(6);

        // If we have pending flags, use them to determine state (most reliable)
        if (_pendingVideoStart) {
            _setRecording(true);
            _pendingVideoStart = false;
            qDebug() << "MicROMController: Video recording started (pending flag)";
        } else if (_pendingVideoStop) {
            _setRecording(false);
            _pendingVideoStop = false;
            qDebug() << "MicROMController: Video recording stopped (pending flag)";
        } else if (suffix == "1" || suffix.startsWith("1")) {
            // Explicit "recording" indicator from camera
            _setRecording(true);
            qDebug() << "MicROMController: Video recording status from camera: recording";
        } else if (suffix == "0" || suffix.startsWith("0")) {
            // Explicit "not recording" indicator from camera
            _setRecording(false);
            qDebug() << "MicROMController: Video recording status from camera: stopped";
        } else {
            // Bare CI_KRV with no suffix and no pending flag - log but don't change state
            qDebug() << "MicROMController: CI_KRV received with no context, current state:" << _recording;
        }
        return;
    }

    // Video command acknowledged (CI_KSV) - also use pending flags
    if (response.startsWith("CI_KSV")) {
        qDebug() << "MicROMController: Video command acknowledged (CI_KSV)";
        if (_pendingVideoStart) {
            _setRecording(true);
            _pendingVideoStart = false;
            qDebug() << "MicROMController: Video recording started";
        } else if (_pendingVideoStop) {
            _setRecording(false);
            _pendingVideoStop = false;
            qDebug() << "MicROMController: Video recording stopped";
        }
        return;
    }

    // Photo command acknowledged
    if (response.startsWith("CI_KSP") || response.startsWith("CI_KRP")) {
        qDebug() << "MicROMController: Photo command acknowledged";
        emit photoTaken();
        return;
    }

    // Photo error response
    if (response.contains("KSPERR") || (response.contains("KSP") && response.contains("ERR"))) {
        _setLastError("Photo capture error - check SD card");
        emit photoError();
        return;
    }

    // SD card space query response: CI_QMSDS<value> or CI_QMSD<value>
    if (response.startsWith("CI_QMSD")) {
        // This is SD card used space info - we can parse it but mainly just acknowledge it
        qDebug() << "MicROMController: SD card space info:" << response.mid(7);
        return;
    }

    // Video status query response: CI_KQV or similar
    if (response.startsWith("CI_KQV") || response.startsWith("CI_KQ")) {
        QString suffix = response.mid(6);
        // Try to determine recording state from response
        if (suffix.contains("V") || suffix == "1") {
            _setRecording(true);
        } else if (suffix == "0" || suffix.isEmpty()) {
            _setRecording(false);
        }
        return;
    }

    // Handle generic error responses (but ignore "Not implemented" as it's not actionable)
    if (response.contains("ERR") && !response.contains("Not implemented")) {
        _setLastError(QString("Camera error: %1").arg(response));
        return;
    }

    // Log unknown responses but don't spam for known periodic messages
    if (!response.isEmpty()) {
        qDebug() << "MicROMController: Unhandled response:" << response;
    }
}
