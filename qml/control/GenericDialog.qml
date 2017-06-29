import QtQuick 2.0
import QtQuick.Controls 2.1

Dialog {
    x           :   (parent.width / 2) - (width / 2)
    y           :   (parent.height / 2) - (height / 2)
    modal       :   true
    closePolicy :   Popup.CloseOnEscape | Popup.CloseOnPressOutside
}
