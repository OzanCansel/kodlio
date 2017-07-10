import QtQuick 2.7
import "../singleton"

Item {

    id              :   it
    property color color    :   Theme.ideMenuItemBackColor
    property alias  mouseArea   :   area
    property alias  img         :   icon
    property alias  txt         :   txt
    property alias  backgroundRect  :   backRect

    scale   :   area.containsMouse ? 1.1 : 1

    Behavior on scale{
        NumberAnimation{
            duration    :   100
        }
    }

    states  :   [
        State{
            name    :   "hover";    when : area.containsMouse
            PropertyChanges {
                target  :   it
                color   :   Theme.ideMenuItemHoverBackColor
            }
        }
    ]

    Rectangle{
        id              :   backRect
        anchors.fill    :   parent
        radius          :   5
        opacity         :   1
        color           :   it.color
    }

    Row{


        anchors.fill    :   parent

        Item{
            width       :   parent.width
            height      :   parent.height

            Image{
                id                  :   icon
                fillMode            :   Image.PreserveAspectFit
                anchors.centerIn    :   parent
                width               :   parent.height * 0.7
            }
        }

        Text {
            id              :   txt
            text            :   qsTr("text")
            font.pointSize  :   11
            font.family     :   FontCollection.menuFont
            width           :   parent.width * 0.6
            anchors.verticalCenter  :   parent.verticalCenter
            color           :   "white"
            visible         :   false
        }

    }

    MouseArea{
        id                  :   area
        anchors.fill        :   parent
        hoverEnabled        :   true
    }
}
