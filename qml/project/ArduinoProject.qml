import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../control"
import "../editor"

Project {

    function openDocument(someth){
        //template
        var doc = documentComponent.createObject(documentsContainer , { width : documentsContainer.width , height : documentsContainer.height , absolutePath : someth})
        var header = arduinoDocHeader.createObject(headerControls)

        doc.width           =   documentsContainer.width
        doc.height          =   documentsContainer.height
        doc.absolutePath    =   someth
        header.implicitWidth = header.height * 3
        header.height = headerControls.height
        header.text =   Qt.binding(function(){ return doc.fileName })
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
