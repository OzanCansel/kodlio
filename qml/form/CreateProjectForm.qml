import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import Kodlio 1.0
import "../control"
import "../singleton"

Item {

    property ProjectManager manager :   ({})
    property ProjectOptions options :   ({})

    implicitHeight      :   100 + (projectFolderPath.visible ? 25 : 0)
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
            projectFolderPath.visible   =   true
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
            id              :   projectFolderPath
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
                    options.root = Common.extractPathFromUrl(projectFolder)
                    options.projectName = projectNameTxt.text
                    manager.createProject(options)
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
