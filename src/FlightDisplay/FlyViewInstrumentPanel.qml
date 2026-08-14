/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick 2.12

import QGroundControl               1.0
import QGroundControl.Controls      1.0
import QGroundControl.ScreenTools   1.0

// This control contains the instruments as well and the instrument pages which include values, camera, ...
Column {
    id:         _root
    spacing:    _toolsMargin
    z:          QGroundControl.zOrderWidgets

    property real availableHeight

    property bool scaleForSmallScreen: QGroundControl.corePlugin.isHerelink
    property bool isVerticalInstrumentPanel: flightDisplayViewWidgets.source == "qrc:/qml/QGCInstrumentWidgetAlternate.qml"

    // Collapsed state survives restarts, the same way the PiP overlay remembers
    // whether it was hidden. Someone who flies with the gauges out of the way
    // wants them out of the way next time too.
    readonly property string _expandedSettingsKey: "IsInstrumentPanelExpanded"

    property bool _isExpanded: true

    Component.onCompleted: _isExpanded = QGroundControl.loadBoolGlobalSetting(_expandedSettingsKey, true)

    function _setExpanded(expanded) {
        _isExpanded = expanded
        QGroundControl.saveBoolGlobalSetting(_expandedSettingsKey, expanded)
    }

    // Collapse/expand tab. Sits above the gauges so it stays put in the top
    // right corner whichever state it is in, rather than travelling up the
    // screen as the panel below it disappears.
    Rectangle {
        anchors.right:  parent.right
        height:         ScreenTools.defaultFontPixelHeight * 2
        width:          height
        radius:         ScreenTools.defaultFontPixelHeight / 3
        color:          Qt.rgba(0, 0, 0, 0.5)

        Image {
            anchors.centerIn:   parent
            width:              parent.width * 0.75
            height:             parent.height * 0.75
            sourceSize.height:  height
            // Right to push the panel away, left to pull it back
            source:             _isExpanded ? "/res/buttonRight.svg" : "/res/buttonLeft.svg"
            mipmap:             true
            fillMode:           Image.PreserveAspectFit
        }

        QGCMouseArea {
            fillItem:   parent
            onClicked:  _root._setExpanded(!_root._isExpanded)
        }
    }

    FlightDisplayViewWidgets {
        id:                 flightDisplayViewWidgets
        width:              scaleForSmallScreen && isVerticalInstrumentPanel ? parent.width * 0.4 : parent.width * 0.8
        missionController:  _missionController
        anchors.right:      parent.right
        // Column positioners skip invisible children, so hiding this collapses
        // the panel down to the tab and shrinks topEdgeRightInset with it,
        // letting the other fly view tools reclaim the vertical space.
        visible:            _isExpanded
    }
}
