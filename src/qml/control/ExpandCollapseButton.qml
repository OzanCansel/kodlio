import QtQuick 2.0
import "../singleton"

Rectangle {

    property alias  mouseArea       :   area
    property bool   expanded        :   true

    border.width    :   0
    border.color    :   Theme.panelHeadersBackgroundColor
    color           :   "transparent"
    radius          :   5

    Image   {
        id          :   icon
        anchors.fill:   parent
        anchors.margins :   5
        fillMode    :   Image.PreserveAspectFit
        source      :   expanded ? "/res/icon/collapse-48x48.png" : "/res/icon/expand-48x48.png"
    }

    MouseArea{
        id              :   area
        anchors.fill    :   parent
    }
}
