import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Kodlio 1.0
import "../dialog"
import "../singleton"
import "../control"
import "../editor"

Project {


    id                  :       arduinoProject
    compiler            :       avrToolchain.compiler()
    toolchain           :       avrToolchain
    watcher             :       projectWatcher
    runner              :       avrRunner
    parser              :       errParser
    allowedExtensions   :       ["cpp" , "c" , "s" , "h" , "S"]

    property ArduinoLibManager  libManager  :   ({})

    AvrErrorParser{
        id          :   errParser
        compiler    :   parent.compiler
    }

    FileInfo    {
        id      :   fInfo
    }

    AvrToolchain{
        id          :   avrToolchain
        libManager  :   arduinoProject.libManager
    }

    AvrCompileOptions   {
        id      :   options
        board   :   "uno"
    }

    AvrToolchainThread  {
        id          :   toolchainThread
        toolchain   :   avrToolchain
        runner      :   avrRunner
    }

    ArduinoProjectWatcher{
        id          :   projectWatcher
        rootDir     :   projectRoot
    }

    AvrRunOptions   {
        id          :   runOpts
        board       :   "uno"
        port        :   SerialOption.option.portName
        hexFile     :   avrToolchain.compiledHexFile
    }

    AvrRunner   {
        id          :   avrRunner
        onRunSuccess:   runOpts
        Component.onCompleted   :   {
            SerialOption.option.uploading = Qt.binding(function(){  return avrRunner.runnerState === AvrRunner.Spawning })
        }
    }

    function compile(){
        if(projectRoot === ""){
            displayWarning("Proje açılmadı.")
            return
        }

        var mainFile = projectWatcher.retrieveMainFile()
        console.log("Derleniyor " + mainFile)
        toolchainThread.compile(mainFile , options)
    }

    function run(){
        if(projectRoot === ""){
            displayWarning("Proje açılmadı.")
            return
        }

        if(runOpts.hexFile === ""){
            displayMessage("Proje derlenmedi.")
            return
        }

        if(runOpts.port === ""){
            displayMessage("Yüklenecek portu seçiniz.")
            return
        }

        toolchainThread.run(runOpts)
    }

    function openDocument(filePath){

        fInfo.file = filePath;

        //Dosya uzantisi kontrol ediliyor
        if(allowedExtensions.indexOf(fInfo.completeSuffix()) === -1)
            return

        //Eger acilmak istenen dosya klasor ise geri donuluyor
        if(!fInfo.isFile())
            return;

        //Daha once acilmissa geri donuluyor
        var docId = documentIndex(filePath)

        //Eger dokuman mevcutsa geri donuluyor
        if(docId >= 0){
            //ve dokumana gecis yapiliyor
            selectDocument(docId)
            return;
        }

        //template
        var doc = documentComponent.createObject(documentsContainer , { width : documentsContainer.width , height : documentsContainer.height , absolutePath : filePath})
        var header = arduinoDocHeader.createObject(headerControls)

        doc.identity        =   documentNumerator.generate()
        doc.width           =   documentsContainer.width
        doc.absolutePath    =   filePath
        header.implicitWidth = header.height * 3
        header.height = headerControls.height
        header.text =   Qt.binding(function(){ return doc.fileName })
        header.attachedDocument = doc;

        openedDocuments.push({ identity : doc.identity , document : doc , header : header });
        header.closeTab.connect(closeDocument)
        doc.focused.connect(selectDocument)
    }

    function documentIndex(filePath){
        for(var i = 0; i < openedDocuments.length; i++){
            var doc = openedDocuments[i].document;

            if(doc.fileInfo.filePath() === filePath){
                return doc.identity
            }
        }

        return -1
    }

    function openProject(path){

    }

    Component{
        id      :   documentComponent
        ArduinoDocument{

        }
    }

    Component{
        id      :   arduinoDocHeader
        DocumentHeader    {

        }
    }
}
