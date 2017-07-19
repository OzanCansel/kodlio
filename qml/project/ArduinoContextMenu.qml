import QtQuick 2.0
import QtQuick.Controls 2.2
import Kodlio 1.0

Menu{

    property string     filePath    :   ""

    id          :   contextMenu

    signal  createFile(string basePath)

    enter           :   Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
    }

    function    isDir(path) {
        fInfo.setFile(path)
        return fInfo.isDir()
    }

    FileInfo    {
        id      :   fInfo
        file    :   contextMenu.filePath
    }

    MenuItem    {
        id          :   createFileItem
        text        :   "Yeni Dosya"
        enabled     :   isDir(filePath)
        height      :   30
        onTriggered :   createFile(filePath)
    }

    MenuItem{
        id      :   removeFile
        text    :   isDir(filePath) ? "Klasörü sil" : "Dosyayı Sil"
        height  :   30
    }
}
