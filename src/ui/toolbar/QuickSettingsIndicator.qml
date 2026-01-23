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

    property var  _activeVehicle:   QGroundControl.multiVehicleManager.activeVehicle

    Component {
        id: quickSettingsPopup

        Rectangle {
            width:  quickSettingsCol.width + ScreenTools.defaultFontPixelWidth * 3
            height: quickSettingsCol.height + ScreenTools.defaultFontPixelHeight * 2
            radius: ScreenTools.defaultFontPixelHeight * 0.5
            color:  qgcPal.window
            border.color: qgcPal.text

            // FactPanelController must be inside the popup
            FactPanelController {
                id: controller
            }

            // Properties to hold the parameter facts
            property Fact wpnavSpeedFact: controller.parameterExists(-1, "WPNAV_SPEED") ?
                                          controller.getParameterFact(-1, "WPNAV_SPEED") : null
            property Fact rtlAltFact:     controller.parameterExists(-1, "RTL_ALT") ?
                                          controller.getParameterFact(-1, "RTL_ALT") : null

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
                    visible:            _activeVehicle && wpnavSpeedFact
                    anchors.margins:    ScreenTools.defaultFontPixelHeight
                    columnSpacing:      ScreenTools.defaultFontPixelWidth
                    anchors.horizontalCenter: parent.horizontalCenter
                    columns: 2

                    QGCLabel { text: qsTr("Waypoint Speed (m/s):") }
                    QGCTextField {
                        id: wpnavSpeedField
                        text: wpnavSpeedFact ? (wpnavSpeedFact.rawValue / 100).toFixed(1) : "--"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        Layout.minimumWidth: ScreenTools.defaultFontPixelWidth * 10

                        onEditingFinished: {
                            if (!wpnavSpeedFact) return
                            var value = parseFloat(text)
                            if (isNaN(value)) value = 0
                            value = Math.max(0.5, Math.min(20.0, value))
                            wpnavSpeedFact.rawValue = Math.round(value * 100)
                            text = value.toFixed(1)
                        }
                    }

                    QGCLabel { text: qsTr("RTL Altitude (m):") }
                    QGCTextField {
                        id: rtlAltField
                        text: rtlAltFact ? (rtlAltFact.rawValue / 100).toFixed(1) : "--"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        Layout.minimumWidth: ScreenTools.defaultFontPixelWidth * 10

                        onEditingFinished: {
                            if (!rtlAltFact) return
                            var value = parseFloat(text)
                            if (isNaN(value)) value = 0
                            value = Math.max(0, Math.min(300, value))
                            rtlAltFact.rawValue = Math.round(value * 100)
                            text = value.toFixed(1)
                        }
                    }
                }

                QGCLabel {
                    visible:            _activeVehicle && !wpnavSpeedFact
                    text:               qsTr("Parameters not available\n(ArduCopter only)")
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
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
