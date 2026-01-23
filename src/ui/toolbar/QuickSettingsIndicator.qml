/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * Quick Settings Indicator - Allows quick adjustment of flight parameters
 *
 ****************************************************************************/

import QtQuick          2.11
import QtQuick.Layouts  1.11

import QGroundControl                       1.0
import QGroundControl.Controls              1.0
import QGroundControl.MultiVehicleManager   1.0
import QGroundControl.ScreenTools           1.0
import QGroundControl.Palette               1.0
import QGroundControl.FactSystem            1.0
import QGroundControl.FactControls          1.0

//-------------------------------------------------------------------------
//-- Quick Settings Indicator
Item {
    id:             _root
    width:          quickSettingsRow.width
    anchors.top:    parent.top
    anchors.bottom: parent.bottom

    property bool showIndicator: _activeVehicle ? true : false

    property var    _activeVehicle:     QGroundControl.multiVehicleManager.activeVehicle

    FactPanelController { id: controller }

    property Fact _wpnavSpeedFact
    property Fact _rtlAltFact

    Connections {
        target: QGroundControl.multiVehicleManager
        onActiveVehicleChanged: {
            if (QGroundControl.multiVehicleManager.activeVehicle) {
                _wpnavSpeedFact = controller.getParameterFact(-1, "WPNAV_SPEED", false)
                _rtlAltFact = controller.getParameterFact(-1, "RTL_ALT", false)
            } else {
                _wpnavSpeedFact = null
                _rtlAltFact = null
            }
        }
    }

    Component.onCompleted: {
        if (_activeVehicle) {
            _wpnavSpeedFact = controller.getParameterFact(-1, "WPNAV_SPEED", false)
            _rtlAltFact = controller.getParameterFact(-1, "RTL_ALT", false)
        }
    }

    Component {
        id: quickSettingsPopup

        Rectangle {
            width:  quickSettingsCol.width + ScreenTools.defaultFontPixelWidth * 3
            height: quickSettingsCol.height + ScreenTools.defaultFontPixelHeight * 2
            radius: ScreenTools.defaultFontPixelHeight * 0.5
            color:  qgcPal.window
            border.color: qgcPal.text

            Column {
                id:                 quickSettingsCol
                spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                width:              Math.max(quickSettingsLabel.width, quickSettingsGrid.width)
                anchors.margins:    ScreenTools.defaultFontPixelHeight
                anchors.centerIn:   parent

                QGCLabel {
                    id:             quickSettingsLabel
                    text:           qsTr("Flight Parameters")
                    font.family:    ScreenTools.demiboldFontFamily
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                GridLayout {
                    id:                 quickSettingsGrid
                    visible:            _activeVehicle
                    anchors.margins:    ScreenTools.defaultFontPixelHeight
                    columnSpacing:      ScreenTools.defaultFontPixelWidth
                    anchors.horizontalCenter: parent.horizontalCenter
                    columns: 2

                    QGCLabel { text: qsTr("Waypoint Speed (m/s):") }
                    QGCTextField {
                        id: wpnavSpeedField
                        text: _wpnavSpeedFact ? (_wpnavSpeedFact.value / 100).toFixed(1) : "--"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        Layout.minimumWidth: ScreenTools.defaultFontPixelWidth * 10

                        onEditingFinished: {
                            if (!_wpnavSpeedFact) return
                            var value = parseFloat(text)
                            if (isNaN(value)) value = 0
                            value = Math.max(0.5, Math.min(20.0, value))
                            _wpnavSpeedFact.value = Math.round(value * 100)
                            wpnavSpeedField.text = value.toFixed(1)
                        }

                        Connections {
                            target: _wpnavSpeedFact
                            onValueChanged: {
                                if (_wpnavSpeedFact) {
                                    wpnavSpeedField.text = (_wpnavSpeedFact.value / 100).toFixed(1)
                                }
                            }
                        }
                    }

                    QGCLabel { text: qsTr("RTL Altitude (m):") }
                    QGCTextField {
                        id: rtlAltField
                        text: _rtlAltFact ? (_rtlAltFact.value / 100).toFixed(1) : "--"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        Layout.minimumWidth: ScreenTools.defaultFontPixelWidth * 10

                        onEditingFinished: {
                            if (!_rtlAltFact) return
                            var value = parseFloat(text)
                            if (isNaN(value)) value = 0
                            value = Math.max(0, Math.min(300, value))
                            _rtlAltFact.value = Math.round(value * 100)
                            rtlAltField.text = value.toFixed(1)
                        }

                        Connections {
                            target: _rtlAltFact
                            onValueChanged: {
                                if (_rtlAltFact) {
                                    rtlAltField.text = (_rtlAltFact.value / 100).toFixed(1)
                                }
                            }
                        }
                    }
                }

                QGCLabel {
                    visible:            !_activeVehicle
                    text:               qsTr("No vehicle connected")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }

    Row {
        id:             quickSettingsRow
        anchors.top:    parent.top
        anchors.bottom: parent.bottom
        spacing:        ScreenTools.defaultFontPixelWidth / 2

        QGCColoredImage {
            id:                 quickSettingsIcon
            width:              height
            anchors.top:        parent.top
            anchors.bottom:     parent.bottom
            source:             "/qmlimages/Gears.svg"
            fillMode:           Image.PreserveAspectFit
            sourceSize.height:  height
            color:              qgcPal.buttonText
        }

        Column {
            id:                     quickSettingsValuesColumn
            anchors.verticalCenter: parent.verticalCenter
            spacing:                0

            QGCLabel {
                color:  qgcPal.buttonText
                text:   "Speed"
                font.pointSize: ScreenTools.smallFontPointSize
            }

            QGCLabel {
                color:  qgcPal.buttonText
                text:   "RTL"
                font.pointSize: ScreenTools.smallFontPointSize
            }
        }
    }

    MouseArea {
        anchors.fill:   parent
        onClicked:      mainWindow.showIndicatorPopup(_root, quickSettingsPopup)
    }
}
