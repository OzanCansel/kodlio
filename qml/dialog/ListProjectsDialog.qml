import QtQuick 2.0
import QtQuick.Controls 2.1
import Kodlio 1.0
import "../form"

Dialog {

    property ProjectManager     manager :   ({})
    property Cloud              cloudApi:   ({})

    id          :   dialog
    x           :   (parent.width / 2) - (width / 2)
    y           :   (parent.height / 2) - (height / 2)
    width       :   500
    height      :   500
    modal       :   true
    closePolicy :   Popup.CloseOnEscape | Popup.CloseOnReleaseOutside
    focus       :   true
    enter       :   Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
    }

    padding :   0

    contentItem :   ListProjectsForm{
        manager     :   dialog.manager
        cloudApi    :   dialog.cloudApi
        width       :   dialog.width
        height      :   dialog.height
        onCloseForm :   {
            dialog.close()
        }
    }
}
