import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import Kodlio 1.0
import "../animation"
import "../control"
import "../editor"
import "../singleton"
import "../dialog"
import "../"

Item {

    readonly property bool projectOpen       :   projectRoot != ""

    property string     projectName         :   fInfo.dirName()
    property string     projectRoot         :   ""
    property variant    openedDocuments     :   []
    property Compiler   compiler            :   ({})
    property Toolchain  toolchain           :   ({})
    property ProjectWatcher watcher         :   ({})
    property OutputConsole  consoleOut      :   ({})
    property Runner     runner              :   ({})
    property GenericProgressBar progress    :   ({})
    property ErrorParser    parser          :   ({})
    property variant    allowedExtensions   :   []

    property alias  documentContainer       :   documents
    property alias  headerControls          :   documentTabs
    property alias  documentsContainer      :   documents
    property alias  browser                 :   fileBrowser
    property alias  documentNumerator       :   docNumerator

    id                      :   project

    signal  showToast(string msg)
    signal  showError(string msg)
    signal  showWarning(string msg)

    onProjectRootChanged    :   {
        console.log("Root => " + projectRoot)
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

    function saveAll(){
        saveCurrentDocument()
    }

    function    displayMessage(msg){
        showToast(msg)
    }

    function    displayError(msg){
        showError(msg)
    }

    function    displayWarning(msg){
        showWarning(msg)
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

    function openCurrentlySelectedFile(idx){
        var path = fileBrowser.getFileInfo(idx)
        openDocument(path)
    }

    function    clearErrors(){
        for(var i = 0; i < openedDocuments.length; i++){
            openedDocuments[i].document.clearErrors();
            openedDocuments[i].header.hasError  =   false
        }
    }


    ContextMenu  {
        id              :   contextMenu
        z               :   10
        property string removeFilePath  :   ""
        onCreateFile    :   {
            createFileDialog.basePath = basePath
            createFileDialog.createDir = false
            createFileDialog.open()
        }
        onRemoveFile    :   {
            contextMenu.removeFilePath = basePath
            removeFileDialog.message =  basePath + " isimli dosyayı silmek istediğinize emin misiniz ?"
            removeFileDialog.open()
        }
        onRemoveFolder  :   {
            contextMenu.removeFilePath = basePath
            removeFileDialog.message =  basePath + " isimli klasörü silmek istediğinize emin misiniz ?"
            removeFileDialog.open()
        }
        onCreateFolder  :   {
            createFileDialog.basePath = basePath
            createFileDialog.createDir = true
            createFileDialog.open()
        }
    }

    GenericMessageDialog{
        id              :   removeFileDialog
        title           :   "Dosya|Klasör sil"
        onAccepted      :   {
            var success = FileSingleton.removeFile(contextMenu.removeFilePath)

            if(!success)
                toast.displayError("Dosya silinemedi.")
        }
        standardButtons :   Dialog.Yes | Dialog.No
    }

    CreateFileDialog    {
        id          :   createFileDialog
    }

    ErrorParser {
        compiler    :   project.compiler
    }

    FileInfo    {
        id              :   fInfo
        file            :   projectRoot
        onFileChanged   :   projectName = fInfo.dirName()
    }

    DocumentNumerator{
        id      :   docNumerator
    }

    Item{
        id                          :   centerPointItem
        anchors.centerIn            :   parent
    }

    Image {
        id                          :   successIcon
        source                      :   "/res/icon/success-icon.png"
        width                       :   128
        fillMode                    :   Image.PreserveAspectFit
        anchors.centerIn            :   centerPointItem
        z                           :   5
    }

    Image {
        id                          :   uploadIconImg
        source                      :   "/res/icon/upload-animation.png"
        width                       :   128
        fillMode                    :   Image.PreserveAspectFit
        anchors.centerIn            :   centerPointItem
        z                           :   5
    }

    Image{
        id                          :   compileErrorIcon
        source                      :   "/res/icon/compile-error.png"
        width                       :   128
        fillMode                    :   Image.PreserveAspectFit
        anchors.centerIn            :   centerPointItem
        z                           :   5
    }

    Image{
        id                          :   runErrorIcon
        source                      :   "/res/icon/run-error.png"
        width                       :   128
        fillMode                    :   Image.PreserveAspectFit
        anchors.centerIn            :   centerPointItem
        z                           :   5
    }

    Item    {

        id              :   documentsContainer
        anchors.fill    :   parent

        TabBar  {
            id              :   documentTabs
            width           :   parent.width
            spacing         :   5

            background      :   Item {            }

            DocumentHeader  {
                x           :   50
                height      :   parent.height
                text        :   projectOpen ? projectName : "Proje Açılmadı"
                mainHeader  :   true
            }
        }

        SplitView   {
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
                rootPath                :   projectRoot
                Layout.minimumWidth     :   projectOpen ? Math.min(300 , splitView.width / 5) : 0
                visible                 :   projectOpen

                onDirRightClicked   :   {
                    //<path>
                    var point = browser.mapToItem(project , mouse.x , mouse.y)
                    contextMenu.x       =   point.x
                    contextMenu.y       =   point.y
                    contextMenu.filePath = path
                    contextMenu.open()
                }

                onDoubleClicked         :   {
                    openCurrentlySelectedFile(index)
                }
                Keys.onEnterPressed     :   {
                    openCurrentlySelectedFile()
                }
                Keys.onReturnPressed    :   {
                    openCurrentlySelectedFile()
                }

                Behavior on width {
                    SmoothedAnimation{
                        velocity    :   splitView.width / 4
                    }
                }
            }

            Item {
                id          :   layout
                height      :   parent.height
                Layout.minimumWidth :   400

                GenericEditorMenu   {
                    id                  :   editorMenu
                    anchors.right       :   parent.right
                    anchors.top         :   parent.top
                    z                   :   5
                    currentDocument     :   documents.itemAt(documents.currentIndex)
                    visible             :   documents.anyDocumentOpened
                }

                StackLayout {
                    id                  :   documents
                    anchors.fill        :   parent
                    readonly property bool anyDocumentOpened :   documents.count > 1
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

    Shortcut{
        id          :   closeAllShortcut
        sequence    :   "Ctrl+Shift+W"
        context     :   Qt.ApplicationShortcut
        onActivated :   {
            while(openedDocuments.length > 0)
                closeCurrentDocument()
        }
    }

    Shortcut{
        id          :   transitionShortcut
        sequence    :   "Ctrl+Tab"
        context     :   Qt.ApplicationShortcut
        onActivated :   {
            if(documentTabs.count <= 1)
                return
            if(documentTabs.currentIndex >= (documentTabs.count - 1))
                documentTabs.currentIndex = 0
            else
                documentTabs.incrementCurrentIndex()
        }
    }


    Shortcut    {
        id                  :   saveShortcut
        sequence            :   StandardKey.Save
        onActivated         :   saveCurrentDocument()
    }

    //Animations
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

    ShowAndFadeAnimation{
        id              :   compileSuccessAnimation
        animationTarget :   successIcon
    }

    ShowAndFadeAnimation{
        id              :   runSuccessAnimation
        animationTarget :   uploadIconImg
    }

    ShowAndFadeAnimation{
        id              :   runErrorAnimation
        animationTarget :   runErrorIcon
    }

    ShowAndFadeAnimation{
        id              :   compileErrorAnimation
        animationTarget :   compileErrorIcon
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
        onProgress      :   progress.progress = value
        onCompileSuccess:   compileSuccessAnimation.restart()
        onCompileError  :   compileErrorAnimation.restart()
        onBuildStarted  :   clearErrors()
    }

    Connections{
        target          :   compiler
    }

    Connections{
        target              :   runner
        onInfoOutput        :   consoleOut.infoOutput(output)
        onStdOutput         :   consoleOut.standartOutput(output)
        onStdErr            :   consoleOut.errorOutput(output)
        onCommandOutput     :   consoleOut.commandOutput(output)
        onRunSuccess        :   runSuccessAnimation.restart()
        onRunError          :   runErrorAnimation.restart()
    }

    Connections{
        target                  :   parser
        onErrorOccurred         :   {
            //<error>.file .row .column .message
            console.log("Err -> " + error.message)
            var     sourcePath  =   error.file
            var     docInfo     =   getDocumentInfo(sourcePath)
            var isProjectSource =   sourcePath.indexOf(projectRoot) > -1

            //Eger dokuman bulunduysa
            if(docInfo !== -1){
                docInfo.document.error(error)
            }   else    {
                openDocument(sourcePath)
                docInfo = getDocumentInfo(sourcePath)
            }

            docInfo.document.error(error)
            docInfo.header.hasError = true
            if(!isProjectSource)    docInfo.document.isReadOnly = true;
        }
    }
}
