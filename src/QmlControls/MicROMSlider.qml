/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

/// @file MicROMSlider.qml
/// @brief Labelled slider for OFIL micROM camera settings.
///
/// Shared by the toolbar indicator popup and the fly view control widget so the
/// two can't drift apart. The camera is driven over UDP, so the value is only
/// pushed on release rather than on every step while dragging.

import QtQuick          2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts  1.11

import QGroundControl.Controls      1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Palette       1.0

ColumnLayout {
    id:         _root
    spacing:    ScreenTools.defaultFontPixelHeight * 0.25

    property string label:          ""      ///< Left hand caption
    property string valueText:      ""      ///< Right hand readout, e.g. "4 / 13"
    property string hint:           ""      ///< Optional small print below the slider
    property real   from:           0
    property real   to:             100
    property real   stepSize:       1
    property real   value:          0       ///< Current camera value; drives the handle when not dragging
    property real   sliderWidth:    ScreenTools.defaultFontPixelWidth * 30

    /// Live handle position. Tracks the finger during a drag, where `value` still
    /// holds what the camera last reported. Read-outs should bind to this so the
    /// number moves with the handle rather than jumping on release.
    property alias  liveValue:      slider.value

    /// When non-empty the track is drawn as equal segments of these colours
    /// instead of the usual progress fill. Used for the UV palette.
    property var    trackColors:    []

    /// Emitted once, on release, with the settled value.
    signal valueSet(int newValue)

    QGCPalette { id: qgcPal; colorGroupEnabled: enabled }

    RowLayout {
        Layout.fillWidth:   true
        spacing:            ScreenTools.defaultFontPixelWidth

        QGCLabel {
            text:           _root.label
            font.weight:    Font.Medium
        }

        QGCLabel {
            text:                   _root.valueText
            Layout.fillWidth:       true
            horizontalAlignment:    Text.AlignRight
        }
    }

    Slider {
        id:                     slider
        from:                   _root.from
        to:                     _root.to
        stepSize:               _root.stepSize
        Layout.preferredWidth:  _root.sliderWidth
        Layout.preferredHeight: ScreenTools.defaultFontPixelHeight * 2

        // Follow the camera except while the user has hold of the handle.
        // A plain `value:` binding would be destroyed by the first drag, after
        // which the handle would ignore the camera entirely.
        Binding {
            target:     slider
            property:   "value"
            value:      _root.value
            when:       !slider.pressed
        }

        background: Item {
            x:      slider.leftPadding
            y:      slider.topPadding + slider.availableHeight / 2 - height / 2
            width:  slider.availableWidth
            height: ScreenTools.defaultFontPixelHeight * 0.5

            // Standard track: shaded groove with a highlighted fill up to the handle
            Rectangle {
                anchors.fill:   parent
                visible:        _root.trackColors.length === 0
                radius:         height / 2
                color:          qgcPal.windowShade

                Rectangle {
                    width:  slider.visualPosition * parent.width
                    height: parent.height
                    radius: height / 2
                    color:  qgcPal.buttonHighlight
                }
            }

            // Colour strip track, one segment per entry. Rounded ends are faked
            // by squaring off the inner half of the first and last segments,
            // which keeps this working on the Qt 5.11 the Herelink builds use.
            Row {
                anchors.fill:   parent
                visible:        _root.trackColors.length > 0

                Repeater {
                    model: _root.trackColors.length

                    Rectangle {
                        width:  parent.width / _root.trackColors.length
                        height: parent.height
                        color:  _root.trackColors[index]
                        radius: height / 2

                        Rectangle {
                            visible:        index === 0
                            anchors.right:  parent.right
                            width:          parent.width / 2
                            height:         parent.height
                            color:          parent.color
                        }
                        Rectangle {
                            visible:        index === _root.trackColors.length - 1
                            anchors.left:   parent.left
                            width:          parent.width / 2
                            height:         parent.height
                            color:          parent.color
                        }
                    }
                }
            }
        }

        handle: Rectangle {
            x:              slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
            y:              slider.topPadding + slider.availableHeight / 2 - height / 2
            width:          ScreenTools.defaultFontPixelHeight * 1.5
            height:         width
            radius:         width / 2
            color:          slider.pressed ? qgcPal.buttonHighlight : qgcPal.button
            border.color:   qgcPal.buttonText
            border.width:   1
        }

        onPressedChanged: {
            if (!pressed) {
                _root.valueSet(Math.round(value))
            }
        }
    }

    QGCLabel {
        text:               _root.hint
        font.pointSize:     ScreenTools.smallFontPointSize
        Layout.alignment:   Qt.AlignHCenter
        opacity:            0.7
        visible:            _root.hint !== ""
    }
}
