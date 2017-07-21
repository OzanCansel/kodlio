import QtQuick 2.0
import QtQuick.Controls 2.2
import "../singleton"

Flickable {

    //Readonly
    readonly property real  logoOpacity :   0.05
    readonly property real  logoWidth   :   0.4

    //Alias
    property alias  textArea        :   textArea
    property alias  verticalScroll  :   verticalScrollBar
    property bool   modified        :   false

    id                  :   flickable
    flickableDirection  :   Flickable.VerticalFlick

    TextArea.flickable  :   TextArea    {
        id                  :   textArea
        persistentSelection :   true
        selectByKeyboard    :   true
        selectByMouse       :   true
        selectionColor      :   "lightsteelblue"

        background      :   Rectangle   {
            id          :   editorBackground
            radius      :   0
            color       :   Theme.editorBackgroundColor

            Image {
                id              :   kodlioLogo
                height          :   parent.height * logoWidth
                anchors.centerIn:   parent
                opacity         :   logoOpacity
                source          :   "/res/icon/logo.png"
                fillMode        :   Image.PreserveAspectFit
            }
        }
    }

    ScrollBar.vertical  :   ScrollBar   {   id  :   verticalScrollBar  }
}
