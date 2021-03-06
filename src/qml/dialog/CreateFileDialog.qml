import QtQuick 2.0
import QtQuick.Controls 2.1
import  "../form"
import "../singleton"

Dialog {

    property string basePath    :   ""
    property bool   createDir   :   false

    id          :   dialog
    x           :   (parent.width / 2) - (width / 2)
    y           :   (parent.height / 2) - (height / 2)
    modal       :   true
    closePolicy :   Popup.CloseOnEscape | Popup.CloseOnReleaseOutside

    contentItem :   CreateFileForm{
        basePath        :   dialog.basePath
        createDir       :   dialog.createDir
        onFileCreated   :   dialog.close()
        onFolderCreated :   dialog.close()
    }
    background  :   Image{
        source      :   "/res/icon/backgroundpattern.png"
        fillMode    :   Image.Tile
    }
}
