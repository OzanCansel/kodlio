import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0 as NativeDialog

import "../qml"
import "control"
import "form"

Rectangle{

    id              :   appMenu
    color           :   Theme.panelHeadersBackgroundColor
    height          :   70



    signal  openProjectRequired(string projectPath)
    signal  createProjectRequired(string folderPath)
    signal  showLoginFormRequired()
    signal  logoutRequired()
    signal  listProjectsRequired()

    function    extractPathFromUrl(url){
        return url.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/,"")
    }

    NativeDialog.FolderDialog{
        id              :   openFileDialog
        title           :   "Klasör Seçin"
        acceptLabel     :   "Seç"
        rejectLabel     :   "İptal"

        onAccepted  :   {
            openProjectRequired(extractPathFromUrl( openFileDialog.folder.toString() ))
        }
    }

    NativeDialog.FileDialog{
        id              :   createFolderDialog
        title           :   "Proje İsmini Giriniz"
        acceptLabel     :   "Seç"
        rejectLabel     :   "İptal"
        fileMode        :   NativeDialog.FileDialog.SaveFile
        modality        :   Qt.NonModal

        onAccepted      :   {
            var path = createFolderDialog.file.toString();
            createProjectRequired(extractPathFromUrl(path))
        }
    }

    Row {
        id                  :   buttons
        height              :   parent.height
        spacing             :   10
        anchors.top         :   parent.top
        anchors.topMargin   :   15
        anchors.left        :   parent.left
        anchors.leftMargin  :   15

        Rectangle{
            width           :   70
            height          :   parent.height
            color           :   "#335B96"
            border.width    :   1
            opacity         :   0
            visible         :   false

            Image {
                id          :   name
                width       :   parent.width * 0.8
                source      :   "/res/icon/roboskop-logo.png"
                smooth      :   true
                fillMode    :   Image.PreserveAspectFit
                anchors.centerIn    :   parent
            }
        }

        Button  {
            id          :   fileButton
            width       :   150
            height      :   40
            text        :   "Dosya"

            onClicked: menu.open()

            Menu{

                id      :   menu
                y       :   40

                MenuItem {
                    text            : "Yeni..."
                    onTriggered     :   createFolderDialog.open()
                    onClicked       :   createFolderDialog.open()
                }

                MenuItem {
                    text: "Aç..."
                    onTriggered     :   openFileDialog.open()
                    onClicked       :   openFileDialog.open()
                }

                MenuItem {
                    text: "Kaydet"
                }
            }
        }

        Button{
            id          :   ports
            height      :   40
            width       :   150
            text        :   "Seri Portlar"
            onClicked   :   serialPortListF.visible = !serialPortListF.visible

            SerialPortListForm{
                id      :   serialPortListF
                width   :   150
                y       :   ports.height
                visible :   false

                onPortSelected  :   {
                    ports.text  = serialPortListF.selectedPort
                    serialPortListF.visible =   false
                }

                Component.onCompleted   :  {
                    serialPortListF.refresh()
                }

                Keys.onEscapePressed    :   {
                }
            }
        }
    }

    CloudStateControl{
        anchors.right       :   parent.right
        anchors.rightMargin :   10
        anchors.top         :   parent.top
        anchors.topMargin   :   10

        onLoginClicked      :   {
            showLoginFormRequired()
        }

        onLogoutClicked     :   {
            logoutRequired()
        }
        onUploadClicked     :   {
        }
        onListProjectsRequired: {
            appMenu.listProjectsRequired()
        }
    }
}
