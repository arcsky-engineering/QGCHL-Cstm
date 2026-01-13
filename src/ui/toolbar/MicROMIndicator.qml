/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts  1.11

import QGroundControl                       1.0
import QGroundControl.Controls              1.0
import QGroundControl.MultiVehicleManager   1.0
import QGroundControl.ScreenTools           1.0
import QGroundControl.Palette               1.0

Item {
    id:             _root
    width:          micromIcon.width + statusColumn.width + ScreenTools.defaultFontPixelWidth
    anchors.top:    parent.top
    anchors.bottom: parent.bottom

    property bool   showIndicator:      true
    property var    _micromController:  QGroundControl.micromController
    property var    margins:            ScreenTools.defaultFontPixelWidth
    property var    panelRadius:        ScreenTools.defaultFontPixelWidth * 0.5

    // Popup control panel
    Component {
        id: micromControlsPopup

        Rectangle {
            width:          mainLayout.width + mainLayout.anchors.margins * 2
            height:         mainLayout.height + mainLayout.anchors.margins * 2
            color:          qgcPal.window
            radius:         panelRadius

            ColumnLayout {
                id:                 mainLayout
                anchors.margins:    ScreenTools.defaultFontPixelWidth
                anchors.top:        parent.top
                anchors.left:       parent.left
                spacing:            ScreenTools.defaultFontPixelHeight * 0.5

                // Title
                QGCLabel {
                    text:               qsTr("MicROM UV Camera")
                    font.pointSize:     ScreenTools.mediumFontPointSize
                    font.weight:        Font.Bold
                    Layout.alignment:   Qt.AlignHCenter
                }

                // Connection status
                Row {
                    spacing: ScreenTools.defaultFontPixelWidth * 0.5
                    Layout.alignment: Qt.AlignHCenter

                    Rectangle {
                        width:  ScreenTools.defaultFontPixelHeight * 0.8
                        height: width
                        radius: width / 2
                        color:  _micromController && _micromController.connected ? "green" : "red"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    QGCLabel {
                        text: _micromController && _micromController.connected ? qsTr("Connected") : qsTr("Disconnected")
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                // Separator
                Rectangle {
                    Layout.fillWidth:       true
                    Layout.preferredHeight: 1
                    color:                  qgcPal.windowShade
                }

                // Photo/Video buttons
                RowLayout {
                    spacing:            ScreenTools.defaultFontPixelWidth
                    Layout.alignment:   Qt.AlignHCenter

                    QGCButton {
                        text:               qsTr("Photo")
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 10
                        onClicked: {
                            if (_micromController) {
                                _micromController.takePhoto()
                            }
                        }
                    }

                    QGCButton {
                        text:               _micromController && _micromController.recording ? qsTr("Stop Video") : qsTr("Record Video")
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 12
                        highlighted:        _micromController && _micromController.recording
                        onClicked: {
                            if (_micromController) {
                                _micromController.toggleVideo()
                            }
                        }
                    }
                }

                // Separator
                Rectangle {
                    Layout.fillWidth:       true
                    Layout.preferredHeight: 1
                    color:                  qgcPal.windowShade
                }

                // Zoom control
                RowLayout {
                    spacing: ScreenTools.defaultFontPixelWidth
                    Layout.fillWidth: true

                    QGCLabel {
                        text:                   qsTr("Zoom:")
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 8
                    }

                    Slider {
                        id:                     zoomSlider
                        from:                   0
                        to:                     15
                        stepSize:               1
                        value:                  _micromController ? _micromController.zoom : 0
                        Layout.fillWidth:       true
                        onPressedChanged: {
                            if (!pressed && _micromController) {
                                _micromController.setZoom(value)
                            }
                        }
                    }

                    QGCLabel {
                        text:                   zoomSlider.value.toFixed(0)
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 3
                        horizontalAlignment:    Text.AlignRight
                    }
                }

                // Gain/Sensitivity control
                RowLayout {
                    spacing: ScreenTools.defaultFontPixelWidth
                    Layout.fillWidth: true

                    QGCLabel {
                        text:                   qsTr("Gain:")
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 8
                    }

                    Slider {
                        id:                     gainSlider
                        from:                   0
                        to:                     255
                        stepSize:               1
                        value:                  _micromController ? _micromController.gain : 130
                        Layout.fillWidth:       true
                        onPressedChanged: {
                            if (!pressed && _micromController) {
                                _micromController.setGain(value)
                            }
                        }
                    }

                    QGCLabel {
                        text:                   gainSlider.value.toFixed(0)
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 4
                        horizontalAlignment:    Text.AlignRight
                    }
                }

                // Info text
                QGCLabel {
                    text:               qsTr("Higher gain = more UV sensitivity")
                    font.pointSize:     ScreenTools.smallFontPointSize
                    Layout.alignment:   Qt.AlignHCenter
                    opacity:            0.7
                }
            }
        }
    }

    // Toolbar icon
    QGCColoredImage {
        id:                     micromIcon
        width:                  height
        anchors.top:            parent.top
        anchors.bottom:         parent.bottom
        source:                 "/qmlimages/CameraComponentIcon.svg"
        fillMode:               Image.PreserveAspectFit
        sourceSize.height:      height
        color:                  qgcPal.buttonText

        // Recording indicator dot
        Rectangle {
            visible:        _micromController && _micromController.recording
            width:          parent.width * 0.35
            height:         width
            radius:         width / 2
            color:          "red"
            anchors.top:    parent.top
            anchors.right:  parent.right
            anchors.margins: 2

            SequentialAnimation on opacity {
                running:    _micromController && _micromController.recording
                loops:      Animation.Infinite
                NumberAnimation { to: 0.3; duration: 500 }
                NumberAnimation { to: 1.0; duration: 500 }
            }
        }
    }

    // Status column
    Column {
        id:                     statusColumn
        anchors.left:           micromIcon.right
        anchors.leftMargin:     ScreenTools.defaultFontPixelWidth * 0.5
        anchors.verticalCenter: parent.verticalCenter
        spacing:                0

        QGCLabel {
            text:           qsTr("MicROM")
            font.pointSize: ScreenTools.smallFontPointSize
        }

        QGCLabel {
            text:           _micromController && _micromController.connected ?
                                qsTr("Z:%1 G:%2").arg(_micromController.zoom).arg(_micromController.gain) :
                                qsTr("--")
            font.pointSize: ScreenTools.smallFontPointSize
            opacity:        0.8
        }
    }

    // Click handler
    MouseArea {
        anchors.fill: parent
        onClicked: {
            mainWindow.showIndicatorPopup(_root, micromControlsPopup, false)
        }
    }
}
