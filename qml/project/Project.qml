import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Kodlio 1.0
import "../control"
import "../editor"
import "../singleton"

Item {

    property string     projectName     :   "Isim Yok"
    property string     projectRoot     :   "/home/arnes/workspace/roboskop"
    property variant    openedDocuments   :   []

    property alias  documentContainer   :   documents
    property alias  headerControls      :   documentTabs
    property alias  documentsContainer  :   documents
    property alias  browser             :   fileBrowser

    function openDocument(){
        //Virtual
    }

    function closeDocument(filePath){
        var docInfo = getDocumentInfo(filePath)
        var idx = openedDocuments.indexOf(docInfo)

        //Eger bulunamadiysa
        if(idx < 0){
            console.log("Dokuman bulunamadi")
        }

        docInfo.document.destroy()  //Acik olan dokuman kapatiliyor
        docInfo.header.destroy()    //Header siliniyor
        openedDocuments.splice(idx , 1) //Listeden siliniyor
    }

    function getDocument(path){
        for(var i = 0; i < openedDocuments; i++){
            var doc = openedDocuments[i]
            if(doc.filePath === path)
                return doc.document
        }
    }

    function getDocumentInfo(path){
        for(var i = 0; i < openedDocuments.length; i++){
            var doc = openedDocuments[i]
            if(doc.document.fileInfo.filePath() === path)
                return doc
        }

        return -1
    }

    function getHeader(path){
        for(var i = 0; i < openedDocuments; i++){
            var doc = openedDocuments[i]
            if(doc.filePath === path)
                return doc.header
        }
    }

    function closeCurrentDocument(){

        for(var i =0 ; i < openedDocuments.length; i++){
            var doc = openedDocuments[i]

            if(doc.header.selected){
                closeDocument(doc.document.absolutePath)
            }
        }

//        if(documentTabs.currentIndex > 0){
//            closeDocument(documentTabs.attachedDocument.absolutePath)
//        }
    }

    function    openProject(){
        //Virtual
    }

    function compile(){
        //Virtual
    }

    function run(){
        //Virtual
    }

    function selectDocument(idx){
        documentTabs.currentIndex = idx + 1
    }

    function openCurrentlySelectedFile(){
        var path = fileBrowser.getFileInfo(fileBrowser.currentIndex)
        openDocument(path)
    }

    Item    {
        id              :   documentsContainer
        anchors.fill    :   parent

        TabBar  {
            id              :   documentTabs
            width           :   parent.width
            spacing         :   5

            background      :   Item {            }

            DocumentHeader{
                x           :   50
                height      :   parent.height
                text        :   projectName
                mainHeader  :   true
            }
        }


        FileBrowser {
            id                      :   fileBrowser
            z                       :   2
            width                   :   250
            anchors.top             :   documentTabs.bottom
            anchors.bottom          :   parent.bottom
            rootPath                :   projectRoot
            onDoubleClicked         :   {
                openCurrentlySelectedFile()
            }
            Keys.onEnterPressed     :   {
                openCurrentlySelectedFile()
            }
            Keys.onReturnPressed    :   {
                openCurrentlySelectedFile()
            }
        }

        StackLayout {
            id              :   documents
            anchors.top     :   documentTabs.bottom
            anchors.topMargin   :   0
            anchors.bottom  :   parent.bottom
            anchors.left    :   fileBrowser.right
            anchors.right   :   parent.right

            currentIndex    :   {
                if(documentTabs.count > 1 && documentTabs.currentIndex === 0){
                    documentTabs.currentIndex = 1
                    return 1
                }
                else
                    return documentTabs.currentIndex
            }

            EmptyDocument   {
                id          :   emptyDoc
                width       :   parent.width
                height      :   parent.height
                visible     :   documents.count <= 1
            }
        }
    }

    Shortcut{
        id          :   closeTabShortcut
        sequence    :   "Ctrl+W"
        context     :   Qt.ApplicationShortcut
        onActivated :   {
            console.log("Close Tab")
            closeCurrentDocument()
        }
    }
}
