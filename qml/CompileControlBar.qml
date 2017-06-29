import QtQuick 2.0
import QtQuick.Controls 2.1
import "singleton"
import "control"

Rectangle {

    color           :  "transparent"

    Column{

        width           :   parent.width
        height          :   100
        anchors.bottom  :   parent.bottom
        anchors.bottomMargin    :   50
        spacing         :   10

        IdeMenuItem{
            mouseArea.onClicked :   {
                projectManager.saveFile()
                projectManager.compileProject()
            }
            width               :   parent.width
            height              :   48
                        color               :   Theme.compileButtonBackgroundColor
            img.source          :   "/res/icon/compile.png"
            txt.text            :   "Derle"
        }

        IdeMenuItem{
            mouseArea.onClicked :   {

                if(Global.selectedPort == "" || Global.selectedPort === "Seçilmedi"){
                    Global.displayMessage("Yüklenecek portu seçmediniz.")
                    Global.openSerialPortsList()
                    return
                }

                projectManager.saveFile()
                projectManager.compileAndUploadProject("")
                Global.dialog.close()
            }
            width               :   parent.width
            height              :   48
                        color               :   Theme.uploadButtonBackgroundColor
            img.source          :   "/res/icon/upload.png"
            txt.text            :   "Yükle"
        }
    }
}
