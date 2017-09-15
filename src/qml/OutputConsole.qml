import QtQuick 2.0
import QtQuick.Controls 2.1
import "control"
import "singleton"
import "../"

Rectangle {

    readonly property real marginRatio      :   0.02

    property bool collapsed                 :   false
    property bool   clearFlag               :   false

    id          :   consoleTextContainer
    color       :   "transparent"
    height      :   collapsed ? Theme.consoleCollapsedHeight : Theme.consoleNormalHeight

    Component.onCompleted   : {
        consoleTextContainer.height  =   Qt.binding(function(){ return collapsed ? Theme.consoleCollapsedHeight : Theme.consoleNormalHeight; })
    }

    Connections{
        target      :   eventContext
        onMessage   :   {
            if(message === EventLabels.consoleOutputMessage)
                infoOutput(args[0])
            else if(message === EventLabels.consoleErrorMessage)
                standartOutput(args[0])
            else if(message === EventLabels.consoleInfoMessage)
                standartOutput(args[0])
        }
    }

    function    checkFlags(){
        if(clearFlag){
            consoleText.clear()
            clearFlag   =   false
        }
    }

    function    infoOutput(text){
        checkFlags();
        var     texts = text.split("\n")
        for(var i = 0; i < texts.length; i++){
            consoleText.append("<span style=\"color : "  + Theme.commandOutConsoleColor + " \">" + texts[i] + "</span>")
        }
    }

    function    commandOutput(text){
        checkFlags();
        var     texts = text.split("\n")
        for(var i = 0; i < texts.length; i++){
            consoleText.append("<span style=\"color : "  + Theme.commandOutConsoleColor + " \">" + texts[i] + "</span>")
        }
    }

    function    standartOutput(text){
        checkFlags()
        var     texts = text.split("\n")
        for(var i = 0; i < texts.length; i++){
            consoleText.append("<span style=\"color : " + Theme.stdOutConsoleColor +  "\">" + texts[i] + "</span>");
        }
    }

    function    errorOutput(text){
        checkFlags()
        var     texts = text.split("\n")
        for(var i = 0; i < texts.length; i++){

            consoleText.append("<span style=\"color : " + Theme.stdErrConsoleColor + ";\">"  + texts[i] + "</span>")
        }
    }

    Flickable   {

        id                  :   consoleFlickable
        anchors.fill        :   parent
        anchors.margins     :   Theme.internalControlsMargin

        TextArea.flickable  :   TextArea    {
            id              :   consoleText
            font.bold       :   true
            selectByKeyboard:   true
            selectByMouse   :   true
            font.pointSize  :   9
            wrapMode        :   TextArea.Wrap
            textFormat      :   TextArea.RichText

            background      :   Rectangle{
                width       :   consoleFlickable.width
                height      :   consoleFlickable.height
                radius      :   2
                color       :   Theme.consoleBackgroundColor
            }
            onTextChanged   :   {
                flickableScroll.increase()
                outputClear.restart()
            }

            readOnly        :   true
            text            :   ""
            overwriteMode   :   true

        }

        rebound     :   Transition {
            NumberAnimation {
                properties  : "x,y"
                duration    : 1000
                easing.type : Easing.OutBounce
            }
        }

        ScrollBar.vertical  :   ScrollBar   {  id   :   flickableScroll }
    }

    ExpandCollapseButton{
        id                  :   button
        width               :   40
        height              :   40
        anchors.right       :   parent.right
        anchors.top         :   parent.top
        anchors.rightMargin :   Theme.internalControlsMargin - border.width
        anchors.topMargin   :   Theme.internalControlsMargin
        z                   :   consoleText.z + 1
        mouseArea.onClicked :   collapsed = !collapsed
        expanded            :   !collapsed
    }

    Timer   {

        id          :   outputClear
        interval    :   8000
        onTriggered :   {
            clearFlag = true
        }
    }

    Behavior on height{
        SmoothedAnimation{
            velocity    :   300
        }
    }
}
