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

    property bool   showIndicator:      QGroundControl.settingsManager.appSettings.showMicROMIndicator.rawValue
    property var    _micromController:  QGroundControl.micromController
    property var    margins:            ScreenTools.defaultFontPixelWidth
    property var    panelRadius:        ScreenTools.defaultFontPixelWidth * 0.5
    property real   _sliderWidth:       ScreenTools.defaultFontPixelWidth * 30  // 2x larger sliders

    // Popup control panel
    Component {
        id: micromControlsPopup

        Rectangle {
            id:             popupRect
            // Width covers content + Flickable side margins (1.5 * fontWidth each)
            // + a buffer for the vertical scrollbar.
            width:          mainLayout.width + ScreenTools.defaultFontPixelWidth * 6
            // Cap height to 85% of window so we stay on-screen; Flickable below
            // handles scrolling when content is taller.
            height:         Math.min(mainLayout.height + ScreenTools.defaultFontPixelWidth * 3,
                                     mainWindow.height * 0.85)
            color:          qgcPal.window
            radius:         panelRadius

            Flickable {
                id:                 popupFlick
                anchors.fill:       parent
                anchors.margins:    ScreenTools.defaultFontPixelWidth * 1.5
                contentWidth:       mainLayout.width
                contentHeight:      mainLayout.height
                clip:               true
                boundsBehavior:     Flickable.StopAtBounds
                flickableDirection: Flickable.VerticalFlick

                ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }

            ColumnLayout {
                id:                 mainLayout
                spacing:            ScreenTools.defaultFontPixelHeight * 0.75

                // Title
                QGCLabel {
                    text:               qsTr("micROM UV Camera")
                    font.pointSize:     ScreenTools.mediumFontPointSize
                    font.weight:        Font.Bold
                    Layout.alignment:   Qt.AlignHCenter
                }

                // Connection and SD card status
                Row {
                    spacing: ScreenTools.defaultFontPixelWidth * 1.5
                    Layout.alignment: Qt.AlignHCenter

                    // Connection status
                    Row {
                        spacing: ScreenTools.defaultFontPixelWidth * 0.5

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

                    // SD Card status
                    Row {
                        spacing: ScreenTools.defaultFontPixelWidth * 0.5
                        visible: _micromController && _micromController.connected

                        Rectangle {
                            width:  ScreenTools.defaultFontPixelHeight * 0.8
                            height: width
                            radius: width / 2
                            color:  _micromController && _micromController.sdCardPresent ? "green" : "orange"
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        QGCLabel {
                            text: _micromController && _micromController.sdCardPresent ? qsTr("SD Card OK") : qsTr("No SD Card")
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }

                // Error message display
                QGCLabel {
                    text:               _micromController ? _micromController.lastError : ""
                    color:              "red"
                    font.pointSize:     ScreenTools.smallFontPointSize
                    Layout.alignment:   Qt.AlignHCenter
                    visible:            _micromController && _micromController.lastError !== ""
                }

                // Separator
                Rectangle {
                    Layout.fillWidth:       true
                    Layout.preferredHeight: 1
                    color:                  qgcPal.windowShade
                }

                // Photo/Video buttons
                RowLayout {
                    spacing:            ScreenTools.defaultFontPixelWidth * 2
                    Layout.alignment:   Qt.AlignHCenter

                    QGCButton {
                        // Shows the lockout countdown in place of the label, so a
                        // dead button explains itself instead of looking broken
                        text:               _micromController && !_micromController.commandReady ?
                                                qsTr("Wait %1s").arg(_micromController.cooldownRemaining) :
                                                qsTr("Take Photo")
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 14
                        Layout.preferredHeight: ScreenTools.defaultFontPixelHeight * 2.5
                        enabled:            _micromController && _micromController.connected && _micromController.commandReady
                        onClicked: {
                            if (_micromController) {
                                _micromController.takePhoto()
                            }
                        }
                    }

                    QGCButton {
                        text:               _micromController && !_micromController.commandReady ?
                                                qsTr("Wait %1s").arg(_micromController.cooldownRemaining) :
                                                (_micromController && _micromController.recording ? qsTr("Stop Recording") : qsTr("Start Recording"))
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 16
                        Layout.preferredHeight: ScreenTools.defaultFontPixelHeight * 2.5
                        highlighted:        _micromController && _micromController.recording
                        enabled:            _micromController && _micromController.connected && _micromController.commandReady
                        onClicked: {
                            if (_micromController) {
                                if (_micromController.recording) {
                                    _micromController.stopVideo()
                                } else {
                                    _micromController.startVideo()
                                }
                            }
                        }

                        // Recording indicator
                        Rectangle {
                            visible:        _micromController && _micromController.recording
                            width:          ScreenTools.defaultFontPixelHeight * 0.6
                            height:         width
                            radius:         width / 2
                            color:          "red"
                            anchors.left:   parent.left
                            anchors.leftMargin: ScreenTools.defaultFontPixelWidth
                            anchors.verticalCenter: parent.verticalCenter

                            SequentialAnimation on opacity {
                                running:    _micromController && _micromController.recording
                                loops:      Animation.Infinite
                                NumberAnimation { to: 0.3; duration: 500 }
                                NumberAnimation { to: 1.0; duration: 500 }
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
                MicROMSlider {
                    Layout.fillWidth:   true
                    enabled:            _micromController && _micromController.connected
                    sliderWidth:        _sliderWidth
                    label:              qsTr("Zoom:")
                    from:               0
                    to:                 13
                    value:              _micromController ? _micromController.zoom : 0
                    valueText:          liveValue.toFixed(0) + " / 13"
                    onValueSet:         _micromController.setZoom(newValue)
                }

                // Gain/Sensitivity control
                MicROMSlider {
                    Layout.fillWidth:   true
                    enabled:            _micromController && _micromController.connected
                    sliderWidth:        _sliderWidth
                    label:              qsTr("Gain (Sensitivity):")
                    from:               0
                    to:                 255
                    value:              _micromController ? _micromController.gain : 130
                    valueText:          liveValue.toFixed(0) + " / 255"
                    hint:               qsTr("Higher gain = more UV sensitivity")
                    onValueSet:         _micromController.setGain(newValue)
                }

                // Separator
                Rectangle {
                    Layout.fillWidth:       true
                    Layout.preferredHeight: 1
                    color:                  qgcPal.windowShade
                }

                // UV Color Palette control
                MicROMSlider {
                    Layout.fillWidth:   true
                    enabled:            _micromController && _micromController.connected
                    sliderWidth:        _sliderWidth
                    label:              qsTr("UV Color:")
                    from:               0
                    to:                 7
                    trackColors:        uvColors
                    value:              _micromController ? _micromController.uvColor : 0
                    valueText:          uvColorNames[liveValue] || ""
                    hint:               qsTr("Color of UV detection overlay")
                    onValueSet:         _micromController.setUVColor(newValue)

                    property var uvColors:     ["#FF0000", "#FF8000", "#FFFF00", "#00FF00",
                                                "#00FFFF", "#0080FF", "#8000FF", "#FF00FF"]
                    property var uvColorNames: [qsTr("Red"),        qsTr("Orange"), qsTr("Yellow"), qsTr("Green"),
                                                qsTr("Light Blue"), qsTr("Blue"),   qsTr("Purple"), qsTr("Pink")]
                }

                // Separator
                Rectangle {
                    Layout.fillWidth:       true
                    Layout.preferredHeight: 1
                    color:                  qgcPal.windowShade
                }

                // RC channel triggers
                ColumnLayout {
                    id:                 rcTriggerLayout
                    Layout.fillWidth:   true
                    spacing:            ScreenTools.defaultFontPixelHeight * 0.25

                    // Channel list: index 0 = Disabled, 1..18 = Channel N
                    property var _channelNames: [
                        qsTr("Disabled"),
                        qsTr("Channel 1"),  qsTr("Channel 2"),  qsTr("Channel 3"),
                        qsTr("Channel 4"),  qsTr("Channel 5"),  qsTr("Channel 6"),
                        qsTr("Channel 7"),  qsTr("Channel 8"),  qsTr("Channel 9"),
                        qsTr("Channel 10"), qsTr("Channel 11"), qsTr("Channel 12"),
                        qsTr("Channel 13"), qsTr("Channel 14"), qsTr("Channel 15"),
                        qsTr("Channel 16"), qsTr("Channel 17"), qsTr("Channel 18")
                    ]

                    QGCLabel {
                        text:               qsTr("RC Channel Triggers")
                        font.weight:        Font.Medium
                        Layout.alignment:   Qt.AlignHCenter
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: ScreenTools.defaultFontPixelWidth

                        QGCLabel {
                            text:                   qsTr("Cam trigger:")
                            Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 14
                        }
                        QGCComboBox {
                            id:                     camTriggerCombo
                            Layout.fillWidth:       true
                            model:                  rcTriggerLayout._channelNames
                            currentIndex:           _micromController ? _micromController.camTriggerChannel : 0
                            onActivated: {
                                if (_micromController) {
                                    _micromController.camTriggerChannel = index
                                }
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: ScreenTools.defaultFontPixelWidth

                        QGCLabel {
                            text:                   qsTr("Video trigger:")
                            Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 14
                        }
                        QGCComboBox {
                            id:                     videoTriggerCombo
                            Layout.fillWidth:       true
                            model:                  rcTriggerLayout._channelNames
                            currentIndex:           _micromController ? _micromController.videoTriggerChannel : 0
                            onActivated: {
                                if (_micromController) {
                                    _micromController.videoTriggerChannel = index
                                }
                            }
                        }
                    }

                }
            }
            } // Flickable
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
            text:           qsTr("micROM")
            font.pointSize: ScreenTools.smallFontPointSize
        }

        QGCLabel {
            text:           _micromController && _micromController.connected ?
                                (_micromController.recording ? qsTr("REC") : qsTr("Z:%1 G:%2").arg(_micromController.zoom).arg(_micromController.gain)) :
                                qsTr("--")
            font.pointSize: ScreenTools.smallFontPointSize
            color:          _micromController && _micromController.recording ? "red" : qgcPal.buttonText
            opacity:        _micromController && _micromController.recording ? 1.0 : 0.8
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
