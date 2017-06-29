import QtQuick 2.0
import "../singleton"

Rectangle {

    property string     text        :   ""
    property int        fontSize    :   12
    property color      textColor   :   Color.white
    property color      backColor   :   "transparent"

    id              :   control
    color           :   backColor

    Text {
        id                  :   txt
        text                :   control.text
        font.pointSize      :   fontSize
        anchors.centerIn    :   parent
        color               :   textColor
    }
}
