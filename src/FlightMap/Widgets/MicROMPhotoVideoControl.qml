/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

/// @file MicROMPhotoVideoControl.qml
/// @brief Fly view capture controls for the OFIL micROM UV camera.
///
/// Loaded by PhotoVideoControl in place of the stock layout whenever the micROM
/// is both the selected video source and answering keepalives. Photo and video
/// both go to the camera's own SD card; QGC's local stream recording is not
/// offered here, since one shutter that could mean either destination is worse
/// than no shutter at all.
///
/// Settings live in a fly-out to the left so the panel stays small enough to
/// keep working over a live feed.

import QtQuick          2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts  1.11

import QGroundControl                   1.0
import QGroundControl.Controls          1.0
import QGroundControl.ScreenTools       1.0
import QGroundControl.Palette           1.0

Item {
    id:             _root
    implicitWidth:  mainColumn.implicitWidth
    implicitHeight: mainColumn.implicitHeight

    property var  _micromController:  QGroundControl.micromController
    property bool _connected:         _micromController && _micromController.connected
    property bool _recording:         _micromController && _micromController.recording
    property bool _sdCardPresent:     _micromController && _micromController.sdCardPresent
    property bool _canShoot:          _connected && _sdCardPresent

    property real _buttonSize:        ScreenTools.defaultFontPixelWidth * 6
    property bool _flyoutOpen:        false

    /// True while the fly-out is on screen, including its fade out. The host
    /// widget lifts its z above the instrument panel for exactly this long;
    /// keying that off _flyoutOpen instead would drop z the instant the toggle
    /// flipped and the fading panel would snap behind the gauges.
    property alias flyoutVisible:     flyout.visible

    // Elapsed recording time. The camera reports that it is recording but not
    // for how long, so we count locally from the moment it confirms the start.
    property int  _recordSeconds:     0

    QGCPalette { id: qgcPal; colorGroupEnabled: enabled }

    function _twoDigits(n) {
        return (n < 10 ? "0" : "") + n
    }

    function _elapsedString() {
        return _twoDigits(Math.floor(_recordSeconds / 60)) + ":" + _twoDigits(_recordSeconds % 60)
    }

    Timer {
        interval:           1000
        repeat:             true
        running:            _root._recording
        onRunningChanged:   if (running) _root._recordSeconds = 0
        onTriggered:        _root._recordSeconds++
    }

    ColumnLayout {
        id:         mainColumn
        anchors.horizontalCenter: parent.horizontalCenter
        spacing:    ScreenTools.defaultFontPixelHeight * 0.4

        // Status line: link state, SD card warning, settings fly-out toggle
        RowLayout {
            Layout.alignment:   Qt.AlignHCenter
            spacing:            ScreenTools.defaultFontPixelWidth * 0.75

            Rectangle {
                width:              ScreenTools.defaultFontPixelHeight * 0.5
                height:             width
                radius:             width / 2
                color:              _connected ? qgcPal.colorGreen : qgcPal.colorRed
                Layout.alignment:   Qt.AlignVCenter
            }

            QGCLabel {
                text:               qsTr("micROM")
                font.pointSize:     ScreenTools.smallFontPointSize
                Layout.alignment:   Qt.AlignVCenter
            }

            QGCLabel {
                text:               qsTr("NO SD")
                font.pointSize:     ScreenTools.smallFontPointSize
                color:              qgcPal.colorOrange
                visible:            _connected && !_sdCardPresent
                Layout.alignment:   Qt.AlignVCenter
            }

            QGCColoredImage {
                source:             "/res/gear-black.svg"
                mipmap:             true
                height:             ScreenTools.defaultFontPixelHeight * 3
                width:              height
                sourceSize.height:  height
                fillMode:           Image.PreserveAspectFit
                color:              _flyoutOpen ? qgcPal.colorGreen : qgcPal.text
                // Dimmed rather than hidden when there is no link: the settings
                // it opens can't be sent, and a control that looks live but
                // silently does nothing is worse than one that looks disabled.
                opacity:            _connected ? 1 : 0.4
                Layout.alignment:   Qt.AlignVCenter

                QGCMouseArea {
                    fillItem:   parent
                    enabled:    _connected
                    onClicked:  _flyoutOpen = !_flyoutOpen
                }
            }
        }

        // Elapsed recording time. Kept in the layout at all times so the panel
        // doesn't jump under the operator's thumb when recording starts.
        QGCLabel {
            Layout.alignment:   Qt.AlignHCenter
            text:               _elapsedString()
            font.pointSize:     ScreenTools.mediumFontPointSize
            color:              _recording ? qgcPal.colorRed : qgcPal.text
            opacity:            _recording ? 1 : 0.5
        }

        // Photo and record, side by side. Two buttons rather than a mode toggle
        // plus one shutter: the camera has no notion of a current mode, and in
        // flight a wrong-mode tap costs the shot.
        RowLayout {
            Layout.alignment:   Qt.AlignHCenter
            spacing:            ScreenTools.defaultFontPixelWidth * 2

            // Take photo
            Rectangle {
                width:          _buttonSize
                height:         width
                radius:         width / 2
                color:          "transparent"
                border.color:   qgcPal.buttonText
                border.width:   3

                Rectangle {
                    anchors.centerIn:   parent
                    width:              parent.width * 0.75
                    height:             width
                    radius:             width / 2
                    color:              _canShoot ? qgcPal.buttonText : qgcPal.colorGrey

                    QGCColoredImage {
                        anchors.centerIn:   parent
                        height:             parent.height * 0.55
                        width:              height
                        sourceSize.height:  height
                        source:             "/qmlimages/camera_photo.svg"
                        fillMode:           Image.PreserveAspectFit
                        color:              qgcPal.button
                    }
                }

                // Brief flash to confirm the camera acknowledged the shot
                Rectangle {
                    id:                 photoFlash
                    anchors.fill:       parent
                    radius:             width / 2
                    color:              "white"
                    opacity:            0

                    NumberAnimation {
                        id:         photoFlashAnimation
                        target:     photoFlash
                        property:   "opacity"
                        from:       0.8
                        to:         0
                        duration:   350
                    }
                }

                MouseArea {
                    anchors.fill:   parent
                    enabled:        _canShoot
                    onClicked:      _micromController.takePhoto()
                }
            }

            // Start/stop recording
            Rectangle {
                width:          _buttonSize
                height:         width
                radius:         width / 2
                color:          "transparent"
                border.color:   qgcPal.buttonText
                border.width:   3

                Rectangle {
                    anchors.centerIn:   parent
                    width:              parent.width * (_recording ? 0.5 : 0.75)
                    height:             width
                    radius:             _recording ? 0 : width * 0.5
                    color:              _canShoot ? qgcPal.colorRed : qgcPal.colorGrey

                    SequentialAnimation on opacity {
                        running:    _root._recording
                        loops:      Animation.Infinite
                        NumberAnimation { to: 0.4; duration: 500 }
                        NumberAnimation { to: 1.0; duration: 500 }
                    }
                }

                MouseArea {
                    anchors.fill:   parent
                    enabled:        _canShoot
                    onClicked: {
                        if (_recording) {
                            _micromController.stopVideo()
                        } else {
                            _micromController.startVideo()
                        }
                    }
                }
            }
        }

        // Last error from the camera, e.g. a rejected command
        QGCLabel {
            Layout.alignment:       Qt.AlignHCenter
            Layout.maximumWidth:    ScreenTools.defaultFontPixelWidth * 22
            text:                   _micromController ? _micromController.lastError : ""
            color:                  qgcPal.colorRed
            font.pointSize:         ScreenTools.smallFontPointSize
            wrapMode:               Text.WordWrap
            horizontalAlignment:    Text.AlignHCenter
            visible:                text !== ""
        }
    }

    Connections {
        target:         _micromController
        onPhotoTaken:   photoFlashAnimation.restart()
    }

    // Settings fly-out. Opens upward rather than to the left, for two reasons.
    // In bottomMode the telemetry values bar runs along the bottom strip, which
    // is where a leftward fly-out lands. And it is declared after this widget in
    // FlyViewWidgetLayer, so at equal z it paints on top and the fly-out
    // disappears behind it on compressed layouts like the Herelink.
    //
    // Upward, the only neighbour is the instrument panel, which is declared
    // before this widget and so is painted over correctly without touching z.
    Rectangle {
        id:                     flyout
        anchors.bottom:         parent.top
        anchors.bottomMargin:   ScreenTools.defaultFontPixelWidth
        anchors.right:          parent.right
        width:                  flyoutColumn.implicitWidth + (ScreenTools.defaultFontPixelWidth * 2)
        height:                 flyoutColumn.implicitHeight + (ScreenTools.defaultFontPixelWidth * 2)
        radius:                 ScreenTools.defaultFontPixelHeight / 2
        color:                  Qt.rgba(qgcPal.window.r, qgcPal.window.g, qgcPal.window.b, 0.75)
        border.color:           Qt.rgba(qgcPal.text.r, qgcPal.text.g, qgcPal.text.b, 0.25)
        border.width:           1
        // Settings stay reachable without an SD card, but not without a link
        opacity:                (_flyoutOpen && _connected) ? 1 : 0
        visible:                opacity > 0
        enabled:                _flyoutOpen && _connected

        Behavior on opacity { NumberAnimation { duration: 150 } }

        // Slide up from behind the widget as it fades in
        transform: Translate {
            y: _flyoutOpen ? 0 : ScreenTools.defaultFontPixelHeight * 2
            Behavior on y { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }
        }

        ColumnLayout {
            id:                 flyoutColumn
            anchors.centerIn:   parent
            spacing:            ScreenTools.defaultFontPixelHeight * 0.5

            property real sliderWidth: ScreenTools.defaultFontPixelWidth * 24

            property var uvColors:     ["#FF0000", "#FF8000", "#FFFF00", "#00FF00",
                                        "#00FFFF", "#0080FF", "#8000FF", "#FF00FF"]
            property var uvColorNames: [qsTr("Red"),        qsTr("Orange"), qsTr("Yellow"), qsTr("Green"),
                                        qsTr("Light Blue"), qsTr("Blue"),   qsTr("Purple"), qsTr("Pink")]

            MicROMSlider {
                Layout.fillWidth:   true
                enabled:            _connected
                sliderWidth:        flyoutColumn.sliderWidth
                label:              qsTr("Zoom")
                from:               0
                to:                 13
                value:              _micromController ? _micromController.zoom : 0
                valueText:          liveValue.toFixed(0) + " / 13"
                onValueSet:         _micromController.setZoom(newValue)
            }

            MicROMSlider {
                Layout.fillWidth:   true
                enabled:            _connected
                sliderWidth:        flyoutColumn.sliderWidth
                label:              qsTr("Gain")
                from:               0
                to:                 255
                value:              _micromController ? _micromController.gain : 130
                valueText:          liveValue.toFixed(0) + " / 255"
                // No hint here, unlike the toolbar popup. Opening upward from a
                // widget already at the bottom of a short screen makes height
                // the scarce dimension, and this is not the place to read prose.
                onValueSet:         _micromController.setGain(newValue)
            }

            MicROMSlider {
                Layout.fillWidth:   true
                enabled:            _connected
                sliderWidth:        flyoutColumn.sliderWidth
                label:              qsTr("UV Colour")
                from:               0
                to:                 7
                trackColors:        flyoutColumn.uvColors
                value:              _micromController ? _micromController.uvColor : 0
                valueText:          flyoutColumn.uvColorNames[liveValue] || ""
                onValueSet:         _micromController.setUVColor(newValue)
            }
        }
    }
}
