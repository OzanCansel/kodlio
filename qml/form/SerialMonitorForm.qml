import QtQuick 2.0
import QtQuick.Controls 2.1
import "../singleton"
import "../control"

Item {

    function connect(port) {
        var connected = serialPort.connectToArduino(port)

        if(connected){
            outputInfo("\"" +  port + "\" ile bağlantı kuruldu.")
        }else{
            outputInfo("\"" +  port + "\" ile bağlantı kurulamadı.")
        }
    }

    function send(txt){
        arduinoOut(txt)
        serialPort.send(txt)
    }

    function    outputInfo(text){
        arduinoIncome.append("<span style=\"color: " + Theme.serialMonitorInfo + ";font-size: 11pt;\"><b>$    </b> </span>" +
                             "<span style=\"color: " + Theme.serialMonitorInfo + "; font-size: 11pt;\"><b>"  + text + "    </b></span>")
    }

    function    arduinoOut(text){
        arduinoIncome.append("<span style=\"color: " +  Theme.serialMonitorOut+ ";font-size: 12pt;\"><b>&rarr;    </b></span>" +
                             "<span style=\"color: " + Theme.serialMonitorOut + "; font-size: 11pt;\"><b>"  + text + "    </b></span>")
    }

    function    arduinoIn(text){
        arduinoIncome.append("<span style=\"color: " + Theme.serialMonitorIn + "; font-size: 12pt;\"><b>&larr;    </b></span>" +
                             "<span style=\"color: " + Theme.serialMonitorIn + "; font-size: 11pt;\"><b>"  + text + "    </b></span>")
    }

    function    clear(){
        arduinoIncome.clear()
    }

    ListModel{
        id          :   comboboxItems
        ListElement{    value :   "yazi"; key   :   "Yazı"}
        ListElement{    value :   "binary"; key :   "İkilik"}
        ListElement{    value :   "hex";  key   :   "On Altılık"}
        ListElement{    value :   "number"; key :   "Sayı"}
    }

    id              :   form

    Item{
        id                  :   controls
        width               :   parent.width
        height              :   50

        TextField           {
            id              :   send
            anchors.left    :   parent.left
            anchors.right   :   sendButton.left
            anchors.top     :   parent.top
            anchors.bottom  :   parent.bottom
            anchors.rightMargin :   Theme.internalControlsMargin

            Keys.onEnterPressed :   {
                form.send(send.text)
                send.clear()
            }

            Keys.onReturnPressed:   {
                form.send(send.text)
                send.clear()
            }
        }

        GenericCombobox{
            id              :   sendType
            width           :   120
            height          :   50
            anchors.right   :   sendButton.left
            anchors.top     :   parent.top
            anchors.bottom  :   parent.bottom
            anchors.rightMargin :   Theme.internalControlsMargin
            model           :    comboboxItems
            visible         :   false
        }

        GenericButton{
            id              :   sendButton
            width           :   120
            height          :   50
            text            :   "Gönder"
            anchors.right   :   reconnectbutton.left
            anchors.rightMargin :   Theme.internalControlsMargin
            onClicked       :   {
                form.send(send.text)
                send.clear()
            }
        }

        GenericButton{
            id              :   reconnectbutton
            width           :   120
            height          :   parent.height
            text            :   "Bağlan"
            anchors.right   :   parent.right
            onClicked       :   {
                serialPort.open(Global.selectedPort)
            }
        }
    }

    Flickable   {

        id                  :   consoleFlickable
        anchors.top         :   controls.bottom
        anchors.left        :   parent.left
        anchors.right       :   parent.right
        anchors.bottom      :   parent.bottom
        anchors.topMargin   :   Theme.internalControlsMargin

        TextArea.flickable  :   TextArea    {
            id              :   arduinoIncome
            selectByKeyboard:   true
            selectByMouse   :   true
            font.pointSize  :   11
            wrapMode        :   TextArea.Wrap
            textFormat      :   TextArea.RichText
            color           :   "white"

            background      :   Rectangle{
                width           :   consoleFlickable.width
                height          :   consoleFlickable.height
                radius          :   2
                color           :   "#024037"
                opacity         :   0.7
                border.width    :   1
            }

            onTextChanged   :   {
                if(arduinoIncome.length > 4000){
                    arduinoIncome.text = arduinoIncome.text.substring(arduinoIncome.length - 4000 , arduinoIncome.length)
                }
            }

            readOnly        :   true
            text            :   ""
        }

        ScrollBar.vertical  :   ScrollBar   {   }
    }

    Connections {
        target          :   serialPort
        onTextIncome    :   {
            //<text>
            arduinoIn(text)
        }
    }
}
