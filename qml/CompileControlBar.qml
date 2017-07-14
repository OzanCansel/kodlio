import QtQuick 2.0
import QtQuick.Controls 2.1
import "singleton"
import "control"

Rectangle {

    color           :  "transparent"

    signal compileRequired()
    signal uploadRequired()

    Column{

        width           :   parent.width
        height          :   100
        anchors.bottom  :   parent.bottom
        anchors.bottomMargin    :   50
        spacing         :   10

        IdeMenuItem{
            mouseArea.onClicked :   {
                compileRequired()
            }
            width               :   parent.width
            height              :   48
                        color               :   Theme.compileButtonBackgroundColor
            img.source          :   "/res/icon/compile.png"
            txt.text            :   "Derle"
        }

        IdeMenuItem{
            mouseArea.onClicked :   {

                uploadRequired()

//                if(Global.selectedPort == "" || Global.selectedPort === "Seçilmedi"){
//                    Global.displayMessage("Yüklenecek portu seçmediniz.")
//                    Global.openSerialPortsList()
//                    return
//                }

//                Global.dialog.close()
            }
            width               :   parent.width
            height              :   48
                        color               :   Theme.uploadButtonBackgroundColor
            img.source          :   "/res/icon/upload.png"
            txt.text            :   "Yükle"
        }
    }
}
