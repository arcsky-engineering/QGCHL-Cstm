/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * Quick Config Indicator - Quick access to mission and flight params
 *
 ****************************************************************************/

import QtQuick          2.11
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3
import QtQuick.Layouts  1.11

import QGroundControl                       1.0
import QGroundControl.Controls              1.0
import QGroundControl.MultiVehicleManager   1.0
import QGroundControl.ScreenTools           1.0
import QGroundControl.Palette               1.0
import QGroundControl.FactSystem            1.0
import QGroundControl.FactControls          1.0

Item {
    id:             _root
    width:          quickSettingsRow.width
    anchors.top:    parent.top
    anchors.bottom: parent.bottom

    property bool showIndicator: _activeVehicle ? true : false

    property var  _activeVehicle:   QGroundControl.multiVehicleManager.activeVehicle
    property var  _unitsConversion: QGroundControl.unitsConversion
    property var  _flyViewSettings: QGroundControl.settingsManager.flyViewSettings

    function cmToDisplayUnits(cm) {
        return _unitsConversion.metersToAppSettingsVerticalDistanceUnits(cm / 100.0)
    }

    function displayUnitsToCm(displayValue) {
        return _unitsConversion.appSettingsVerticalDistanceUnitsToMeters(displayValue) * 100.0
    }

    function cmpsToDisplaySpeed(cmps) {
        return _unitsConversion.metersSecondToAppSettingsSpeedUnits(cmps / 100.0)
    }

    Component {
        id: quickSettingsPopup

        Rectangle {
            width:  popupColumn.width + ScreenTools.defaultFontPixelWidth * 3
            height: popupColumn.height + ScreenTools.defaultFontPixelHeight * 2
            radius: ScreenTools.defaultFontPixelHeight * 0.5
            color:  qgcPal.window
            border.color: qgcPal.text

            FactPanelController { id: controller }

            // Parameter facts. getParameterFact(-1, name, false) returns null if the
            // param is not present on this vehicle; we use that to hide each row.
            property Fact wpnavSpeedFact:    controller.parameterExists(-1, "WPNAV_SPEED")   ? controller.getParameterFact(-1, "WPNAV_SPEED",   false) : null
            property Fact rtlAltFact:        controller.parameterExists(-1, "RTL_ALT")       ? controller.getParameterFact(-1, "RTL_ALT",       false) : null
            property Fact rtlSpeedFact:      controller.parameterExists(-1, "RTL_SPEED")     ? controller.getParameterFact(-1, "RTL_SPEED",     false) : null
            property Fact loitSpeedFact:     controller.parameterExists(-1, "LOIT_SPEED")    ? controller.getParameterFact(-1, "LOIT_SPEED",    false) : null
            property Fact misRestartFact:    controller.parameterExists(-1, "MIS_RESTART")   ? controller.getParameterFact(-1, "MIS_RESTART",   false) : null

            property bool useAutoRtlSpeed:   rtlSpeedFact   && rtlSpeedFact.rawValue   === 0
            property bool misRestartEnabled: misRestartFact && misRestartFact.rawValue !== 0

            function loitSpeedIs(target) {
                return loitSpeedFact && loitSpeedFact.rawValue === target
            }

            property var _planMasterController: globals.planMasterControllerFlyView
            property var _missionController:    _planMasterController ? _planMasterController.missionController : null

            Column {
                id:                 popupColumn
                spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                anchors.margins:    ScreenTools.defaultFontPixelHeight
                anchors.centerIn:   parent
                width:              ScreenTools.defaultFontPixelWidth * 36

                QGCLabel {
                    text:                       qsTr("Quick Config")
                    font.family:                ScreenTools.demiboldFontFamily
                    anchors.horizontalCenter:   parent.horizontalCenter
                }

                QGCLabel {
                    visible:                    !_activeVehicle
                    text:                       qsTr("No vehicle connected")
                    anchors.horizontalCenter:   parent.horizontalCenter
                }

                //-----------------------------------------------------------------
                // Mission
                //-----------------------------------------------------------------
                QGCLabel {
                    visible:        _activeVehicle
                    text:           qsTr("Mission")
                    font.bold:      true
                }

                QGCCheckBox {
                    visible:        _activeVehicle
                    text:           qsTr("Show mission on map")
                    checked:        _flyViewSettings.showMissionOnMap.rawValue
                    onClicked:      _flyViewSettings.showMissionOnMap.rawValue = checked
                }

                QGCCheckBox {
                    visible:        _activeVehicle
                    text:           qsTr("Show photo capture indicators")
                    checked:        _flyViewSettings.showPhotoCaptureIndicators.rawValue
                    onClicked:      _flyViewSettings.showPhotoCaptureIndicators.rawValue = checked
                }

                QGCButton {
                    visible:        _activeVehicle
                    width:          parent.width
                    text:           qsTr("Download Mission From Vehicle")
                    enabled:        _activeVehicle && _missionController && !_missionController.syncInProgress
                    onClicked: {
                        if (_activeVehicle) {
                            _activeVehicle.reloadMissionFromVehicle()
                        }
                    }
                }

                QGCButton {
                    visible:        _activeVehicle
                    width:          parent.width
                    text:           qsTr("Clear Mission on Vehicle")
                    enabled:        _activeVehicle && _planMasterController
                    onClicked: {
                        mainWindow.showMessageDialog(
                            qsTr("Clear Mission"),
                            qsTr("Are you sure you want to remove all mission items and clear the mission from the vehicle?"),
                            StandardButton.Yes | StandardButton.Cancel,
                            function() {
                                if (_planMasterController) {
                                    _planMasterController.removeAllFromVehicle()
                                }
                            })
                    }
                }

                // Mission download progress — visible only while a load is active.
                ColumnLayout {
                    width:      parent.width
                    visible:    _missionController && _missionController.syncInProgress
                    spacing:    ScreenTools.defaultFontPixelHeight * 0.2

                    ProgressBar {
                        Layout.fillWidth:   true
                        from:               0
                        to:                 1
                        value:              _missionController ? _missionController.progressPct : 0
                    }
                    QGCLabel {
                        Layout.fillWidth:       true
                        horizontalAlignment:    Text.AlignHCenter
                        font.pointSize:         ScreenTools.smallFontPointSize
                        text:                   _missionController ? qsTr("Downloading mission: %1%").arg(Math.round(_missionController.progressPct * 100)) : ""
                    }
                }

                Rectangle { visible: _activeVehicle; width: parent.width; height: 1; color: qgcPal.windowShade }

                //-----------------------------------------------------------------
                // Return to Launch
                //-----------------------------------------------------------------
                QGCLabel {
                    visible:        _activeVehicle && (rtlAltFact || rtlSpeedFact)
                    text:           qsTr("Return to Launch")
                    font.bold:      true
                }

                RowLayout {
                    visible:    _activeVehicle && rtlAltFact
                    width:      parent.width

                    QGCLabel {
                        Layout.fillWidth: true
                        text:             qsTr("RTL Altitude (%1):").arg(_unitsConversion.appSettingsVerticalDistanceUnitsString)
                    }
                    QGCTextField {
                        id:                     rtlAltField
                        text:                   rtlAltFact ? cmToDisplayUnits(rtlAltFact.rawValue).toFixed(1) : "--"
                        inputMethodHints:       Qt.ImhFormattedNumbersOnly
                        Layout.minimumWidth:    ScreenTools.defaultFontPixelWidth * 10
                        onEditingFinished: {
                            if (!rtlAltFact) return
                            var value = parseFloat(text)
                            if (isNaN(value)) value = 0
                            var maxInDisplayUnits = _unitsConversion.metersToAppSettingsVerticalDistanceUnits(300)
                            value = Math.max(0, Math.min(maxInDisplayUnits, value))
                            rtlAltFact.rawValue = Math.round(displayUnitsToCm(value))
                            text = value.toFixed(1)
                        }
                        Connections {
                            target: rtlAltFact
                            onRawValueChanged: rtlAltField.text = rtlAltFact ? cmToDisplayUnits(rtlAltFact.rawValue).toFixed(1) : "--"
                        }
                    }
                }

                RowLayout {
                    visible:    _activeVehicle && rtlSpeedFact && !useAutoRtlSpeed
                    width:      parent.width

                    QGCLabel {
                        Layout.fillWidth: true
                        text:             qsTr("RTL Speed (%1):").arg(_unitsConversion.appSettingsSpeedUnitsString)
                    }
                    QGCTextField {
                        id:                     rtlSpeedField
                        text:                   rtlSpeedFact && rtlSpeedFact.rawValue > 0 ? cmpsToDisplaySpeed(rtlSpeedFact.rawValue).toFixed(1) : "--"
                        inputMethodHints:       Qt.ImhFormattedNumbersOnly
                        Layout.minimumWidth:    ScreenTools.defaultFontPixelWidth * 10
                        onEditingFinished: {
                            if (!rtlSpeedFact) return
                            var value = parseFloat(text)
                            if (isNaN(value)) value = 2.0
                            var mps = _unitsConversion.appSettingsSpeedUnitsToMetersSecond(value)
                            mps = Math.max(2.0, Math.min(14.0, mps))
                            rtlSpeedFact.rawValue = Math.round(mps * 100)
                            text = cmpsToDisplaySpeed(rtlSpeedFact.rawValue).toFixed(1)
                        }
                        Connections {
                            target: rtlSpeedFact
                            onRawValueChanged: {
                                if (rtlSpeedFact && rtlSpeedFact.rawValue > 0) {
                                    rtlSpeedField.text = cmpsToDisplaySpeed(rtlSpeedFact.rawValue).toFixed(1)
                                }
                            }
                        }
                    }
                }

                QGCCheckBox {
                    visible:    _activeVehicle && rtlSpeedFact
                    text:       qsTr("Use Auto Flight Speed")
                    checked:    useAutoRtlSpeed
                    onClicked: {
                        if (!rtlSpeedFact) return
                        rtlSpeedFact.rawValue = checked ? 0 : 600
                    }
                }

                Rectangle { visible: _activeVehicle && loitSpeedFact; width: parent.width; height: 1; color: qgcPal.windowShade }

                //-----------------------------------------------------------------
                // Manual Flight Speed
                //-----------------------------------------------------------------
                QGCLabel {
                    visible:        _activeVehicle && loitSpeedFact
                    text:           qsTr("Manual Flight Speed")
                    font.bold:      true
                }

                RowLayout {
                    visible:    _activeVehicle && loitSpeedFact
                    width:      parent.width
                    spacing:    ScreenTools.defaultFontPixelWidth

                    QGCButton {
                        text:               qsTr("Slow")
                        Layout.fillWidth:   true
                        checked:            loitSpeedIs(400)
                        onClicked:          { if (loitSpeedFact) loitSpeedFact.rawValue = 400 }
                    }
                    QGCButton {
                        text:               qsTr("Normal")
                        Layout.fillWidth:   true
                        checked:            loitSpeedIs(800)
                        onClicked:          { if (loitSpeedFact) loitSpeedFact.rawValue = 800 }
                    }
                    QGCButton {
                        text:               qsTr("Fast")
                        Layout.fillWidth:   true
                        checked:            loitSpeedIs(1200)
                        onClicked:          { if (loitSpeedFact) loitSpeedFact.rawValue = 1200 }
                    }
                }

                QGCLabel {
                    visible:                    _activeVehicle && loitSpeedFact
                    anchors.horizontalCenter:   parent.horizontalCenter
                    opacity:                    0.7
                    font.pointSize:             ScreenTools.smallFontPointSize
                    text:                       loitSpeedFact ? qsTr("Current: %1 m/s").arg((loitSpeedFact.rawValue / 100).toFixed(1)) : ""
                }

                Rectangle { visible: _activeVehicle && (wpnavSpeedFact || misRestartFact); width: parent.width; height: 1; color: qgcPal.windowShade }

                //-----------------------------------------------------------------
                // Auto Settings
                //-----------------------------------------------------------------
                QGCLabel {
                    visible:        _activeVehicle && (wpnavSpeedFact || misRestartFact)
                    text:           qsTr("Auto Settings")
                    font.bold:      true
                }

                RowLayout {
                    visible:    _activeVehicle && wpnavSpeedFact
                    width:      parent.width

                    QGCLabel {
                        Layout.fillWidth: true
                        text:             qsTr("Auto Flight Speed (m/s):")
                    }
                    QGCTextField {
                        id:                     wpnavSpeedField
                        text:                   wpnavSpeedFact ? (wpnavSpeedFact.rawValue / 100).toFixed(1) : "--"
                        inputMethodHints:       Qt.ImhFormattedNumbersOnly
                        Layout.minimumWidth:    ScreenTools.defaultFontPixelWidth * 10
                        onEditingFinished: {
                            if (!wpnavSpeedFact) return
                            var value = parseFloat(text)
                            if (isNaN(value)) value = 0
                            value = Math.max(0.5, Math.min(20.0, value))
                            wpnavSpeedFact.rawValue = Math.round(value * 100)
                            text = value.toFixed(1)
                        }
                        Connections {
                            target: wpnavSpeedFact
                            onRawValueChanged: wpnavSpeedField.text = wpnavSpeedFact ? (wpnavSpeedFact.rawValue / 100).toFixed(1) : "--"
                        }
                    }
                }

                QGCCheckBox {
                    visible:    _activeVehicle && misRestartFact
                    text:       qsTr("Restart mission from beginning")
                    checked:    misRestartEnabled
                    onClicked: {
                        if (misRestartFact) misRestartFact.rawValue = checked ? 1 : 0
                    }
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

        QGCLabel {
            anchors.verticalCenter: parent.verticalCenter
            color:                  qgcPal.buttonText
            text:                   qsTr("Quick\nConfig")
            font.pointSize:         ScreenTools.smallFontPointSize
        }
    }

    MouseArea {
        anchors.fill:   parent
        onClicked:      mainWindow.showIndicatorPopup(_root, quickSettingsPopup)
    }
}
