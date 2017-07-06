import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Kodlio 1.0
import "../control"
import "../editor"
import "../singleton"

Item {

    property string     projectName     :   "Isim Yok"
    property string     projectRoot     :   "/home/arnes/workspace/roboskop"

    property alias  documentContainer   :   documents
    property alias  headerControls      :   documentTabs
    property alias  documentsContainer  :   documents

    function openDocument(){

    }

    function    openProject(){

    }

    function compile(){
    }

    function run(){

    }

    Item    {
        id              :   documentsContainer
        anchors.fill    :   parent

        TabBar{
            id              :   documentTabs
            width           :   parent.width
            spacing         :   5

            background      :   Item {            }

            DocumentHeader{
                x           :   50
                height      :   parent.height
                width       :   150
                text        :   "Proje -> " + projectName
                mainHeader  :   true
            }
        }


        FileBrowser{
            id                      :   fileBrowser
            z                       :   2
            width                   :   250
            anchors.top             :   documentTabs.bottom
            anchors.bottom          :   parent.bottom
            visible                 :   true
            rootPath                :   projectRoot
            rootIndex               :   tree.rootIndex
            model                   :   tree.model
        }

        StackLayout{
            id              :   documents
            anchors.top     :   documentTabs.bottom
            anchors.topMargin   :   0
            anchors.bottom  :   parent.bottom
            anchors.left    :   fileBrowser.right
            anchors.right   :   parent.right
            currentIndex    :   {
                if(documentTabs.count > 1 && documentTabs.currentIndex === 0){
                    documentTabs.currentIndex = 1
                    return 1
                }
                else
                    return documentTabs.currentIndex
            }


            EmptyDocument{
                id          :   emptyDoc
                width       :   parent.width
                height      :   parent.height
                visible     :   documents.count <= 1
            }
        }
    }
}
