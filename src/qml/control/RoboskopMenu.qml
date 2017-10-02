import QtQuick 2.7
import Kodlio 1.0
import "../"
import "../singleton"

Item {

    property Toast          toast           :   ({})
    property OutputConsole  consoleOutput   :   ({})
    property GenericProgressBar progressBar :   ({})

    id              :   container
    width           :   menu.width
    height          :   childrenRect.height

    function open(){
        menu.open()
    }

    AvrRunOptions   {
        id          :   runOpts
        board       :   "uno"
        port        :   SerialOption.option.portName
    }

    RoboskopRunner{
        id          :   roboskopRunner
        onStdErr    :   consoleOutput.errorOutput(output)
        onStdOutput :   consoleOutput.infoOutput(output)
        onInfoOutput:   consoleOutput.infoOutput(output)
        onRunSuccess:   toast.displaySuccess("Roboskop yazılımı başarıyla yüklendi.")
        onRunError  :   toast.displayError("Yükleme sırasında hata oluştu !")
        onProgress  :   progressBar.progress = progress
    }

    S4ARunner{
        id          :   scratchRunner
        onStdErr    :   consoleOutput.errorOutput(output)
        onStdOutput :   consoleOutput.infoOutput(output)
        onInfoOutput:   consoleOutput.infoOutput(output)
        onRunSuccess:   toast.displaySuccess("Scratch yazılımı başarıyla yüklendi.")
        onRunError  :   toast.displayError("Yükleme sırasında hata oluştu !")
        onProgress  :   progressBar.progress = progress
    }

    RoboskopToolchainThread{
        id          :   roboskopRunnerThread
        runner      :   roboskopRunner
    }

    RoboskopToolchainThread{
        id          :   scratchRunnerThread
        runner      :   scratchRunner
    }

    Item    {
        id                          :   headerContainer
        width                       :   parent.width
        height                      :   40
        visible                     :   menu.visible

        Text {
            id                      :   userNameText
            text                    :   "Yazılım"
            anchors.centerIn        :   parent
            z                       :   2
            color                   :   "white"
            font.family             :   FontCollection.menuFont
            font.bold               :   true
        }

        Rectangle   {
            id                      :   back
            anchors.fill            :   parent
            color                   :   "#ffa500"
            radius                  :   10
            anchors.bottomMargin    :   -radius
        }
    }

    GenericMenu {

        id          :   menu
        y           :   headerContainer.height
        height      :   30

        GenericMenuItem    {
            id              :   uploadRoboskopFirmware
            text            :   "Roboskop yazılımını yükle"
            tooltipEnabled  :   true
            tooltipText     :   "Roboskop yazılımını yüklemek için tıklayınız"
            height          :   30
            onClicked       :   {
                if(roboskopRunner.busy){
                    toast.displayWarning("Lütfen işlemin bitmesini bekleyiniz.")
                    return;
                }
                roboskopRunnerThread.run(runOpts)
            }
        }

        GenericMenuItem {
            id              :   scratchFirmware
            text            :   "Scratch yazılımını yükle"
            tooltipEnabled  :   true
            tooltipText     :   "Scratch yazılımını yüklemek için lütfen tıklayınız"
            height          :   30
            onClicked       :   {
                if(scratchRunner.busy){
                    toast.displayWarning("Lütfen işlemin bitmesini bekleyiniz")
                    return;
                }

                scratchRunnerThread.run(runOpts)
            }
        }
    }
}
