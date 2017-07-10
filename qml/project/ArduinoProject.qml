import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Kodlio 1.0
import "../control"
import "../editor"

Project {

    FileInfo{
        id      :   file
    }

    function openDocument(filePath){

        file.file = filePath;

        //Eger acilmak istenen dosya klasor ise geri donuluyor
        if(!file.isFile())
            return;

        //Daha once acilmissa geri donuluyor
        var docIdx = documentIndex(filePath)

        //Eger dokuman mevcutsa geri donuluyor
        if(docIdx >= 0){
            //ve dokumana gecis yapiliyor
            selectDocument(docIdx)
            return;
        }

        //template
        var doc = documentComponent.createObject(documentsContainer , { width : documentsContainer.width , height : documentsContainer.height , absolutePath : filePath})
        var header = arduinoDocHeader.createObject(headerControls)

        doc.width           =   documentsContainer.width
        doc.height          =   documentsContainer.height
        doc.absolutePath    =   filePath
        header.implicitWidth = header.height * 3
        header.height = headerControls.height
        header.text =   Qt.binding(function(){ return doc.fileName })
        header.attachedDocument = doc;

        openedDocuments.push({ document : doc , header : header   });
        header.closeTab.connect(closeDocument)
    }

    function documentIndex(filePath){
        for(var i = 0; i < openedDocuments.length; i++){
            var doc = openedDocuments[i].document;

            if(doc.fileInfo.filePath() === filePath){
                return i
            }
        }

        return -1
    }

    function openProject(path){

    }

    function compile(){
        //template
    }

    function run(){
        //
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
