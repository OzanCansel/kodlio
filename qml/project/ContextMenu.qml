import QtQuick 2.0
import QtQuick.Controls 2.2
import Kodlio 1.0
import "../control"

Menu{

    property string     filePath    :   ""

    id          :   contextMenu

    signal  createFile(string basePath)
    signal  removeFile(string basePath)
    signal  createFolder(string basePath)

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
        id          :   createDirectory
        text        :   isDir(filePath) ? "Klasör ekle" : "Dosyayı Sil"
        height      :   30
        onTriggered :   createFolder(filePath)
    }

    MenuItem{
        id          :   removeFileItem
        text        :   isDir(filePath) ? "Klasörü sil" : "Dosyayı Sil"
        height      :   30
        onTriggered :   removeFile(filePath)
    }
}
