import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import "../singleton"
import "../dialog"

Menu    {

    readonly property real menuItemWidth            :   menu.width - 2 * backRect.border.width
    readonly property real menuItemVertShift        :   backRect.border.width


    id              :   menu

    enter           :   Transition {
        ParallelAnimation{
            NumberAnimation{
                property    :   "opacity"; from : 0; to : 1.0
            }

            NumberAnimation{
                property        :   "height"; from : 0; to : menu.implicitHeight
            }
        }
    }

    signal  openProjectRequired(string projectPath)
    signal  createProjectRequired()

    function    extractPathFromUrl(url){
        return url.replace(/^(file:\\{2})|(file:\/{2})|(qrc:\/{2})|(qrc:\\{2})|(http:\/{2})|(http:\\{2})/,"")
    }

    background      :   Rectangle{
        id                  :   backRect
        height              :   menu.height + 2
        radius              :   5
        color               :   "transparent"
    }

    DropdownMenuItem    {
        id          :   openProject
        text        :   "Aç"
        font.family :   FontCollection.menuFont
        width       :   menuItemWidth
        onTriggered :   openProjectDialog.open()
        tooltipText :   "Projeyi açmak için tıklayınız"
        anchors.horizontalCenter    :   parent.horizontalCenter
        backItem.y  :   menuItemVertShift
        backRadius  :   backRect.radius
    }

    DropdownMenuItem    {
        id          :   createProject
        text        :   "Yeni Proje"
        font.family :   FontCollection.menuFont
        width       :   menuItemWidth
        onTriggered :   createProjectRequired()
        tooltipText :   "Yeni proje oluşturmak için tıklayınız"
        anchors.horizontalCenter    :   parent.horizontalCenter
        y           :   menuItemVertShift
        backRadius  :   backRect.radius
    }

    DropdownMenuItem    {
        id          :   saveFile
        text        :   "Kaydet"
        width       :   menuItemWidth
        font.family :   FontCollection.menuFont
        onTriggered :   projectManager.saveFile()
        tooltipText :   "Kaydetmek için tıklayınız."
        anchors.horizontalCenter    :   parent.horizontalCenter
        y           :   menuItemVertShift
        backRadius  :   backRect.radius
    }

    DropdownMenuItem{
        id          :   createNewClass
        text        :   "Yeni Sınıf Yarat"
        width       :   menuItemWidth
        font.family :   FontCollection.menuFont
        onTriggered :   Global.createNewClass()
        tooltipText :   "Yeni sınıf yaratmak için tıklayınız"
        anchors.horizontalCenter    :   parent.horizontalCenter
        y           :   menuItemVertShift
        backRadius  :   backRect.radius
        visible     :   false
    }

    FileDialog{
        id              :   openProjectDialog
        title           :   "Proje seçin"
        folder          :   shortcuts.home
        selectFolder    :   true
        selectMultiple  :   false
        onAccepted      :   {
            var path = Common.extractPathFromUrl(openProjectDialog.fileUrl.toString())
            openProjectRequired(path)
        }
    }

    FileDialog{
        id              :   createProjectDialog
        title           :   "Proje Yarat"
        folder          :   shortcuts.home
        selectFolder    :   true
        selectMultiple  :   false
        onAccepted      :   {
            var path = extractPathFromUrl(createProjectDialog.fileUrl.toString())

            createProjectRequired(path)
        }
    }

    Component{
        id      :   itemBackground
        Rectangle   {
            id                          :   backCont
            y                           :   backRect.border.width
            implicitWidth               :   menu.width - backRect.border.width * 3
            radius                      :   backRect.radius
            implicitHeight              :   40
            color                       :   Theme.dropdownMenuButtonBackColor
        }
    }

    Component{
        id      :   contentItemComp
        Text {
            id      :   name
            text    :   qsTr("text")
        }
    }
}
