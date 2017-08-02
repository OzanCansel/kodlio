import QtQuick 2.0
import QtQuick.Controls 2.1
import Kodlio 1.0
import "../form"

Dialog {

    property Cloud  cloud       :   ({})

    id          :   loginDialog
    width       :   300
    height      :   200
    x           :   parent.width / 2 - (width / 2)
    y           :   parent.height / 2 - (height / 2)
    padding     :   0
    modal       :   true
    closePolicy :   Popup.CloseOnEscape | Popup.CloseOnReleaseOutside
    background  :   Rectangle{
        color   :   "transparent"
    }
    visible     :   !cloud.authenticated

    contentItem :   LoginForm   {
        id      :   form
        focus   :   true
        cloud   :   loginDialog.cloud
    }
}
