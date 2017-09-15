import QtQuick 2.0
import QtQuick.Controls 2.1
import "../singleton"

Button {
    id          :   control
    clip        :   true
    property alias  backgroundRect  :   back
    property alias  contentTextItem :   txt

    background  :   Rectangle   {
        id      :   back
        implicitWidth   :   control.width
        implicitHeight  :   control.height
        radius          :   5
        color           :   control.hovered ? Theme.genericButtonBackColor : Theme.genericButtonHoverColor
        scale           :   control.pressed ? 0.95 : 1

        Behavior on scale {
            NumberAnimation{
                duration    :   30
            }
        }
    }

    contentItem :   Text    {
        id                  :   txt
        font.pointSize      :   12
        font.family         :   FontCollection.buttonFont
        color               :   Theme.genericButtonTextColor
        text                :   control.text
        anchors.centerIn    :   back
        verticalAlignment  :   Text.AlignVCenter
        horizontalAlignment:   Text.AlignHCenter
    }
}
