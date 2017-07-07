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
    property variant    openDocuments   :   []

    property alias  documentContainer   :   documents
    property alias  headerControls      :   documentTabs
    property alias  documentsContainer  :   documents
    property alias  browser             :   browser

    function openDocument(){
    }

    function closeDocument(filePath){
        var docInfo = getDocumentInfo(filePath)
        var idx = openDocuments.indexOf(docInfo)

        docInfo.document.destroy()  //Acik olan dokuman kapatiliyor
        docInfo.header.destroy()    //Header siliniyor
        openDocuments.splice(idx , 1) //Listeden siliniyor
    }

    function getDocument(path){
        for(var i = 0; i < openDocuments; i++){
            var doc = openDocuments[i]
            if(doc.filePath === path)
                return doc.document
        }
    }

    function getDocumentInfo(path){
        for(var i = 0; i < openDocuments.length; i++){
            var doc = openDocuments[i]
            if(doc.filePath === path)
                return doc
        }
    }


    function getHeader(path){
        for(var i = 0; i < openDocuments; i++){
            var doc = openDocuments[i]
            if(doc.filePath === path)
                return doc.header
        }
    }

    function closeCurrentDocument(){
        if(documentTabs.currentIndex > 0){
            documentTabs.currentItem.destroy()
            documents.itemAt(documents.currentIndex).destroy()
        }
    }

    function    openProject(){

    }

    function compile(){

    }

    function run(){

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
                text        :   "Proje -> " + projectName
                mainHeader  :   true
            }
        }


        FileBrowser {
            id                      :   fileBrowser
            z                       :   2
            width                   :   250
            anchors.top             :   documentTabs.bottom
            anchors.bottom          :   parent.bottom
            visible                 :   true
            rootPath                :   projectRoot
            onDoubleClicked         :   {
                var path = fileBrowser.getFileName(currentIndex)
                openDocument(path)
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

            EmptyDocument{
                id          :   emptyDoc
                width       :   parent.width
                height      :   parent.height
                visible     :   documents.count <= 1
            }
        }
    }

    Shortcut{
        id          :   closeTabShortcut
        sequence    :   ["Ctrl+W" , StandardKey.Close]
        context     :   Qt.ApplicationShortcut
        onActivated :   {
            closeCurrentDocument()
        }
    }
}
