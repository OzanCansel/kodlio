import QtQuick 2.0
import QtQuick.Controls 2.2
import "../singleton"

MenuItem {

    property string tooltipText         :   ""
    property bool   tooltipEnabled      :   true
    id                      :   menuItem
    hoverEnabled            :   true

    background  :   Item {
        id      :   menuBackgroundItem
        width   :   menuItem.width
        height  :   menuItem.height

        Rectangle {
            id              :   backgroundRect
            anchors.fill    :   parent
            color           :   menuItem.hovered ? "red" : "white"
        }
    }

    contentItem :   Text {
        id                  :   menuItemContentText
        text                :   menuItem.text
        verticalAlignment   :   Text.verticalCenter
        font.family         :   FontCollection.menuFont

        Behavior on scale {
            NumberAnimation{

            }
        }
    }

    ToolTip.visible     :   tooltipEnabled ? hovered : false
    ToolTip.delay       :   Qt.styleHints.mousePressAndHoldInterval
    ToolTip.text        :   tooltipText
    ToolTip.timeout     :   3000

}
