/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick                  2.12
import QtQuick.Controls         2.4
import QtQuick.Dialogs          1.3
import QtQuick.Layouts          1.12

import QtLocation               5.3
import QtPositioning            5.3
import QtQuick.Window           2.2
import QtQml.Models             2.1

import QGroundControl               1.0
import QGroundControl.Controllers   1.0
import QGroundControl.Controls      1.0
import QGroundControl.FactSystem    1.0
import QGroundControl.FlightDisplay 1.0
import QGroundControl.FlightMap     1.0
import QGroundControl.Palette       1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Vehicle       1.0

Item {
    id: _root

    // These should only be used by MainRootWindow
    property var planController:    _planController
    property var guidedController:  _guidedController

    PlanMasterController {
        id:                     _planController
        flyView:                true
        Component.onCompleted:  start()
    }

    property bool   _mainWindowIsMap:       mapControl.pipState.state === mapControl.pipState.fullState
    property bool   _isFullWindowItemDark:  _mainWindowIsMap ? mapControl.isSatelliteMap : true
    property var    _activeVehicle:         QGroundControl.multiVehicleManager.activeVehicle
    property var    _missionController:     _planController.missionController
    property var    _geoFenceController:    _planController.geoFenceController
    property var    _rallyPointController:  _planController.rallyPointController
    property real   _margins:               ScreenTools.defaultFontPixelWidth / 2
    property var    _guidedController:      guidedActionsController
    property var    _guidedActionList:      guidedActionList
    property var    _guidedValueSlider:     guidedValueSlider
    property var    _widgetLayer:           widgetLayer
    property real   _toolsMargin:           ScreenTools.defaultFontPixelWidth * 0.75
    property rect   _centerViewport:        Qt.rect(0, 0, width, height)
    property real   _rightPanelWidth:       ScreenTools.defaultFontPixelWidth * 30
    property var    _mapControl:            mapControl

    property real   _fullItemZorder:    0
    property real   _pipItemZorder:     QGroundControl.zOrderWidgets

    function _calcCenterViewPort() {
        var newToolInset = Qt.rect(0, 0, width, height)
        toolstrip.adjustToolInset(newToolInset)
        if (QGroundControl.corePlugin.options.instrumentWidget) {
            flightDisplayViewWidgets.adjustToolInset(newToolInset)
        }
    }

    QGCToolInsets {
        id:                     _toolInsets
        leftEdgeBottomInset:    _pipOverlay.visible ? _pipOverlay.x + _pipOverlay.width : 0
        bottomEdgeLeftInset:    _pipOverlay.visible ? parent.height - _pipOverlay.y : 0
    }

    FlyViewWidgetLayer {
        id:                     widgetLayer
        anchors.top:            parent.top
        anchors.bottom:         parent.bottom
        anchors.left:           parent.left
        anchors.right:          guidedValueSlider.visible ? guidedValueSlider.left : parent.right
        z:                      _fullItemZorder + 1
        parentToolInsets:       _toolInsets
        mapControl:             _mapControl
        visible:                !QGroundControl.videoManager.fullScreen
    }


    FlyViewCustomLayer {
        id:                 customOverlay
        anchors.fill:       widgetLayer
        z:                  _fullItemZorder + 2
        parentToolInsets:   widgetLayer.totalToolInsets
        mapControl:         _mapControl
        visible:            !QGroundControl.videoManager.fullScreen
    }

    // Development tool for visualizing the insets for a paticular layer, enable if needed
    /*
    FlyViewInsetViewer {
        id:                     widgetLayerInsetViewer
        anchors.top:            parent.top
        anchors.bottom:         parent.bottom
        anchors.left:           parent.left
        anchors.right:          guidedValueSlider.visible ? guidedValueSlider.left : parent.right

        z:                      widgetLayer.z + 1

        insetsToView:           customOverlay.totalToolInsets
    }*/

    GuidedActionsController {
        id:                 guidedActionsController
        missionController:  _missionController
        actionList:         _guidedActionList
        guidedValueSlider:     _guidedValueSlider
    }

    /*GuidedActionConfirm {
        id:                         guidedActionConfirm
        anchors.margins:            _margins
        anchors.bottom:             parent.bottom
        anchors.horizontalCenter:   parent.horizontalCenter
        z:                          QGroundControl.zOrderTopMost
        guidedController:           _guidedController
        guidedValueSlider:             _guidedValueSlider
    }*/

    GuidedActionList {
        id:                         guidedActionList
        anchors.margins:            _margins
        anchors.bottom:             parent.bottom
        anchors.horizontalCenter:   parent.horizontalCenter
        z:                          QGroundControl.zOrderTopMost
        guidedController:           _guidedController
    }

    //-- Guided value slider (e.g. altitude)
    GuidedValueSlider {
        id:                 guidedValueSlider
        anchors.margins:    _toolsMargin
        anchors.right:      parent.right
        anchors.top:        parent.top
        anchors.bottom:     parent.bottom
        z:                  QGroundControl.zOrderTopMost
        radius:             ScreenTools.defaultFontPixelWidth / 2
        width:              ScreenTools.defaultFontPixelWidth * 10
        color:              qgcPal.window
        visible:            false
    }

    FlyViewMap {
        id:                     mapControl
        planMasterController:   _planController
        rightPanelWidth:        ScreenTools.defaultFontPixelHeight * 9
        pipMode:                !_mainWindowIsMap
        toolInsets:             customOverlay.totalToolInsets
        mapName:                "FlightDisplayView"
    }

    FlyViewVideo {
        id: videoControl
    }

    // RTSP stream switcher button — shows on FlyView when an RTSP source is
    // selected and both rtspUrl and rtspUrl2 are configured. Clicking toggles
    // _currentStream in VideoManager and restarts the video pipeline.
    Rectangle {
        id:                     rtspStreamSwitchButton
        // Steps aside for the guided value slider the same way the widget layer
        // does, rather than sitting underneath it. Both occupy this right edge
        // at the same width, so without this the button is simply hidden
        // whenever a guided altitude change is in progress.
        anchors.right:          guidedValueSlider.visible ? guidedValueSlider.left : parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin:    _toolsMargin
        width:                  ScreenTools.defaultFontPixelWidth * 10
        height:                 ScreenTools.defaultFontPixelHeight * 2.8
        radius:                 ScreenTools.defaultFontPixelWidth / 2
        // Bottom of the overlay stack, just above the full screen map/video it
        // sits on. zOrderTopMost put it in the same band as the guided action
        // overlays, and being declared after them it painted on top: the guided
        // value slider is a full height strip on this same right edge, at this
        // same width, so the altitude slider ended up behind this button.
        //
        // This also lets the fly view widgets cover it. z is not transitive, so
        // nothing inside FlyViewWidgetLayer could ever beat this button while it
        // outranked the layer itself, which is why the micROM settings fly-out
        // opened behind it.
        z:                      _fullItemZorder
        color:                  "#80000000"
        border.color:           "white"
        border.width:           1

        property var _videoSettings: QGroundControl.settingsManager.videoSettings
        property bool _isRTSP: _videoSettings.videoSource.rawValue === _videoSettings.rtspVideoSource

        visible: !QGroundControl.videoManager.fullScreen
                 && QGroundControl.videoManager.hasVideo
                 && _isRTSP
                 && _videoSettings.rtspUrl.rawValue !== ""
                 && _videoSettings.rtspUrl2.rawValue !== ""

        Column {
            anchors.centerIn:   parent
            spacing:            ScreenTools.defaultFontPixelHeight * 0.1

            QGCColoredImage {
                anchors.horizontalCenter: parent.horizontalCenter
                source:             "/qmlimages/camera_video.svg"
                color:              "white"
                width:              ScreenTools.defaultFontPixelHeight * 1.2
                height:             width
                sourceSize.height:  height
                fillMode:           Image.PreserveAspectFit
            }

            QGCLabel {
                anchors.horizontalCenter: parent.horizontalCenter
                text:               QGroundControl.videoManager.currentStream === "1" ? qsTr("Stream 1") : qsTr("Stream 2")
                color:              "white"
                font.bold:          true
            }
        }

        MouseArea {
            anchors.fill:   parent
            onClicked:      QGroundControl.videoManager.switchRTSPStream()
        }
    }

    QGCPipOverlay {
        id:                     _pipOverlay
        anchors.left:           parent.left
        anchors.bottom:         parent.bottom
        anchors.margins:        _toolsMargin
        item1IsFullSettingsKey: "MainFlyWindowIsMap"
        item1:                  mapControl
        item2:                  QGroundControl.videoManager.hasVideo ? videoControl : null
        fullZOrder:             _fullItemZorder
        pipZOrder:              _pipItemZorder
        show:                   !QGroundControl.videoManager.fullScreen &&
                                    (videoControl.pipState.state === videoControl.pipState.pipState || mapControl.pipState.state === mapControl.pipState.pipState)
    }
}
