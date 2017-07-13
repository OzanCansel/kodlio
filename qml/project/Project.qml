import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Kodlio 1.0
import "../control"
import "../editor"
import "../singleton"

Item {

    property string     projectName         :   fInfo.dirName()
    property string     projectRoot         :   "/home/arnes/Documents/toolchain-example"
    property variant    openedDocuments     :   []
    property Compiler   compiler            :   ({})
    property variant    allowedExtensions   :   []

    property alias  documentContainer       :   documents
    property alias  headerControls          :   documentTabs
    property alias  documentsContainer      :   documents
    property alias  browser                 :   fileBrowser
    property alias  documentNumerator       :   docNumerator

    function openDocument(){
        //Virtual
    }

    function closeDocument(identity){
        var docInfo =   getDocInfo(identity)
        var idx     =   openedDocuments.indexOf(docInfo)

        //Eger bulunamadiysa
        if(idx < 0) {
            console.log("Dokuman bulunamadi")
        }

        docInfo.document.destroy()  //Acik olan dokuman kapatiliyor
        docInfo.header.destroy()    //Header siliniyor
        openedDocuments.splice(idx , 1) //Listeden siliniyor

        var lastIdx = openedDocuments.length - 1;

        //Focus ayarlaniyor
        selectDocument(openedDocuments[idx].identity)
    }

    function checkHeadersIndex(){

        //Acik document yoksa
        if(openedDocuments.length === 0)
            return


        //Eger headerlardan hepsinde focus varsa
        for(var i = 0; i < openedDocuments.length; i++){
            if(openedDocuments[i].header.checked)
                return // geri donuluyor
        }

        //Hicbiri secilmemisse otomatik olarak seciliyor
        selectDocument(openedDocuments[0].identity)
    }

    function getDocument(path){
        for(var i = 0; i < openedDocuments; i++){
            var doc = openedDocuments[i]
            if(doc.filePath === path)
                return doc.document
        }
    }

    function getDocInfo(identity){
        for(var i = 0; i < openedDocuments.length; i++)
            if(openedDocuments[i].identity === identity)
                return openedDocuments[i]
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
                closeDocument(doc.document.identity)
            }
        }
    }

    function saveCurrentDocument(){
        for(var i =0 ; i < openedDocuments.length; i++){
            var doc = openedDocuments[i]

            //Kaydediliyor
            if(doc.header.selected){
                doc.document.save()
            }
        }
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

    function selectDocument(identity){
        for(var i = 0; i < openedDocuments.length; i++){
            if(openedDocuments[i].identity === identity){
                openedDocuments[i].header.checked = true
            }
        }
    }

    function openCurrentlySelectedFile(){
        var path = fileBrowser.getFileInfo(fileBrowser.currentIndex)
        openDocument(path)
    }

    FileInfo{
        id      :   fInfo
        file    :   projectRoot
    }

    DocumentNumerator{
        id      :   docNumerator
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
                id              :   emptyDoc
                width           :   parent.width
                height          :   parent.height
                visible         :   documents.count <= 1
                projectOpened   :   projectRoot !== ""
            }
        }
    }

    Shortcut{
        id          :   closeTabShortcut
        sequence    :   "Ctrl+W"
        context     :   Qt.ApplicationShortcut
        onActivated :   {
            closeCurrentDocument()
        }
    }


    Shortcut    {
        id                  :   saveShortcut
        sequence            :   StandardKey.Save
        onActivated         :   saveCurrentDocument()
    }
}
