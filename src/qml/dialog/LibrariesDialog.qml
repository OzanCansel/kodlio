import QtQuick 2.0
import Kodlio 1.0
import "../control"
import "../form"

GenericDialog {

    property ArduinoLibManager      libManager  :   ({})

    id          :   dialog
    width       :   form.implicitWidth
    height      :   form.implicitHeight

    contentItem :  LibraryManagerForm  {
        id          :   form
        libManager  :   dialog.libManager
    }

    background      :    Rectangle{
        color           :   "transparent"
        radius          :   15
        clip            :   true

        Image   {
            source      :   "/res/icon/backgroundpattern.png"
            fillMode    :   Image.Tile
            anchors.fill:   parent
        }
    }
}
