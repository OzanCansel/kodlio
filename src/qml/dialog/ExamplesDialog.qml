import QtQuick 2.7
import QtQuick.Controls 2.1
import "../control"
import "../form"

GenericDialog {

    id              :   dialog
    onOpened        :   examplesForm.refresh()
    contentItem     :   ExamplesForm  {
        id          :   examplesForm
        onCloseMe   :   close()
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
