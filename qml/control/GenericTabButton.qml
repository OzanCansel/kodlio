import QtQuick 2.0
import QtQuick.Controls 2.1
import "../singleton"

TabButton {

    id          :   control
    property alias  backgroundRect  :   back
    property alias  contentTextItem :   txt

    background  :   Rectangle   {
        id      :   back
        implicitWidth   :   control.width
        implicitHeight  :   control.height
        color           :   control.hovered ? Theme.genericButtonBackColor : Theme.genericButtonHoverColor
        scale           :   control.pressed ? 0.99 : 1
        border.width    :   control.checked ? 1 : 0

        Behavior on scale {
            NumberAnimation{
                duration    :   30
            }
        }
    }

    contentItem :   Text    {
        id                  :   txt
        font.pointSize      :   12
        color               :   "white"
        text                :   control.text
        anchors.centerIn    :   back
        verticalAlignment  :   Text.AlignVCenter
        horizontalAlignment:   Text.AlignHCenter
    }
}
