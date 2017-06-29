import QtQml 2.2
import QtQuick 2.0
import QtQuick.Controls 2.1
import "../singleton"

MenuItem {

    id      :   control
    property real   backRadius          :   0
    property color  backColor           :   Theme.dropdownMenuButtonBackColor
    property color  hoverColor          :   Theme.dropdownMenuButtonHoverColor
    property color  textColor           :   "white"
    property alias  textItem            :   textContent
    property alias  backItem            :   backCont
    property string tooltipText         :   ""
    property bool   tooltipEnabled      :   true

    background  :        Rectangle{
        implicitWidth   :   control.width
        implicitHeight  :   40
        radius          :   4
        clip            :   true
        Image {
            id              :   backCont
            source          :   hovered || pressed ? "/res/icon/backgroundpattern-highlight.png" : "/res/icon/backgroundpattern.png"
            fillMode        :   Image.Tile
            anchors.fill    :   parent
            z               :   0
        }
    }

    contentItem :   Text{
        id              :   textContent
        text            :   "> " + control.text
        font.pointSize  :   12
        color           :   textColor
        y               :   25
    }

    ToolTip.visible     :   tooltipEnabled ? hovered : false
    ToolTip.delay       :   Qt.styleHints.mousePressAndHoldInterval
    ToolTip.text        :   tooltipText
    ToolTip.timeout     :   3000

}
