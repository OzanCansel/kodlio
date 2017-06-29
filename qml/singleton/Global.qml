pragma Singleton
import QtQuick 2.0
import QtQuick.Controls 2.1
import Roboskop 1.0
import "../control"
import "../dialog"
import "../"

Item {

    property Toast      toast
    property string     selectedPort        :   ""
    property Dialog     dialog              :   Dialog  { }
    property Dialog     createProjectDialog :   Dialog  { }
    property Dialog     openProjectDialog   :   Dialog  { }
    property Dialog     createNewClassDialog:   Dialog  { }
    property variant    outConsole          :   []
    property QtObject   mainContainer       :   QtObject{ }

    signal  listSerialPorts()

    function displayMessage(str){
        if(toast)   {
            toast.displayMessage(str)
        }
    }

    function serialMonitorEnabled(enabled){
        dialog.close()
    }

    function createProject(){
        createProjectDialog.open()
    }

    function consoleStandartOutput(output){
        outConsole.commandOutput(output)
    }

    function consoleErrorOutput(output){
        outConsole.errorOutput(output)
    }

    function consoleCommandOutput(output){
        outConsole.standartOutput(output)
    }

    function createNewClass(){
        createNewClassDialog.open()
    }

    function openProject(){
        openProjectDialog.open()
    }

    function openSerialPortsList(){
        listSerialPorts()
    }
}
