pragma Singleton
import QtQuick 2.0
import QtQuick.Controls 2.1
import Kodlio 1.0

Item {


    readonly property string    consoleInfoMessage      :   "console-info"
    readonly property string    consoleOutputMessage    :   "console-output"
    readonly property string    consoleErrorMessage     :   "console-error-message"

    property string     selectedPort        :   ""
    property Dialog     dialog              :   Dialog  { }
    property Dialog     createProjectDialog :   Dialog  { }
    property Dialog     openProjectDialog   :   Dialog  { }
    property Dialog     createNewClassDialog:   Dialog  { }
    property variant    outConsole          :   []
    property QtObject   mainContainer       :   QtObject{ }

    signal  listSerialPorts()

    function consoleInfo(output){
        message(consoleInfoMessage , [output])
    }

    function consoleStdError(output){
        message(consoleErrorMessage , [output])
    }

    function consoleStdOut(output){
        message(consoleOutputMessage , [output])
    }

    function displayMessage(str)    {
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
