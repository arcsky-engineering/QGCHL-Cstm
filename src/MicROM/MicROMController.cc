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

    // Setup status query timer - periodically query recording status
    _statusQueryTimer = new QTimer(this);
    connect(_statusQueryTimer, &QTimer::timeout, this, &MicROMController::_queryRecordingStatus);
    _statusQueryTimer->start(STATUS_QUERY_INTERVAL_MS);

    // Initial connection attempt
    _sendKeepalive();
}

MicROMController::~MicROMController()
{
    if (_keepaliveTimer) {
        _keepaliveTimer->stop();
    }
    if (_statusQueryTimer) {
        _statusQueryTimer->stop();
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
    _sendCommand("IC_KSV");
}

void MicROMController::stopVideo()
{
    qDebug() << "MicROMController: Stopping video recording";
    _setLastError("");
    // Send the same command to toggle off
    _sendCommand("IC_KSV");
}

void MicROMController::setZoom(int value)
{
    if (value < 0) value = 0;
    if (value > 15) value = 15;

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
    // Query current zoom, gain, SD card presence, and video status
    _sendCommand("IC_MZQ");
    _sendCommand("IC_GAQ");
    _sendCommand("IC_SDPQ");  // Query SD card presence
    _sendCommand("IC_KQV");   // Query video recording status (K command with Q suffix)
}

void MicROMController::_queryRecordingStatus()
{
    if (_connected) {
        // Periodically query video status to keep our state in sync
        _sendCommand("IC_KQV");
    }
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
        if (ok && value >= 0 && value <= 15) {
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

    // Parse video recording status response: CI_KRV (recording) or CI_KRV0/CI_KRV1
    // Based on the protocol, V = video, and the response tells us the state
    if (response.startsWith("CI_KRV")) {
        // CI_KRV with no suffix or CI_KRV1 = recording, CI_KRV0 = not recording
        QString suffix = response.mid(6);
        if (suffix.isEmpty() || suffix == "1" || suffix.startsWith("1")) {
            _setRecording(true);
        } else if (suffix == "0" || suffix.startsWith("0")) {
            _setRecording(false);
        }
        qDebug() << "MicROMController: Video recording status:" << _recording;
        return;
    }

    // Video command acknowledged (start recording)
    if (response.startsWith("CI_KSV")) {
        qDebug() << "MicROMController: Video command acknowledged";
        // Query status to confirm the actual state
        _sendCommand("IC_KQV");
        return;
    }

    // Video error response
    if (response.contains("KRVERR") || (response.contains("KRV") && response.contains("ERR"))) {
        _setLastError("Video recording error - check SD card");
        _setRecording(false);
        emit videoError();
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

    // Handle generic error responses
    if (response.contains("ERR")) {
        _setLastError(QString("Camera error: %1").arg(response));
        return;
    }

    // Log unknown responses but don't spam for known periodic messages
    if (!response.isEmpty()) {
        qDebug() << "MicROMController: Unhandled response:" << response;
    }
}
