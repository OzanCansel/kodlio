import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import Kodlio 1.0
import "../animation"
import "../control"
import "../editor"
import "../singleton"
import "../"

Item {

    property string     projectName         :   fInfo.dirName()
    property string     projectRoot         :   "/home/arnes/Documents/toolchain-example"
    property variant    openedDocuments     :   []
    property Compiler   compiler            :   ({})
    property Toolchain  toolchain           :   ({})
    property ProjectWatcher watcher         :   ({})
    property OutputConsole  consoleOut      :   ({})
    property Runner     runner              :   ({})
    property variant    allowedExtensions   :   []

    property alias  documentContainer       :   documents
    property alias  headerControls          :   documentTabs
    property alias  documentsContainer      :   documents
    property alias  browser                 :   fileBrowser
    property alias  documentNumerator       :   docNumerator

    onProjectRootChanged    :   {
        while(openedDocuments.length > 0)
            closeCurrentDocument()
    }

    function compile(){
        //Virtual
    }

    function openDocument(){
        //Virtual
    }

    function closeDocument(identity){
        var docInfo =   getDocInfo(identity)
        var idx     =   openedDocuments.indexOf(docInfo)

        //Eger bulunamadiysa
        if(idx < 0) {
            console.log("Dokuman bulunamadi")

            return
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


    RunAnimation{
        z           :   3
        x           :   parent.width / 2 - width / 2
        y           :   parent.height / 2 - height / 2
        rotation    :   135
    }
    FileInfo{
        id              :   fInfo
        file            :   projectRoot
        onFileChanged   :   projectName = fInfo.dirName()
    }

    DocumentNumerator{
        id      :   docNumerator
    }

    Image {
        id      :   successIcon
        source  :   "/res/icon/success-icon.png"
        width   :   128
        fillMode:   Image.PreserveAspectFit
        visible :   compileSuccesAnimation2.running
        x       :   documentsContainer.width * 0.45
        opacity :   compileSuccesAnimation2.running ? 1 : 0
        z       :   5
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

        SplitView{
            id      :   splitView
            anchors.top     :   documentTabs.bottom
            anchors.bottom  :   parent.bottom
            anchors.left    :   parent.left
            anchors.right   :   parent.right


            FileBrowser {
                id                      :   fileBrowser
                z                       :   2
                anchors.top             :   parent.top
                anchors.bottom          :   parent.bottom
                width                   :   250
                rootPath                :   projectRoot
                Layout.minimumWidth     :   200

                onDoubleClicked         :   {
                    openCurrentlySelectedFile()
                }
                onClicked               :   {
                    console.log("clicked")
                }

                Keys.onEnterPressed     :   {
                    openCurrentlySelectedFile()
                }
                Keys.onReturnPressed    :   {
                    openCurrentlySelectedFile()
                }
            }

            StackLayout {
                id                  :   documents
                anchors.top         :   parent.top
                anchors.bottom      :   parent.bottom
                Layout.minimumWidth :   400

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
    }

    //Kisayol
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

    SequentialAnimation{

        id          :   compileSuccesAnimation2

        ScriptAction{
            script  :   {
                successIcon.opacity = 1
            }
        }

        NumberAnimation {
            target      :   successIcon
            property    :   "y"
            from        :   documents.height * 0.1
            to          :   documents.height * 0.5
            duration    :   850
            easing.type : Easing.OutBounce
        }


        NumberAnimation {
            target      :   successIcon
            property    :   "opacity"
            duration    :   500
            from        :   1
            to          :   0
            easing.type: Easing.InOutQuad
        }
    }

    Connections{
        target  :   compiler
        onCommandOutput :   console.log("Project : " + output)
        onInfoOutput    :   {
            Global.consoleInfo(output)
        }
    }

    Connections {

        target          :   toolchain

        onInfoOutput    :   consoleOut.infoOutput(output)
        onStdOutput     :   consoleOut.standartOutput(output)
        onStdError      :   consoleOut.errorOutput(output)
        onCommandOutput :   consoleOut.commandOutput(output)
        onCompileSuccess:   {

            console.log("compile success")
            compileSuccesAnimation2.restart()
        }
    }

    Connections{
        target              :   runner
        onInfoOutput        :   consoleOut.infoOutput(output)
        onStdOutput         :   consoleOut.standartOutput(output)
        onStdErr            :   consoleOut.errorOutput(output)
        onCommandOutput     :   consoleOut.commandOutput(output)
        onSuccessfullyRan   :   compileSuccesAnimation2.restart()
    }
}
