import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.folderlistmodel 2.1
import QtQuick.Window 2.2
import Kodlio 1.0
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
    visibility      :   fullscreenButton.checked ? Window.FullScreen : Window.Windowed
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

    Connections {
        target              :   compileControlBar
        onCompileRequired   :   {
            currentProject.saveAll()
            currentProject.compile()
        }
        onUploadRequired    :   currentProject.run()
    }

    onClosing   :   {
        console.log("Closing")
        Qt.quit()
    }


    //Dialogs
    LoginDialog{
        id      :   loginDialog
        cloud   :   cloudApi
        toast   :   mainToast
    }

    ListProjectsDialog{
        id      :   listProjectsDialog
        manager :   projectManager
        cloudApi:   cloudApi
    }

    SettingsDialog{
        id          :   settingsDialog
    }

    LibrariesDialog {
        id          :   libraryManagerDialog
        libManager  :   libManager
    }

    ExamplesDialog{
        id              :   examplesDialog
        manager         :   projectManager
        options         :   projectOptions
        libraryManager  :   libManager
    }

    SerialMonitorDialog{
        id      :   serialMonitorDialog
    }

    CreateNewClassDialog{
        id      :   createNewClassDialog
    }


    CreateProjectDialog {
        id      :   createProjectDialog
        manager :   projectManager
        options :   projectOptions
    }

    GenericMessageDialog{
        id              :   quitAppDialog
        title           :   "Uygulamayı kapat"
        message         :   "Uygulamayı kapatmak istediğinize emin misiniz ?"
        onAccepted      :   Qt.quit()
        standardButtons :   StandardButton.Yes | StandardButton.No
    }

    GenericMessageDialog    {
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
        message         :   "Projeyi yüklemek istediğinize emin misiniz ?"
        onAccepted      :   {
            if(cloudApi.projectUploadBusy){
                mainToast.displayError("Su anda baska bir yukleme mevcut")
            }
            else{
                cloudApi.uploadProjectV2(projectManager.projectRoot)
            }
        }
    }

    //Backend objects
    ProjectOptions{
        id      :   projectOptions
    }

    ArduinoProjectManager{
        id                  :   projectManager
        onProjectCreateError:   mainToast.displayError(error)
    }

    Cloud   {
        id      :   cloudApi
    }

    background  :   Image   {
        id          :   img
        source      :   "/res/icon/backgroundpattern.png"
        fillMode    :   Image.Tile
        width       :   app.width
        height      :   app.height
        z           :   0
    }

    ArduinoLibManager{
        id                  :   libManager
    }

    CloudMenu {
        id              :   cloudMenu
        cloud           :   cloudApi
        dialogContainer :   parent
        x               :   110
        y               :   235
        z               :   2
        toast           :   mainToast
        onLogout        :   cloudApi.logout()
        onUploadProject :   {
            //Internet baglantisi yoksa
            if(!cloudApi.hasInternetAccess){
                mainToast.displayWarning("Internet baglantisi yok.")
                return
            }

            if(projectManager.projectOpened)
                uploadProjectDialog.open()
            else
                mainToast.displayWarning("Yuklemek icin once projeyi aciniz")
        }
        onListProjects  :   listProjectsDialog.open()
    }

    RoboskopMenu{
        id              :   roboskopMenu
        x               :   110
        y               :   350
        z               :   2
        toast           :   mainToast
        consoleOutput   :   outputConsole
        progressBar     :   compileProgressBar
    }

    FileMenu{
        id              :   fileMenu
        x               :   110
        y               :   15
        z               :   2
        onCreateProject :   createProjectDialog.open()
        onOpenProject   :   projectManager.projectRoot = projectRoot
        onOpenExamples  :   examplesDialog.open()
    }

    Item {

        anchors.fill        :   parent
        anchors.topMargin   :   5

        ToolImageButton {
            id                  :   fullscreenButton
            checkable           :   true
            src                 :   checked ? "/res/icon/full-screen-activated.png" : "/res/icon/full-screen-not-activated.png"
            anchors.right       :   parent.right
            anchors.rightMargin :   10
            anchors.top         :   parent.top
            anchors.topMargin   :   5
            z                   :   2
            highlighted         :   false
            ToolTip.visible     :   hovered
            ToolTip.text        :   checked ? "Tam Ekrandan Çık (F11)" : "Tam Ekran (F11)"
        }

        Row {

            anchors.fill        :   parent

            Item    {

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
                            mouseArea.onClicked :   fileMenu.menu.open()
                            tooltipEnabled      :   true
                            tooltipText         :   "Proje ilgili işlemler için tıklayınız"
                        }

                        IdeMenuItem{
                            id                  :   serialMonitor
                            img.source          :   "/res/icon/serial-monitor.png"
                            width               :   parent.width
                            height              :   50
                            txt.text            :   "İletişim"
                            mouseArea.onClicked :   serialMonitorDialog.open()
                            tooltipEnabled      :   true
                            tooltipText         :   "Seri portu açmak için tıklayınız"
                        }

                        IdeMenuItem {
                            id                  :   examplesMenuItem
                            img.source          :   "/res/icon/examples.png"
                            width               :   parent.width
                            height              :   50
                            txt.text            :   "Örnekler"
                            mouseArea.onClicked :   examplesDialog.open()
                            tooltipEnabled      :   true
                            tooltipText         :   "Hazır örneklere göz atmak için tıklayınız"
                        }

                        IdeMenuItem {
                            id                  :   serialPorts
                            img.source          :   "/res/icon/ports.png"
                            width               :   parent.width
                            height              :   50
                            txt.text            :   "Portlar"
                            mouseArea.onClicked :   serialPortPopup.open()
                            tooltipEnabled      :   true
                            tooltipText         :   "Bilgisayara bağlı arduino işlemcileri için tıklayınız"
                        }

                        IdeMenuItem{
                            id                  :   libraryMan
                            img.source          :   "/res/icon/library.png"
                            width               :   parent.width
                            height              :   50
                            txt.text            :   "Kutuphaneler"
                            mouseArea.onClicked :   libraryManagerDialog.open()
                            tooltipEnabled      :   true
                            tooltipText         :   "Kütüphanelere göz atmak için tıklayınız"
                        }

                        IdeMenuItem{
                            id                  :   cloudMenuItem
                            img.source          :   "/res/icon/cloud-icon-2.png"
                            width               :   parent.width
                            height              :   50
                            txt.text            :   "Bulut"
                            mouseArea.onClicked :   cloudApi.authenticated ? cloudMenu.open() : loginDialog.open()
                            tooltipEnabled      :   true
                            tooltipText         :   "Bulut işlemleri için tıklayınız"
                        }

                        IdeMenuItem{
                            id                  :   roboskopMenuItem
                            img.source          :   "/res/icon/roboskop-icon.png"
                            width               :   parent.width
                            height              :   50
                            mouseArea.onClicked :   roboskopMenu.open()
                            tooltipEnabled      :    true
                            tooltipText         :   "Roboskop yazılımı ile ilgili işlemler için tıklayınız."
                            visible             :   true
                        }

                        IdeMenuItem{
                            id                  :   settingsMenuItem
                            img.source          :   "/res/icon/settings.png"
                            width               :   parent.width
                            height              :   50
                            txt.text            :   "Ayarlar"
                            mouseArea.onClicked :   settingsDialog.open()
                            tooltipEnabled      :   true
                            tooltipText         :   "Ayarlar için tıklayınız."
                        }

                        IdeMenuItem{
                            id                  :   close
                            img.source          :   "/res/icon/shutdown-icon.png"
                            width               :   parent.width
                            height              :   50
                            mouseArea.onClicked :   quitAppDialog.open()
                            txt.text            :   "Çıkış"
                            tooltipEnabled      :   true
                            tooltipText         :   "Programdan çıkmak için tıklayınız"
                        }
                    }

                    ProjectMenu {
                        id              :   projectMenu
                        visible         :   false
                        width           :   150
                        x               :   newFile.x + newFile.width + 10
                        y               :   newFile.y + 10

                        onOpenProjectRequired   :   {
                            projectManager.projectRoot = projectPath
                        }

                        onCreateProjectRequired :   {
                            createProjectDialog.open()
                        }
                    }

                    Popup   {
                        id              :   serialPortPopup
                        contentWidth    :   serialPortListF.width
                        contentHeight   :   serialPortListF.height
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
                            //                            implicitWidth   :   150

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

                //            CloudStateControl{
                //                z                   :   5
                //                anchors.right       :   parent.right
                //                anchors.rightMargin :   10
                //                height              :   50

                //                onLoginClicked      :   {
                //                    loginDialog.open()
                //                    loginDialog.focus = true
                //                }
                //                onLogoutClicked     :   {
                //                    logoutDialog.open()
                //                }
                //                onListProjectsRequired  :      {
                //                    listProjectsDialog.open()
                //                    listProjectsDialog.contentItem.retrieve()
                //                }
                //                onUploadClicked     :   {
                //                    //
                //                    uploadProjectDialog.open()
                //                }
                //            }

                Item{

                    anchors.top         :   parent.top
                    anchors.bottom      :   outputConsole.top
                    anchors.left        :   parent.left
                    anchors.right       :   parent.right
                    anchors.topMargin   :   15
                    z                   :   4

                    Rectangle {
                        id              :   editorOverride
                        anchors.fill    :   parent
                        z               :   3
                        color           :   "transparent"

                        ArduinoProject  {
                            id                      :   currentProject
                            libManager              :   libManager
                            onShowToast             :   mainToast.displayMessage(msg)
                            onShowError             :   mainToast.displayError(msg)
                            onShowWarning           :   mainToast.displayWarning(msg)
                            consoleOut              :   outputConsole
                            anchors.fill            :   parent
                            anchors.leftMargin      :   Theme.controlXMargin
                            anchors.rightMargin     :   Theme.controlXMargin
                            progress                :   compileProgressBar
                            projectRoot             :   projectManager.projectRoot
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
                    id                      :   compileProgressBar
                    width                   :   200
                    height                  :   50
                    anchors.right           :   outputConsole.right
                    anchors.rightMargin     :   Theme.internalControlsMargin * 2
                    anchors.bottom          :   outputConsole.bottom
                    anchors.bottomMargin    :   Theme.internalControlsMargin * 2
                    z                       :   5
                    visible                 :   false
                    header                  :   "Derleme"
                }
            }

            Toast{
                id              :   mainToast
                container       :   parent
                textColor       :   "white"

                Component.onCompleted   : {
                    Global.toast = mainToast
                }
            }
        }
    }

    Connections{
        target      :   cloudApi
        onProjectUploadProgress :   {
            //  <progress>
            if(!compileProgressBar.visible)    compileProgressBar.visible = true
            compileProgressBar.header   =   "Yükle"
            compileProgressBar.progress   = progress
        }
    }

    Connections {
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
