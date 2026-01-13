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
    _sendCommand("IC_KSP");
}

void MicROMController::toggleVideo()
{
    qDebug() << "MicROMController: Toggling video recording";
    _sendCommand("IC_KSV");
    // Toggle local state immediately for responsive UI
    // Will be corrected by response if needed
    _recording = !_recording;
    emit recordingChanged();
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
    // Query current zoom and gain values
    _sendCommand("IC_MZQ");
    _sendCommand("IC_GAQ");
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

    // Parse gain response: CI_GAR<value> or CI_GAS<value>
    if (response.startsWith("CI_GAR") || response.startsWith("CI_GAS")) {
        bool ok;
        int value = response.mid(6).toInt(&ok);
        if (ok && value >= 0 && value <= 255) {
            _gain = value;
            emit gainChanged();
            qDebug() << "MicROMController: Gain is" << _gain;
        }
        return;
    }

    // Parse zoom response: CI_MZR<value> or CI_MZS<value>
    if (response.startsWith("CI_MZR") || response.startsWith("CI_MZS")) {
        bool ok;
        int value = response.mid(6).toInt(&ok);
        if (ok && value >= 0 && value <= 15) {
            _zoom = value;
            emit zoomChanged();
            qDebug() << "MicROMController: Zoom is" << _zoom;
        }
        return;
    }

    // Parse video/photo responses
    if (response.startsWith("CI_KSV")) {
        // Video state confirmed
        qDebug() << "MicROMController: Video command acknowledged";
        return;
    }

    if (response.startsWith("CI_KSP")) {
        // Photo confirmed
        qDebug() << "MicROMController: Photo command acknowledged";
        return;
    }

    qDebug() << "MicROMController: Unknown response:" << response;
}
