import QtQuick 2.0
import QtQuick.Controls 2.1

ComboBox {

    id          :   control

    textRole    :   "key"
    popup.enter :   Transition {
        NumberAnimation{
            target  :   popup
            property:   "height"
            from    :   0
            to      :   popup.implicitHeight
        }
    }

    delegate        :   GenericLabel    {
        id              :   label
        radius          :   0
        text            :   key
        implicitWidth   :   control.width
        implicitHeight  :   control.height
        border.width    :   1

        MouseArea{
            anchors.fill    :   parent
            onClicked       :   {control.currentIndex = index; control.popup.close() }
        }
    }

    background          :   Rectangle{
        id              :   back
        implicitWidth   :   control.width
        height          :   50
        color           :   "green"
    }
}
