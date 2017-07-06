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

    FileTree{
        id          :   tree
        rootPath    :   treeView.rootPath
    }

    TableViewColumn {
        title   :   "Name"
        role    :   "fileName"
        width   :   300
    }

    itemDelegate    :   Rectangle{
        color       :   styleData.selected ? "lightsteelblue" : "transparent"
        Text {
            id      :   txt
            elide   :   styleData.elideMode
            text    :   styleData.value
        }
    }

    onCurrentIndexChanged   :   console.log(treeView.currentIndex)

    onDoubleClicked           :   {
        console.log(tree.fileName(treeView.currentIndex))
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
