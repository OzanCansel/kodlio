import QtQuick 2.7
import QtQuick.Controls 2.1
import "../singleton"

TabButton {

    id          :   control
    property alias  backgroundRect  :   back
    property alias  contentTextItem :   txt
    property real   minWidth        :   50
    property bool   coverText       :   true
    property bool   mainHeader      :   false

    width               :   Math.max(minWidth , textMetrics.advanceWidth(txt.text) + 20)
    enabled             :   !mainHeader

    FontMetrics{
        id              :   textMetrics
        font            :   txt.font
    }

    background  :   Item   {
        id              :   back
        implicitWidth   :   control.width
        implicitHeight  :   control.height
        scale           :   1

        Rectangle{
            id          :   backRect
            anchors.fill    :   parent
            border.width    :   control.checked ? 1 : 0
            color           :   {
                if(mainHeader)  return Theme.documentProjectHeaderColor

                return control.hovered || control.checked ? Theme.documentHeaderSelectedHoverColor : Theme.documentHeaderDefaultColor
            }
            radius          :   10
        }

        Rectangle{
            anchors.left    :   backRect.left
            anchors.right   :   backRect.right
            height          :   parent.height / 2
            anchors.bottom  :   parent.bottom
            color           :   backRect.color
        }

        Rectangle{
            id              :   left
            color           :   backRect.border.color
            width           :   backRect.border.width
            height          :   parent.height * 0.5
            anchors.right   :   parent.right
            anchors.bottom  :   parent.bottom
            z               :   2
        }

        Rectangle{
            id              :   right
            color           :   backRect.border.color
            width           :   backRect.border.width
            height          :   parent.height * 0.5
            anchors.left    :   parent.left
            anchors.bottom  :   parent.bottom
            z               :   2
        }
    }

    contentItem :   Text    {
        id                  :   txt
        font.pointSize      :   12
        color               :   "white"
        text                :   control.checked ? "->" + control.text : control.text
        anchors.centerIn    :   back
        verticalAlignment   :   Text.AlignVCenter
        horizontalAlignment :   Text.AlignHCenter
        font.bold           :   mainHeader
    }


    //Animations
    Behavior on width {
        NumberAnimation{
            duration    :   200
        }
    }
}
