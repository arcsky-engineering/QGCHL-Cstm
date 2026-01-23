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
            width:          mainLayout.width + mainLayout.anchors.margins * 2
            height:         mainLayout.height + mainLayout.anchors.margins * 2
            color:          qgcPal.window
            radius:         panelRadius

            ColumnLayout {
                id:                 mainLayout
                anchors.margins:    ScreenTools.defaultFontPixelWidth * 1.5
                anchors.top:        parent.top
                anchors.left:       parent.left
                spacing:            ScreenTools.defaultFontPixelHeight * 0.75

                // Title
                QGCLabel {
                    text:               qsTr("MicROM UV Camera")
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
                        text:               qsTr("Take Photo")
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 14
                        Layout.preferredHeight: ScreenTools.defaultFontPixelHeight * 2.5
                        enabled:            _micromController && _micromController.connected
                        onClicked: {
                            if (_micromController) {
                                _micromController.takePhoto()
                            }
                        }
                    }

                    QGCButton {
                        text:               _micromController && _micromController.recording ? qsTr("Stop Recording") : qsTr("Start Recording")
                        Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 16
                        Layout.preferredHeight: ScreenTools.defaultFontPixelHeight * 2.5
                        highlighted:        _micromController && _micromController.recording
                        enabled:            _micromController && _micromController.connected
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
                ColumnLayout {
                    spacing: ScreenTools.defaultFontPixelHeight * 0.25
                    Layout.fillWidth: true

                    RowLayout {
                        spacing: ScreenTools.defaultFontPixelWidth
                        Layout.fillWidth: true

                        QGCLabel {
                            text:                   qsTr("Zoom:")
                            Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 8
                        }

                        QGCLabel {
                            text:                   zoomSlider.value.toFixed(0) + " / 13"
                            Layout.fillWidth:       true
                            horizontalAlignment:    Text.AlignRight
                        }
                    }

                    Slider {
                        id:                     zoomSlider
                        from:                   0
                        to:                     13
                        stepSize:               1
                        value:                  _micromController ? _micromController.zoom : 0
                        Layout.preferredWidth:  _sliderWidth
                        Layout.preferredHeight: ScreenTools.defaultFontPixelHeight * 2
                        enabled:                _micromController && _micromController.connected

                        background: Rectangle {
                            x:              zoomSlider.leftPadding
                            y:              zoomSlider.topPadding + zoomSlider.availableHeight / 2 - height / 2
                            width:          zoomSlider.availableWidth
                            height:         ScreenTools.defaultFontPixelHeight * 0.5
                            radius:         height / 2
                            color:          qgcPal.windowShade

                            Rectangle {
                                width:  zoomSlider.visualPosition * parent.width
                                height: parent.height
                                color:  qgcPal.buttonHighlight
                                radius: height / 2
                            }
                        }

                        handle: Rectangle {
                            x:              zoomSlider.leftPadding + zoomSlider.visualPosition * (zoomSlider.availableWidth - width)
                            y:              zoomSlider.topPadding + zoomSlider.availableHeight / 2 - height / 2
                            width:          ScreenTools.defaultFontPixelHeight * 1.5
                            height:         width
                            radius:         width / 2
                            color:          zoomSlider.pressed ? qgcPal.buttonHighlight : qgcPal.button
                            border.color:   qgcPal.buttonText
                            border.width:   1
                        }

                        onPressedChanged: {
                            if (!pressed && _micromController) {
                                _micromController.setZoom(value)
                            }
                        }
                    }
                }

                // Gain/Sensitivity control
                ColumnLayout {
                    spacing: ScreenTools.defaultFontPixelHeight * 0.25
                    Layout.fillWidth: true

                    RowLayout {
                        spacing: ScreenTools.defaultFontPixelWidth
                        Layout.fillWidth: true

                        QGCLabel {
                            text:                   qsTr("Gain (Sensitivity):")
                            Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 16
                        }

                        QGCLabel {
                            text:                   gainSlider.value.toFixed(0) + " / 255"
                            Layout.fillWidth:       true
                            horizontalAlignment:    Text.AlignRight
                        }
                    }

                    Slider {
                        id:                     gainSlider
                        from:                   0
                        to:                     255
                        stepSize:               1
                        value:                  _micromController ? _micromController.gain : 130
                        Layout.preferredWidth:  _sliderWidth
                        Layout.preferredHeight: ScreenTools.defaultFontPixelHeight * 2
                        enabled:                _micromController && _micromController.connected

                        background: Rectangle {
                            x:              gainSlider.leftPadding
                            y:              gainSlider.topPadding + gainSlider.availableHeight / 2 - height / 2
                            width:          gainSlider.availableWidth
                            height:         ScreenTools.defaultFontPixelHeight * 0.5
                            radius:         height / 2
                            color:          qgcPal.windowShade

                            Rectangle {
                                width:  gainSlider.visualPosition * parent.width
                                height: parent.height
                                color:  qgcPal.buttonHighlight
                                radius: height / 2
                            }
                        }

                        handle: Rectangle {
                            x:              gainSlider.leftPadding + gainSlider.visualPosition * (gainSlider.availableWidth - width)
                            y:              gainSlider.topPadding + gainSlider.availableHeight / 2 - height / 2
                            width:          ScreenTools.defaultFontPixelHeight * 1.5
                            height:         width
                            radius:         width / 2
                            color:          gainSlider.pressed ? qgcPal.buttonHighlight : qgcPal.button
                            border.color:   qgcPal.buttonText
                            border.width:   1
                        }

                        onPressedChanged: {
                            if (!pressed && _micromController) {
                                _micromController.setGain(value)
                            }
                        }
                    }

                    QGCLabel {
                        text:               qsTr("Higher gain = more UV sensitivity")
                        font.pointSize:     ScreenTools.smallFontPointSize
                        Layout.alignment:   Qt.AlignHCenter
                        opacity:            0.7
                    }
                }

                // Separator
                Rectangle {
                    Layout.fillWidth:       true
                    Layout.preferredHeight: 1
                    color:                  qgcPal.windowShade
                }

                // UV Color Palette control
                ColumnLayout {
                    spacing: ScreenTools.defaultFontPixelHeight * 0.25
                    Layout.fillWidth: true

                    // Color palette property to map values 0-7 to colors
                    property var uvColors: ["#FF0000", "#FF8000", "#FFFF00", "#00FF00", "#00FFFF", "#0080FF", "#8000FF", "#FF00FF"]
                    property var uvColorNames: ["Red", "Orange", "Yellow", "Green", "Light Blue", "Blue", "Purple", "Pink"]

                    QGCLabel {
                        text:               qsTr("UV Color Palette")
                        font.pointSize:     ScreenTools.defaultFontPointSize
                        font.weight:        Font.Medium
                    }

                    // Color preview boxes
                    Row {
                        spacing: ScreenTools.defaultFontPixelWidth * 0.3
                        Layout.alignment: Qt.AlignHCenter

                        Repeater {
                            model: 8
                            Rectangle {
                                width:          ScreenTools.defaultFontPixelWidth * 3.5
                                height:         ScreenTools.defaultFontPixelHeight * 1.2
                                color:          parent.parent.parent.uvColors[index]
                                opacity:        uvColorSlider.value === index ? 1.0 : 0.4
                                border.width:   uvColorSlider.value === index ? 2 : 0
                                border.color:   qgcPal.buttonText
                                radius:         2

                                // Checkered pattern for transparency preview
                                Canvas {
                                    anchors.fill: parent
                                    visible: transparencyToggle.checked
                                    onPaint: {
                                        var ctx = getContext("2d")
                                        ctx.fillStyle = "#808080"
                                        var size = 4
                                        for (var x = 0; x < width; x += size * 2) {
                                            for (var y = 0; y < height; y += size * 2) {
                                                ctx.fillRect(x, y, size, size)
                                                ctx.fillRect(x + size, y + size, size, size)
                                            }
                                        }
                                    }
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        uvColorSlider.value = index
                                        if (_micromController) {
                                            var colorValue = index + (transparencyToggle.checked ? 8 : 0)
                                            _micromController.setUVColor(colorValue)
                                        }
                                    }
                                }
                            }
                        }
                    }

                    RowLayout {
                        spacing: ScreenTools.defaultFontPixelWidth
                        Layout.fillWidth: true

                        QGCLabel {
                            text:                   qsTr("Color:")
                            Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 6
                        }

                        QGCLabel {
                            property int colorIndex: _micromController ? (_micromController.uvColor % 8) : 0
                            text:                   parent.parent.parent.uvColorNames[colorIndex]
                            Layout.fillWidth:       true
                            horizontalAlignment:    Text.AlignRight
                        }
                    }

                    Slider {
                        id:                     uvColorSlider
                        from:                   0
                        to:                     7
                        stepSize:               1
                        value:                  _micromController ? (_micromController.uvColor % 8) : 0
                        Layout.preferredWidth:  _sliderWidth
                        Layout.preferredHeight: ScreenTools.defaultFontPixelHeight * 2
                        enabled:                _micromController && _micromController.connected

                        background: Rectangle {
                            x:              uvColorSlider.leftPadding
                            y:              uvColorSlider.topPadding + uvColorSlider.availableHeight / 2 - height / 2
                            width:          uvColorSlider.availableWidth
                            height:         ScreenTools.defaultFontPixelHeight * 0.5
                            radius:         height / 2

                            // Rainbow gradient for color slider background
                            gradient: Gradient {
                                orientation: Gradient.Horizontal
                                GradientStop { position: 0.000; color: "#FF0000" }
                                GradientStop { position: 0.143; color: "#FF8000" }
                                GradientStop { position: 0.286; color: "#FFFF00" }
                                GradientStop { position: 0.429; color: "#00FF00" }
                                GradientStop { position: 0.571; color: "#00FFFF" }
                                GradientStop { position: 0.714; color: "#0080FF" }
                                GradientStop { position: 0.857; color: "#8000FF" }
                                GradientStop { position: 1.000; color: "#FF00FF" }
                            }
                        }

                        handle: Rectangle {
                            x:              uvColorSlider.leftPadding + uvColorSlider.visualPosition * (uvColorSlider.availableWidth - width)
                            y:              uvColorSlider.topPadding + uvColorSlider.availableHeight / 2 - height / 2
                            width:          ScreenTools.defaultFontPixelHeight * 1.5
                            height:         width
                            radius:         width / 2
                            color:          uvColorSlider.pressed ? qgcPal.buttonHighlight : qgcPal.button
                            border.color:   qgcPal.buttonText
                            border.width:   1
                        }

                        onPressedChanged: {
                            if (!pressed && _micromController) {
                                var colorValue = value + (transparencyToggle.checked ? 8 : 0)
                                _micromController.setUVColor(colorValue)
                            }
                        }
                    }

                    // Transparency toggle
                    RowLayout {
                        spacing: ScreenTools.defaultFontPixelWidth
                        Layout.fillWidth: true

                        QGCCheckBox {
                            id:         transparencyToggle
                            text:       qsTr("Transparent overlay")
                            checked:    _micromController ? (_micromController.uvColor >= 8) : false
                            enabled:    _micromController && _micromController.connected
                            onClicked: {
                                if (_micromController) {
                                    var colorValue = uvColorSlider.value + (checked ? 8 : 0)
                                    _micromController.setUVColor(colorValue)
                                }
                            }
                        }
                    }

                    QGCLabel {
                        text:               qsTr("Color of UV detection overlay")
                        font.pointSize:     ScreenTools.smallFontPointSize
                        Layout.alignment:   Qt.AlignHCenter
                        opacity:            0.7
                    }
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
