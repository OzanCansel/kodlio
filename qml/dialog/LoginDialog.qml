import QtQuick 2.0
import QtQuick.Controls 2.1

import "../form"

Dialog {

    signal      loginRequired(string uName , string passwd)

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

    contentItem :   LoginForm   {
        id      :   form
        focus   :   true
        onAuthenticated :   {
            if(success){
                loginDialog.close()
            }
        }
    }
}
