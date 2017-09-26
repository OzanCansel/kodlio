import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import Kodlio 1.0
import "../singleton"

Item {

    property alias  menu            :   menu

    signal  createProject()
    signal  openProject(string projectRoot)
    signal  openExamples()

    width                           :   menu.width
    height                          :   childrenRect.height

    Item    {
        id                          :   headerContainer
        width                       :   parent.width
        height                      :   30
        visible                     :   menu.visible

        Text {
            id                      :   headerText
            text                    :   "Dosya"
            anchors.centerIn        :   parent
            z                       :   2
            color                   :   "white"
            font.family             :   FontCollection.menuFont
            font.bold               :   true
        }

        Rectangle{
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

        GenericMenuItem     {
            id              :   openProjectItem
            text            :   "Projeyi Ac"
            tooltipEnabled  :   true
            tooltipText     :   "Projeyi açmak için tıklayınız"
            onTriggered     :   openProjectDialog.open()
        }

        GenericMenuItem     {
            id              :   createProjectItem
            text            :   "Proje Olustur"
            tooltipEnabled  :   true
            tooltipText     :   "Yeni proje olusturmak icin tiklayiniz"
            onTriggered     :   createProject()
        }

        GenericMenuItem{
            id              :   openExamplesItem
            text            :   "Örnekleri Aç"
            tooltipEnabled  :   true
            tooltipText     :   "Örnekleri açmak için tıklayınız"
            onTriggered     :   openExamples()
        }
    }

    FileDialog{
        id                  :   openProjectDialog
        title               :   "Acmak istediginiz projeyi seciniz"
        folder              :   shortcuts.documents + "/kodlio"
        selectFolder        :   true
        selectMultiple      :   false
        onAccepted          :   {
            var path = Common.extractPathFromUrl(openProjectDialog.fileUrl.toString())
            openProject(path)
        }
    }
}
