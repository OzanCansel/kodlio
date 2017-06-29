import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../singleton"

TreeView {

    TableViewColumn {
        title: "Name"
        role: "fileName"
        width: 300
    }

    itemDelegate    :   Rectangle{
        color       :   styleData.selected ? "lightsteelblue" : "transparent"
        Text {
            id      :   txt
            elide   :   styleData.elideMode
            text    :   styleData.value
        }
    }

    rowDelegate     :   Rectangle{
        color       :   "transparent"
    }

    Rectangle{
        anchors.fill    :   parent
        color           :   "green"
        z               :   -1
        radius          :   10
        border.width    :   1
    }

    headerVisible       :   false
    backgroundVisible   :   false


    rootIndex   :   projectManager.rootIndex
    model       :   projectManager.projectFsModel

}
