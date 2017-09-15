import QtQuick 2.0
import QtQuick.Controls 2.1
import "../control"

Item {
    property string     label       :   "Label"
    property color      textColor   :   "white"
    property real       value       :   spinner.value
    property real       min         :   0
    property real       max         :   1

    id                  :   ctl

    Row{
        id              :   row
        z               :   2
        anchors.fill    :   parent
        anchors.leftMargin      :   15
        anchors.rightMargin     :   15
        anchors.topMargin       :   ctl.height * 0.07
        anchors.bottomMargin    :   ctl.height * 0.07
        Item {
            id          :   labelCont
            width       :   parent.width * 0.5 - (row.spacing / 2)
            height      :   parent.height
            Text {
                id          :   lbl
                text        :   label
                color       :   textColor
                anchors.verticalCenter  :   parent.verticalCenter
            }
        }

        GenericSpinner{
            id          :   spinner
            width       :   parent.width * 0.5 - (row.spacing / 2)
            height      :   parent.height * 0.9
            anchors.verticalCenter  :   parent.verticalCenter
            value       :   ctl.value
            from        :   min
            to          :   max
        }
    }

    Rectangle{
        width           :   parent.width
        height          :   parent.height
        color           :   "#006f98"
        opacity         :   0.3
    }

    Component.onCompleted: {
        ctl.value   =   Qt.binding(function() {
            return spinner.value })
    }
}
