import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Kodlio 1.0
import "../singleton"

TreeView {

    property string     rootPath    :   ""

    id          :   treeView


    headerVisible       :   false
    backgroundVisible   :   false
    rootIndex           :   tree.rootIndex
    model               :   tree.model

    signal  dirRightClicked(string path);

    function    getFileInfo(idx){
        return tree.fileName(idx)
    }

    FileTree    {
        id          :   tree
        rootPath    :   treeView.rootPath
    }

    TableViewColumn {
        title   :   "Name"
        role    :   "fileName"
    }

    FileInfo{
        id      :   info
    }

    itemDelegate    :   Rectangle{
        color       :   styleData.selected ? "lightsteelblue" : "transparent"
        Text {
            id          :   txt
            elide       :   styleData.elideMode
            text        :   styleData.value
            font.family :   FontCollection.fileTreeFont
        }
    }

    MouseArea {
         anchors.fill: parent
         acceptedButtons: Qt.RightButton
         onClicked: {
             var index = parent.indexAt(mouse.x, mouse.y)
             if (index.valid) {
                 var file = getFileInfo(index)
                 info.file = file
                 if(info.isDir())
                     dirRightClicked(file)
                 console.log("show context menu for row: " + getFileInfo(index))
             }
         }
     }

    rowDelegate     :   Rectangle{
        color       :   "transparent"
    }

    Rectangle{
        anchors.fill    :   parent
        color           :   "white"
        z               :   -1
        border.width    :   1
    }
}
