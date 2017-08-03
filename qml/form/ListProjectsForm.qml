import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import Kodlio 1.0
import "../singleton"
import "../control"

Item {

    property string     projName    :   ""
    property string     content     :   ""
    property variant    sourceFilesInf :   []
    property ProjectManager manager :   ({})
    property Cloud          cloudApi:   ({})

    function    retrieve(){
        projectModel.clear()
        var projects = cloudApi.myProjects()

        for(var i = 0; i < projects.length ; i++){
            projectModel.append({ "name" : projects[i]})
        }
    }

    signal      closeForm();
    signal      deleteProject(string name)

    ListModel{
        id      :   projectModel
    }

    ProjectOptions{
        id              :   opts
    }

    FileDialog{
        id              :   createProjectDialog
        title           :   "Klasör seçiniz..."
        folder          :   shortcuts.documents
        selectFolder    :   true
        selectMultiple  :   false
        onAccepted      :   {
            var projectRoot = Common.extractPathFromUrl(createProjectDialog.folder.toString()) + "/" + projName
            cloudApi.downloadSources(projName , projectRoot)
            opts.root = projectRoot
            manager.openProject(opts)
        }
    }

    GenericMessageDialog{
        id      :   deleteProjectDialog
        title   :   "Projeyi Sil"
        message :    projectsList.currentIndex > 0 ? "'" + projectModel.get(projectsList.currentIndex).name + "'isimli projeyi silmek istediğinize emin misiniz ?" : ""
        standardButtons :   StandardButton.Yes | StandardButton.No
        onAccepted  :   {
            var projName = projectModel.get(projectsList.currentIndex).name
            cloudApi.deleteProject(projName)
            retrieve()
        }
    }

    ListView{
        anchors.fill            :   parent

        id                      :   projectsList
        model                   :   projectModel
        keyNavigationWraps      :   true
        z                       :   2
        clip                    :   true

        header      :    Item{
            height      :   60
            width       :   projectsList.width

            Text {
                id                  :   projectsHeaderText
                text                :   qsTr("Projelerim")
                font.family         :   FontCollection.titleFont
                anchors.centerIn    :   parent
                color               :   "white"
                font.pixelSize      :   30
                font.bold           :   true
                z                   :   2
            }

            Rectangle{
                id                  :   back
                anchors.fill        :   parent
                color               :   "#075688"
                opacity             :   0.6
            }
        }

        delegate:   Item    {
            width   :   projectsList.width
            height  :   50
            scale   :   ListView.view.currentIndex === index ? 1.5 : 1

            Text{
                id              :   projName
                font.pointSize  :   12
                color           :   "white"
                text            :   name
                anchors.centerIn:   parent
            }
            MouseArea{
                anchors.fill    :   parent
                onClicked       :   projectsList.currentIndex = index
            }

            Behavior on scale{
                SmoothedAnimation{  velocity    :   2 }
            }
        }

        populate                :   Transition{
            NumberAnimation{
                properties  :   "y"
            }
        }

        highlight                   :  Rectangle{   color : "steelblue" }
    }

    Item {
        id  :   viewIsEmpty
        anchors.top     :   projectsList.top
        anchors.bottom  :   projectsList.bottom
        anchors.right   :   projectsList.right
        anchors.left    :   projectsList.left
        z               :   3
        visible         :   projectsList.count === 0

        Text {
            id      :   emptyText
            text    :   qsTr("Henüz bir proje yüklemediniz.")
            font.pointSize  :   24
            color   :   "white"
            anchors.centerIn    :   parent
        }
    }

    Row {
        anchors.bottom  :   parent.bottom
        anchors.right   :   parent.right
        anchors.rightMargin :   10
        anchors.bottomMargin:   10
        spacing         :   10
        z               :   2

        GenericButton{
            width       :   80
            height      :   40
            text        :   "Yenile"
            onClicked   :   retrieve()
        }

        GenericButton{
            width       :   80
            height      :   40
            text        :   "Aç"
            onClicked   :   {
                if(projectsList.count === 0)
                    return

                var name = projectModel.get(projectsList.currentIndex).name;

                if(manager.projectName === name){
                    cloudApi.downloadSources(name , manager.projectRoot)
                } else {
                    projName = name
                    createProjectDialog.open()
                }

                closeForm()
            }
        }

        GenericButton{
            width       :   80
            height      :   40
            text        :   "Sil"
            onClicked   :   {

                if(projectsList.count === 0)
                    return

                deleteProjectDialog.open()
            }
        }
    }

    Image {
        id          :   img
        source      :   "/res/icon/backgroundpattern.png"
        fillMode    :   Image.Tile
        z           :   0
        anchors.fill:   parent
    }


    Connections{
        target      :   createProjectDialog
        onAccepted  :   {
            deleteProjectDialog.open()
        }
    }
}
