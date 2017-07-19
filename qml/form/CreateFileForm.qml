import QtQuick 2.0
import Kodlio 1.0
import "../singleton"
import "../control"

Item {
    implicitHeight      :   100
    implicitWidth       :   250
    property string     basePath    :   ""

    signal  fileCreated()

    File{
        id      :   f
    }

    Column{
        id                  :   controlsColumn
        anchors.fill        :   parent
        anchors.leftMargin  :   10
        anchors.rightMargin :   10
        anchors.topMargin   :   5
        anchors.bottomMargin:   5
        spacing             :   10

        GenericTextBox{
            id              :   txt
            width           :   parent.width
            height          :   40
            placeholderText :   "Dosya ismini giriniz..."
        }

        GenericButton{
            id          :   button
            width       :   parent.width
            height      :   40
            text        :   "Oluştur"
            onClicked   :   {
                if(f.createFile(basePath + "/" + txt.text))
                    fileCreated()
            }
        }
    }
}
