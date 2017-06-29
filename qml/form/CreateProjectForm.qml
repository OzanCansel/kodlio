import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import "../control"
import "../singleton"

Item {

    implicitHeight      :   100 + (projectFolderPathh.visible ? 25 : 0)
    implicitWidth       :   300

    readonly property string projectFolder : dialog.shortcuts.documents

    FileDialog{
        id              :   dialog
        title           :   "Klasör seçiniz"
        folder          :   shortcuts.documents
        selectFolder    :   true
        selectMultiple  :   false

        onAccepted      :   {
            projectFolder               =   dialog.fileUrl
            projectFolderPathh.visible  =   true
        }
    }

    Column  {

        anchors.fill    :   parent
        spacing         :   10
        TextField        {
            id              :   projectNameTxt
            placeholderText :   "Projenin Adını Giriniz"
            height          :   40
            width           :   parent.width
            background      :   Rectangle{
                radius      :   10
            }
        }

        Label{
            id              :   projectFolderPathh
            width           :   parent.width
            text            :   dialog.fileUrl
            color           :   "white"
            visible         :   false
        }

        Row {
            height          :   50
            width           :   parent.width
            spacing         :   10
            layoutDirection :   Qt.RightToLeft

            GenericButton{
                width       :   100
                height      :   parent.height
                text        :   "Oluştur"
                onClicked   :   {
                    var path = Common.extractPathFromUrl(projectFolder)
                    var projPath = projectManager.createProject(projectNameTxt.text , path , "İçerik yok")
                    projectManager.openProject(projPath)

                    close()
                }
            }

            GenericButton{
               width        :   100
               height       :   parent.height
               text         :   "Klasör Seç"
               onClicked    :   dialog.open()
            }
        }
    }
}
