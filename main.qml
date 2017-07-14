import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.folderlistmodel 2.1
import QtQuick.Window 2.2
import "qml"
import "qml/singleton"
import "qml/dialog"
import "qml/control"
import "qml/form"
import "qml/editor"
import "qml/project"

ApplicationWindow {
    id              :   app
    visible         :   true
    width           :   Math.max(1024 , height * 16 / 9)
    height          :   Math.max(768 , Screen.desktopAvailableHeight * 0.75)
    visibility      :   Window.Windowed
    title           :   qsTr("Kodlio")

    Component.onCompleted   :   {
        serialPort.setDebugEnabled(true)
        Global.dialog               =   serialMonitorDialog
        Global.createProjectDialog  =   createProjectDialog
        Global.createNewClassDialog =   createNewClassDialog
        Global.mainContainer        =   app
        Global.outConsole           =   outputConsole
    }

    Connections{
        target  :   Global
        onListSerialPorts   :   serialPortPopup.open()
    }

    Connections{
        target              :   compileControlBar
        onCompileRequired   :   currentProject.compile()
        onUploadRequired    :   currentProject.run()
    }

    LoginDialog{
        id      :   loginDialog
    }

    ListProjectsDialog{
        id      :   listProjectsDialog
    }

    SettingsDialog{
        id      :   settingsDialog
    }

    LibrariesDialog {
        id      :   libraryManagerDialog
    }

    ExamplesDialog{
        id      :   examplesDialog
    }

    GenericMessageDialog{
        id      :   quitAppDialog
        title   :   "Uygulamayı kapat"
        message :   "Uygulamayı kapatmak istediğinize emin misiniz ?"
        onAccepted      :   Qt.quit()
        standardButtons :   StandardButton.Yes | StandardButton.No
    }

    GenericMessageDialog{
        id              :   logoutDialog
        title           :   "Çıkış Yap"
        message         :   "'" + cloudApi.userName + "' çıkış yapmak istediğinize emin misin ?"
        onAccepted      :   {
            cloudApi.logout()
            Global.displayMessage("Çıkış yapıldı.")
        }
        standardButtons :   StandardButton.Yes | StandardButton.No
    }

    GenericMessageDialog{
        id              :   uploadProjectDialog
        title           :   "Proje Yükle"
        standardButtons :   StandardButton.Yes | StandardButton.No
        message         :   "'" + projectManager.projectName + "' isimli projeyi yüklemek istediğinize emin misiniz ?"
        onAccepted      :   {
            var projname = fileSys.projectName(fileSys.workingDirectory());
            var src = fileSys.mainFileContent();

            var res = cloudApi.uploadProjectV2(projname , fileSys.workingDirectory());

            if(res)
                Global.displayMessage("Proje başarıyla yüklendi.")
            else
                Global.displayMessage("Proje yüklenirken hata oluştu !")
        }
    }

    SerialMonitorDialog{
        id      :   serialMonitorDialog
    }

    CreateProjectDialog{
        id      :   createProjectDialog
    }

    CreateNewClassDialog{
        id      :   createNewClassDialog
    }


    background  :
        Image {
        id          :   img
        source      :   "/res/icon/backgroundpattern.png"
        fillMode    :   Image.Tile
        width       :   app.width
        height      :   app.height
        z           :   0
    }

    Row {

        anchors.fill        :   parent
        anchors.topMargin   :   5

        Item{

            id          :   compileControlsContainer
            height      :   parent.height -  26
            anchors.verticalCenter  :   parent.verticalCenter
            width       :   120
            z           :   2

            Item{
                width       :   parent.width
                height      :   50
                x           :   10
                y           :   -7

                Image {
                    id              :   logo
                    source          :   "/res/icon/logo.png"
                    anchors.fill    :   parent
                    anchors.margins :   parent.height * 0.05
                    fillMode        :   Image.PreserveAspectFit
                    z               :   2
                    visible         :   false
                }

                Rectangle{
                    id      :   back
                    anchors.fill    :   parent
                    radius  :   height / 2
                    color   :   "white"
                    opacity :   1
                    visible :   false
                }
            }

            Rectangle {

                anchors.fill    :   parent
                anchors.leftMargin  :   5
                anchors.topMargin   :   -9
                anchors.bottomMargin:   -8
                radius          :   10
                border.width    :   0
                color           :   "transparent"


                Column  {
                    y                       :   10
                    anchors.horizontalCenter :   parent.horizontalCenter
                    width                   :   parent.width * 0.8
                    spacing                 :   5

                    IdeMenuItem{
                        id                  :   newFile
                        img.source          :   "/res/icon/cog.png"
                        width               :   parent.width
                        height              :   50
                        txt.text            :   "Ekle"
                        mouseArea.onClicked :   projectMenu.open()
                    }

                    IdeMenuItem{
                        id                  :   serialMonitor
                        img.source          :   "/res/icon/serial-monitor.png"
                        width               :   parent.width
                        height              :   50
                        txt.text            :   "İletişim"
                        mouseArea.onClicked :   serialMonitorDialog.open()
                    }

                    IdeMenuItem {
                        id                  :   examplesMenuItem
                        img.source          :   "/res/icon/examples.png"
                        width               :   parent.width
                        height              :   50
                        txt.text            :   "Örnekler"
                        mouseArea.onClicked :   examplesDialog.open()
                    }

                    IdeMenuItem {
                        id                  :   serialPorts
                        img.source          :   "/res/icon/ports.png"
                        width               :   parent.width
                        height              :   50
                        txt.text            :   "Portlar"
                        mouseArea.onClicked :   serialPortPopup.open()
                    }

                    IdeMenuItem{
                        id                  :   libraryMan
                        img.source          :   "/res/icon/library.png"
                        width               :   parent.width
                        height              :   50
                        txt.text            :   "Kutuphaneler"
                        mouseArea.onClicked :   libraryManagerDialog.open()
                    }

                    IdeMenuItem{
                        id                  :   settingsMenuItem
                        img.source          :   "/res/icon/settings.png"
                        width               :   parent.width
                        height              :   50
                        txt.text            :   "Ayarlar"
                        mouseArea.onClicked :   settingsDialog.open()
                    }

                    IdeMenuItem{
                        id                  :   close
                        img.source          :   "/res/icon/shutdown-icon.png"
                        width               :   parent.width
                        height              :   50
                        mouseArea.onClicked :   quitAppDialog.open()
                        txt.text            :   "Çıkış"
                    }
                }

                ProjectMenu {
                    id              :   projectMenu
                    visible         :   false
                    width           :   150
                    //                    height          :   200
                    x               :   newFile.x + newFile.width + 10
                    y               :   newFile.y + 10

                    onOpenProjectRequired   :   {
                        currentProject.projectRoot = projectPath
                    }

                    onCreateProjectRequired :   {

                    }
                }

                Popup   {
                    id              :   serialPortPopup
                    contentWidth    :   serialPortListF.implicitWidth
                    contentHeight   :   serialPortListF.implicitHeight
                    x               :   serialPorts.x + serialPorts.width + 10
                    y               :   serialPorts.y + 10
                    background      :   Item{  }
                    contentItem     :   Column{ }
                    padding         :   0
                    clip            :   true
                    enter           :   Transition{
                        ParallelAnimation{
                            NumberAnimation{
                                property    :   "opacity"; from : 0; to : 1.0
                            }

                            NumberAnimation{
                                property        :   "height"; from : 0; to : serialPortPopup.contentHeight
                            }
                        }
                    }

                    onAboutToShow       :   {
                        if(serialPortListF.selectedPort === "Seçilmedi" || serialPortListF.selectedPort === "")
                            serialPortListF.refresh()
                    }

                    SerialPortListForm  {
                        id              :   serialPortListF
                        implicitWidth   :   150

                        onPortSelected  :   {
                            serialPortPopup.close()
                            Global.selectedPort = serialPortListF.selectedPort
                        }

                        Keys.onEscapePressed    :   {
                        }

                        Component.onCompleted   :   refresh()
                    }
                }

                Rectangle{
                    width           :   parent.width *  0.8
                    anchors.horizontalCenter    :   parent.horizontalCenter
                    height          :   1
                    color           :   "black"
                    anchors.bottom  :   compileControlBar.top
                    visible         :   false
                }

                CompileControlBar   {
                    id                          :   compileControlBar
                    height                      :   180
                    width                       :   parent.width * 0.8
                    anchors.bottom              :   parent.bottom
                    anchors.bottomMargin        :   58
                    anchors.horizontalCenter    :   parent.horizontalCenter
                }
            }
        }

        Item    {
            id                      :   it
            height                  :   parent.height
            width                   :   parent.width - compileControlsContainer.width
            z                       :   10

            CloudStateControl{
                z                   :   5
                anchors.right       :   parent.right
                anchors.rightMargin :   10
                height              :   50

                onLoginClicked      :   {
                    loginDialog.open()
                    loginDialog.focus = true
                }
                onLogoutClicked     :   {
                    logoutDialog.open()
                }
                onListProjectsRequired  :      {
                    listProjectsDialog.open()
                    listProjectsDialog.contentItem.retrieve()
                }
                onUploadClicked     :   {
                    //
                    uploadProjectDialog.open()
                }
            }

            Item{

                anchors.top         :   parent.top
                anchors.bottom      :   outputConsole.top
                anchors.left        :   parent.left
                anchors.right       :   parent.right
                anchors.topMargin   :   15
                z               :   4

                Rectangle {
                    id              :   editorOverride
                    anchors.fill    :   parent
                    z               :   3
                    color           :   "transparent"

                    ArduinoProject  {
                        id                      :   currentProject
                        consoleOut              :   outputConsole
                        anchors.fill            :   parent
                        anchors.leftMargin      :   Theme.controlXMargin
                        anchors.rightMargin     :   Theme.controlXMargin
                    }
                }
            }

            OutputConsole{
                id                  :   outputConsole
                width               :   parent.width
                height              :   20
                anchors.bottom      :   parent.bottom
            }

            GenericProgressBar{
                id      :   compileProgressBar
                width   :   200
                height  :   50
                anchors.right           :   outputConsole.right
                anchors.rightMargin     :   Theme.internalControlsMargin * 2
                anchors.bottom          :   outputConsole.bottom
                anchors.bottomMargin    :   Theme.internalControlsMargin * 2
                z               :   5
                visible         :   false
                header          :   "Derleme"
            }
        }

        Toast{
            id              :   toast
            container       :   parent
            textColor       :   "white"

            Component.onCompleted   : {
                Global.toast = toast
            }
        }
    }

    Connections{
        target                      :   projectManager
        onProjectOpened             :   {
        }
        onCompilerStandardOutput    :   {
            //<output>
            //outputConsole.standartOutput(output)
        }
        onCompilerErrorOutput       :   {
            //<output>
            outputConsole.errorOutput(output)
        }
    }

    Connections{
        target      :   toolchain
        onCompileProgress   :   {
            //<progress>
            if(!compileProgressBar.visible) compileProgressBar.visible = true
            compileProgressBar.header = "Derle"
            compileProgressBar.progress = progress
            progressBarHideout.restart()
        }
        onStdOutput :   {
            //<output>
            outputConsole.commandOutput(output)
        }
    }

    Connections{
        target      :   cloudApi
        onProjectUploadProgress :   {
            //  <progress>
            if(!compileProgressBar.visible)    compileProgressBar.visible = true
            compileProgressBar.header   =   "Yükle"
            compileProgressBar.progress   = progress
            progressBarHideout.restart()
        }
    }


    Timer{
        id      :   progressBarHideout
        interval:   2000
        onTriggered :   {
            compileProgressBar.visible  =   false
            compileProgressBar.progress =   0
        }
    }

    Connections{
        target                      :   compiler
        onCommandOutput             :   {
            //  <text>
            //outputConsole.commandOutput(text)
        }
        onStdOutput             :   {
            // <text>
            //outputConsole.standartOutput(text)
        }
        onStdError              :   {
            //  <text>
            outputConsole.errorOutput(text)
        }
    }

    Connections{
        target                      :   programmer
        onCommandOutput             :   {
            //<text>
            outputConsole.commandOutput(text)
        }
        onStdOutput                 :   {
            //<text>
            outputConsole.standartOutput(text)
        }
        onStdError                  :   {
            //<text>
            outputConsole.errorOutput(text)
        }
    }

    Connections{
        target      :       cloudApi
        onStdOutput :   {
            //<out>
            outputConsole.standartOutput(out)
        }
        onStdError  :   {
            //<err>
            outputConsole.errorOutput(err)
        }
        onCommandOutput :   {
            //<out>
            outputConsole.commandOutput(out)
        }
    }
}
