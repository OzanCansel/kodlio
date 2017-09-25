import QtQuick 2.7
import QtQuick.Controls 2.1
import Kodlio 1.0
import "../control"
import "../form"

GenericDialog {

    property ProjectManager manager         :   ({})
    property ProjectOptions options         :   ({})
    property ArduinoLibManager  libraryManager  :   ({})

    id              :   dialog
    onOpened        :   examplesForm.refresh()

    contentItem     :   ExamplesForm  {
        id          :   examplesForm
        onCloseMe   :   close()
        manager     :   dialog.manager
        options     :   dialog.options
        libraryManager  :   dialog.libraryManager
    }

    background      :    Rectangle{
        color           :   "transparent"
        radius          :   15
        clip            :   true

        Image{
            source      :   "/res/icon/backgroundpattern.png"
            fillMode    :   Image.Tile
            anchors.fill:   parent
        }
    }
}
