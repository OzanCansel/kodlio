import QtQuick 2.7
import "../singleton"

Item {

    property string     selectedPort    :   getCurrentPortName()
    property variant    ports           :   SerialOption.scanner.ports

    function refresh(){
        SerialOption.scanner.refresh()

        for(var i = 0; i < ports.length; i++){
            console.log(ports[i])
        }
    }

    id              :   form
    width           :   120
    height          :   200

    Item    {
        id                          :   headerContainer
        width                       :   parent.width
        height                      :   40

        Text {
            id                      :   userNameText
            text                    :   "Portlar"
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

    ListView    {

        id          :   serialPortList
        width       :   parent.width
        height      :   parent.height
        anchors.top :   headerContainer.bottom
        model       :   ports

        onCurrentItemChanged    :   {
            SerialOption.option.portName = currentIndex >= 0 ? ports[currentIndex].portName : ""
        }

        delegate:       Item    {
            height  :   30
            width   :   parent.width

            Text {
                id                  :   portNameText
                text                :   ">" + ports[index].portName
                anchors.centerIn    :   parent
                z                   :   2
                color               :   "black"
            }

            MouseArea{
                id              :   area
                anchors.fill    :   parent
                onClicked       :   {
                    serialPortList.currentIndex = index;
                }
                hoverEnabled    :   true
                z               :   2
            }

            Rectangle{
                id          :   backRect
                anchors.fill:   parent
                color       :   area.containsMouse ? "lightsteelblue" : "white"
            }

            //            Image {
            //                id          :   img
            //                source      :   area.containsMouse || area.pressed ? "/res/icon/backgroundpattern-highlight.png" : "/res/icon/backgroundpattern.png"
            //                fillMode    :   Image.Tile
            //                anchors.fill:   parent
            //                z           :   0
            //            }
        }
    }
}
