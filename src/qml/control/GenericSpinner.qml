import QtQuick 2.0
import QtQuick.Controls 2.1
import "../singleton"

SpinBox {

    id              :   ctl

    up.indicator    :   Item {
        implicitHeight  :   ctl.height
        implicitWidth   :   implicitHeight
        anchors.right   :   ctl.right
        Rectangle{
            anchors.fill    :   parent
            color           :   up.pressed ? Theme.genericButtonHoverColor :  Theme.genericButtonBackColor
        }
        Text {
            id          :   txt
            text        :   "+"
            font.pixelSize  :   parent.height * 0.5
            color       :   "white"
            anchors.centerIn    :   parent
        }
    }

    down.indicator  :   Item {
        implicitHeight  :   ctl.height
        implicitWidth   :   implicitHeight
        Rectangle{
            anchors.fill    :   parent
            color           :   down.pressed ? Theme.genericButtonHoverColor :  Theme.genericButtonBackColor
        }
        Text {
            id          :   txt2
            text        :   "-"
            font.pixelSize  :   parent.height * 0.5
            color       :   "white"
            anchors.centerIn    :   parent
        }
    }
}
