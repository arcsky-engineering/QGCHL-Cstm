import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtQuick.Controls.Styles  1.4

import QGroundControl.Palette       1.0
import QGroundControl.ScreenTools   1.0

CheckBox {
    property color  textColor:          _qgcPal.text
    property bool   textBold:           false
    property real   textFontPointSize:  ScreenTools.defaultFontPointSize

    /// Set true to restore the stock behavior where the entire row (indicator + label) toggles
    /// the control. Default is indicator-only.
    property bool   clickAnywhere:      false

    property var    _qgcPal: QGCPalette { colorGroupEnabled: enabled }
    property bool   _noText: text === ""

    // Width of the live hit area, measured from the left edge: the indicator plus a small pad.
    property real   _hitAreaWidth: ScreenTools.checkBoxIndicatorSize + (ScreenTools.defaultFontPixelWidth * 0.5)

    activeFocusOnPress: true

    // The control's own MouseArea fills the whole row, so the label was just as clickable as the
    // checkbox itself. On a touchscreen that made it easy to toggle a setting with a stray tap --
    // in particular, the Select Tool dialog's buttons land on top of the settings list when you
    // come back from the Fly View, so a second tap could silently flip whichever row was
    // underneath. This overlay swallows presses on the label strip so only the indicator toggles.
    //
    // Sits above the control's internal MouseArea by z-order rather than by declaration order,
    // and deliberately covers the full row height so the indicator stays a usable touch target.
    MouseArea {
        z:                  1000
        anchors.top:        parent.top
        anchors.bottom:     parent.bottom
        anchors.left:       parent.left
        anchors.right:      parent.right
        anchors.leftMargin: _hitAreaWidth
        enabled:            !clickAnywhere && !_noText
        // An enabled MouseArea accepts left-button presses by default, which is what blocks the
        // event from reaching the control underneath. No handler needed.
    }

    style: CheckBoxStyle {
        spacing: _noText ? 0 : ScreenTools.defaultFontPixelWidth * 0.25

        label: Item {
            implicitWidth:  _noText ? 0 : text.implicitWidth + ScreenTools.defaultFontPixelWidth * 0.25
            implicitHeight: _noText ? 0 : Math.max(text.implicitHeight, ScreenTools.checkBoxIndicatorSize)
            baselineOffset: text.baselineOffset

            Text {
                id:                 text
                text:               control.text
                font.pointSize:     textFontPointSize
                font.bold:          control.textBold
                font.family:        ScreenTools.normalFontFamily
                color:              control.textColor
                anchors.centerIn:   parent
            }
        }

        indicator:  Item {
            implicitWidth:  ScreenTools.checkBoxIndicatorSize
            implicitHeight: implicitWidth
            Rectangle {
                anchors.fill:   parent
                color:          control.enabled ? "white" : _qgcPal.text
                border.color:   _qgcPal.text
                border.width:   1
                opacity:        control.checkedState === Qt.PartiallyChecked ? 0.5 : 1
                QGCColoredImage {
                    source:     "/qmlimages/checkbox-check.svg"
                    color:      "black"
                    opacity:    control.checkedState === Qt.Checked ? (control.enabled ? 1 : 0.5) : 0
                    mipmap:     true
                    fillMode:   Image.PreserveAspectFit
                    width:      parent.width * 0.75
                    height:     width
                    sourceSize.height: height
                    anchors.centerIn:  parent
                }
            }
        }
    }
}
