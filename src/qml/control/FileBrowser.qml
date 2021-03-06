import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.3
import Kodlio 1.0
import "../singleton"

TreeView {

    property string     rootPath    :   ""
    id                  :   treeView


    headerVisible       :   false
    backgroundVisible   :   false
    rootIndex           :   tree.rootIndex
    model               :   tree.model
    selectionMode       :   SelectionMode.SingleSelection
    selection           :   ItemSelectionModel {
        model: tree.model
    }

    onRootIndexChanged  :   console.log("Root index cnhaged to -> " + tree.fileName(treeView.rootIndex))
    onCurrentIndexChanged   :   console.log("Curr idx => " + tree.fileName(currentIndex))

    onRootPathChanged   :   {
        selection.clearSelection()
        selection.clearCurrentIndex()
    }

    signal  dirRightClicked(string path , variant mouse);

    function    getFileInfo(idx){
        return tree.fileName(idx)
    }

    FileTree    {
        id          :   tree
        rootPath    :   treeView.rootPath
    }

    TableViewColumn {
        title       :   "Name"
        role        :   "fileName"
    }

    FileInfo{
        id      :   info
    }

    itemDelegate    :   Rectangle{
        color       :   styleData.selected ? "lightsteelblue" : "transparent"
        Text {
            id              :   txt
            elide           :   styleData.elideMode
            text            :   styleData.value
            font.pointSize  :   11
            font.family     :   FontCollection.fileTreeFont
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: {
            var index = parent.indexAt(mouse.x, mouse.y)
            if (index.valid) {
                var file = getFileInfo(index)
                treeView.dirRightClicked(file , mouse)
            }else{
                treeView.dirRightClicked(rootPath , mouse)
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
