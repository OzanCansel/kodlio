import QtQuick 2.0
import QtQuick.Controls 2.1
import "../form"
import "../singleton"

Dialog {

    signal      loginRequired(string uName , string passwd)

    id          :   serialMonitorDialog
    width       :   parent.width * 0.8
    height      :   parent.height * 0.8
    x           :   parent.width / 2 - (width / 2)
    y           :   parent.height / 2 - (height / 2)
    modal       :   true
    closePolicy :   Popup.CloseOnEscape | Popup.CloseOnReleaseOutside
    background  :          Image {
        id          :   img
        source      :   "/res/icon/serialmonitor-background-pattern.png"
        fillMode    :   Image.Tile
    }

    contentItem :   SerialMonitorForm{
        id      :   form
        isOpen  :   serialMonitorDialog.visible
    }
}
