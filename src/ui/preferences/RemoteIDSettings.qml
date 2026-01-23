/****************************************************************************
 *
 * (c) 2009-2022 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtQuick.Controls.Styles  1.4
import QtQuick.Dialogs          1.2
import QtQuick.Layouts          1.2

import QGroundControl                       1.0
import QGroundControl.FactSystem            1.0
import QGroundControl.FactControls          1.0
import QGroundControl.Controls              1.0
import QGroundControl.ScreenTools           1.0
import QGroundControl.MultiVehicleManager   1.0
import QGroundControl.Palette               1.0

Rectangle {
    id:             remoteIDRoot
    color:          qgcPal.window
    anchors.fill:   parent

    // Visual properties
    property real _margins:             ScreenTools.defaultFontPixelWidth
    property real _labelWidth:          ScreenTools.defaultFontPixelWidth * 28
    property real _valueWidth:          ScreenTools.defaultFontPixelWidth * 24
    property real _columnSpacing:       ScreenTools.defaultFontPixelHeight * 0.25
    property real _comboFieldWidth:     ScreenTools.defaultFontPixelWidth * 30
    property real _valueFieldWidth:     ScreenTools.defaultFontPixelWidth * 10
    property int  _borderWidth:         3
    // Flags visual properties
    property real   flagsWidth:         ScreenTools.defaultFontPixelWidth * 15
    property real   flagsHeight:        ScreenTools.defaultFontPixelWidth * 7
    property int    radiusFlags:        5

    // Flag to get active vehicle and active RID
    property var  _activeRID:           _activeVehicle && _activeVehicle.remoteIDManager ? _activeVehicle.remoteIDManager : null

    // Healthy connection with RID device
    property bool commsGood:            _activeVehicle && _activeVehicle.remoteIDManager ? _activeVehicle.remoteIDManager.commsGood : false

    // General properties
    property var  _activeVehicle:       QGroundControl.multiVehicleManager.activeVehicle
    property int  _locationType:        QGroundControl.settingsManager.remoteIDSettings.locationType.value

    // GPS properties
    property var    gcsPosition:        QGroundControl.qgcPositionManger.gcsPosition
    property real   gcsHeading:         QGroundControl.qgcPositionManger.gcsHeading
    property real   gcsHDOP:            QGroundControl.qgcPositionManger.gcsPositionHorizontalAccuracy

    QGCPalette { id: qgcPal }

    QGCFlickable {
        id:                 flickable
        clip:               true
        anchors.fill:       parent
        anchors.margins:    ScreenTools.defaultFontPixelWidth
        contentHeight:      mainColumn.height
        contentWidth:       mainColumn.width
        flickableDirection: Flickable.VerticalFlick

        ColumnLayout {
            id:                         mainColumn
            anchors.horizontalCenter:   parent.horizontalCenter
            spacing:                    _margins * 2

            // ---------------------------------------- STATUS FLAGS -----------------------------------------
            Rectangle {
                id:                     flagsRectangle
                Layout.preferredHeight: statusGrid.height + (_margins * 2)
                Layout.preferredWidth:  statusGrid.width + (_margins * 2)
                color:                  qgcPal.windowShade
                visible:                _activeVehicle
                Layout.alignment:       Qt.AlignHCenter

                GridLayout {
                    id:                         statusGrid
                    anchors.margins:            _margins
                    anchors.top:                parent.top
                    anchors.horizontalCenter:   parent.horizontalCenter
                    rows:                       1
                    rowSpacing:                 _margins * 3
                    columnSpacing:              _margins * 2

                    Rectangle {
                        id:                     armFlag
                        Layout.preferredHeight: flagsHeight
                        Layout.preferredWidth:  flagsWidth
                        color:                  _activeRID ? (_activeVehicle.remoteIDManager.armStatusGood ? qgcPal.colorGreen : qgcPal.colorRed) : qgcPal.colorGrey
                        radius:                 radiusFlags
                        visible:                commsGood

                        QGCLabel {
                            anchors.fill:           parent
                            text:                   qsTr("ARM STATUS")
                            wrapMode:               Text.WordWrap
                            horizontalAlignment:    Text.AlignHCenter
                            verticalAlignment:      Text.AlignVCenter
                            font.bold:              true
                        }
                    }

                    Rectangle {
                        id:                     commsFlag
                        Layout.preferredHeight: flagsHeight
                        Layout.preferredWidth:  flagsWidth
                        color:                  _activeRID ? (_activeVehicle.remoteIDManager.commsGood ? qgcPal.colorGreen : qgcPal.colorRed) : qgcPal.colorGrey
                        radius:                 radiusFlags

                        QGCLabel {
                            anchors.fill:           parent
                            text:                   _activeRID && _activeVehicle.remoteIDManager.commsGood ? qsTr("RID COMMS") : qsTr("NOT CONNECTED")
                            wrapMode:               Text.WordWrap
                            horizontalAlignment:    Text.AlignHCenter
                            verticalAlignment:      Text.AlignVCenter
                            font.bold:              true
                        }
                    }

                    Rectangle {
                        id:                     gpsFlag
                        Layout.preferredHeight: flagsHeight
                        Layout.preferredWidth:  flagsWidth
                        color:                  _activeRID ? (_activeVehicle.remoteIDManager.gcsGPSGood ? qgcPal.colorGreen : qgcPal.colorRed) : qgcPal.colorGrey
                        radius:                 radiusFlags
                        visible:                commsGood

                        QGCLabel {
                            anchors.fill:           parent
                            text:                   qsTr("GCS GPS")
                            wrapMode:               Text.WordWrap
                            horizontalAlignment:    Text.AlignHCenter
                            verticalAlignment:      Text.AlignVCenter
                            font.bold:              true
                        }
                    }
                }
            }

            // ---------------------------------------- ARM STATUS ERROR -----------------------------------------
            Rectangle {
                id:                     armStatusRectangle
                Layout.preferredHeight: armStatusGrid.height + (_margins * 2)
                Layout.preferredWidth:  armStatusGrid.width + (_margins * 2)
                color:                  qgcPal.windowShade
                Layout.alignment:       Qt.AlignHCenter
                border.width:           _borderWidth
                border.color:           qgcPal.colorRed
                visible:                _activeVehicle && !_activeVehicle.remoteIDManager.armStatusGood

                GridLayout {
                    id:                         armStatusGrid
                    anchors.margins:            _margins
                    anchors.top:                parent.top
                    anchors.horizontalCenter:   parent.horizontalCenter
                    columns:                    2
                    rowSpacing:                 _margins * 3
                    columnSpacing:              _margins * 2

                    QGCLabel {
                        text:               qsTr("Arm status error: ")
                        Layout.fillWidth:   true
                    }
                    QGCLabel {
                        text:               _activeVehicle ? _activeVehicle.remoteIDManager.armStatusError : ""
                        Layout.fillWidth:   true
                    }
                }
            }

            // ----------------------------------------- GPS GCS -------------------------------------------
            QGCLabel {
                text:               qsTr("GCS Location")
                Layout.alignment:   Qt.AlignHCenter
                font.pointSize:     ScreenTools.mediumFontPointSize
            }

            Rectangle {
                id:                     gpsRectangle
                Layout.preferredHeight: gpsGridData.height + (_margins * 2)
                Layout.preferredWidth:  gpsGridData.width + (_margins * 2)
                color:                  qgcPal.windowShade
                Layout.alignment:       Qt.AlignHCenter
                border.width:           _borderWidth
                border.color:           _activeRID ? (_activeVehicle.remoteIDManager.gcsGPSGood ? color : qgcPal.colorRed) : color

                GridLayout {
                    id:                         gpsGridData
                    anchors.margins:            _margins
                    anchors.top:                parent.top
                    anchors.horizontalCenter:   parent.horizontalCenter
                    rowSpacing:                 _margins
                    columns:                    2
                    columnSpacing:              _margins * 2

                    QGCLabel {
                        text:               qsTr("Status:")
                        Layout.fillWidth:   true
                    }
                    QGCLabel {
                        text:               gcsPosition.isValid ? qsTr("Live GNSS Active") : qsTr("Waiting for GPS fix...")
                        color:              gcsPosition.isValid ? qgcPal.colorGreen : qgcPal.colorOrange
                        Layout.fillWidth:   true
                    }

                    QGCLabel {
                        text:               qsTr("Latitude:")
                        Layout.fillWidth:   true
                    }
                    QGCLabel {
                        text:               gcsPosition.isValid ? gcsPosition.latitude.toFixed(7) : "N/A"
                        Layout.fillWidth:   true
                    }

                    QGCLabel {
                        text:               qsTr("Longitude:")
                        Layout.fillWidth:   true
                    }
                    QGCLabel {
                        text:               gcsPosition.isValid ? gcsPosition.longitude.toFixed(7) : "N/A"
                        Layout.fillWidth:   true
                    }

                    QGCLabel {
                        text:               qsTr("Altitude:")
                        Layout.fillWidth:   true
                    }
                    QGCLabel {
                        text:               gcsPosition.isValid && !isNaN(gcsPosition.altitude) ? gcsPosition.altitude.toFixed(1) + " m" : "N/A"
                        Layout.fillWidth:   true
                    }

                    QGCLabel {
                        text:               qsTr("Heading:")
                        Layout.fillWidth:   true
                    }
                    QGCLabel {
                        text:               gcsPosition.isValid && !isNaN(gcsHeading) ? gcsHeading.toFixed(1) + "\u00B0" : "N/A"
                        Layout.fillWidth:   true
                    }

                    QGCLabel {
                        text:               qsTr("Accuracy:")
                        Layout.fillWidth:   true
                    }
                    QGCLabel {
                        text:               gcsPosition.isValid && gcsHDOP ? gcsHDOP.toFixed(1) + " m" : "N/A"
                        Layout.fillWidth:   true
                    }
                }
            }

            // Info text
            QGCLabel {
                text:               qsTr("Operator location is automatically sent to the vehicle\nusing Live GNSS from your device.")
                Layout.alignment:   Qt.AlignHCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize:     ScreenTools.smallFontPointSize
                opacity:            0.7
            }

            // No vehicle connected message
            QGCLabel {
                text:               qsTr("Connect a vehicle to see Remote ID status")
                Layout.alignment:   Qt.AlignHCenter
                visible:            !_activeVehicle
                font.pointSize:     ScreenTools.mediumFontPointSize
            }
        }
    }
}
