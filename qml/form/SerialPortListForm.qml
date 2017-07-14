import QtQuick 2.0
import "../singleton"

Item {

    property string selectedPort    :   getCurrentPortName()

    signal  portSelected(string port)

    function refresh(){
        var ports = serialPort.listSerialPort()
        var selectedZero =  serialPortList.currentIndex < 1

        //Model temizleniyor
        lModel.clear()

        lModel.append({"name"   :   "Seçilmedi"})
        for(var i = 0 ; i < ports.length ; i++){
            lModel.append({"name"   :   ports[i] })
        }

        if(selectedZero){
            serialPortList.currentIndex = lModel.count - 1

            programmer.configuration.portName = osInfo.os !== "windows" ? "/dev/" + form.getCurrentPortName() : form.getCurrentPortName()
            portSelected(getCurrentPortName())
        }
    }

    function getCurrentPortName(){
        return lModel.get(serialPortList.currentIndex).name
    }

    id              :   form
    implicitHeight  :   lModel.count * 50

    ListModel{
        id      :   lModel
    }

    ListView{
        id      :   serialPortList
        width   :   parent.implicitWidth
        height  :   parent.implicitHeight

        delegate:   Item{
            height  :   50
            width   :   parent.width

            Text {
                id      :   portName
                text    :   ">" + name
                anchors.centerIn    :   parent
                z       :   2
                color   :   "white"
            }

            MouseArea{
                id              :   area
                anchors.fill    :   parent
                onClicked       :   {
                    serialPortList.currentIndex = index;
                    programmer.configuration.portName = osInfo.os !== "windows" ? "/dev/" + form.getCurrentPortName() : form.getCurrentPortName()
                    portSelected(form.getCurrentPortName())
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

        model  :   lModel
    }
}
