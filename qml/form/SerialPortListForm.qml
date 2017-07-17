import QtQuick 2.0
import "../singleton"

Item {

    property string     selectedPort    :   getCurrentPortName()
    property variant    ports           :   SerialOption.scanner.ports

    function refresh(){
        SerialOption.scanner.refresh()
    }

    id              :   form
    implicitHeight  :  ports.length * 50

    ListView    {

        id      :   serialPortList
        width   :   parent.implicitWidth
        height  :   parent.implicitHeight
        model   :   ports
        onCurrentItemChanged    :   {
            SerialOption.option.portName = currentIndex >= 0 ? ports[currentIndex].portName : ""
        }

        delegate:   Item    {
            height  :   50
            width   :   parent.width

            Text {
                id      :   portNameText
                text    :   ">" + ports[index].portName
                anchors.centerIn    :   parent
                z       :   2
                color   :   "white"
            }

            MouseArea{
                id              :   area
                anchors.fill    :   parent
                onClicked       :   {
                    serialPortList.currentIndex = index;
                    //                     SerialOption.option.portName = index >= 0 ? ports[index].portName : ""
                }
                hoverEnabled    :   true
                z               :   2
            }

            Image {
                id          :   img
                source      :   area.containsMouse || area.pressed ? "/res/icon/backgroundpattern-highlight.png" : "/res/icon/backgroundpattern.png"
                fillMode    :   Image.Tile
                anchors.fill:   parent
                z           :   0
            }
        }

        highlight   :   Rectangle   {
            color   :   "steelblue"
            radius  :   4
            border.width    :   1
        }
    }
}
