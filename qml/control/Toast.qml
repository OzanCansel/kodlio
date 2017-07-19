import QtQuick 2.2
import "../animation"
import "../singleton"

Item {

    //Widthh
    readonly property real rectWidthMultiplier      :   1.7
    readonly property real borderWidth              :   0.03
    readonly property int  info                     :   0
    readonly property int  warning                  :   1
    readonly property int  error                    :   2

    //Height
    readonly property real rectHeightMultiplier :   3

    //Colors
    property color  fillColor               :   "white"
    property color  borderColor             :   "black"
    property color  textColor               :   "black"


    //Radius
    property real toastRadius               :   0.1

    //Flag
    property bool   hasBorder               :   true

    //Duration
    property real showDuration              :   1500
    property real disappearDuration         :   1000

    property Item container

    id              :   loader

    function    displayMessage(message){
        var toastObj = toastComponent.createObject(container)

        toastObj.message    =   message
        toastObj.z          =   10
        toastObj.type       =   info
    }

    function    displayError(message){
        display(message , error)
    }

    function    displayWarning(message){
        display(message,  warning)
    }

    function    display(message , type){
        var toastObj = toastComponent.createObject(container)

        toastObj.message    =   message
        toastObj.z          =   10
        toastObj.type       =   type
    }

//    Timer{
//        repeat  :   true
//        interval    :   2000
//        running     :   true
//        onTriggered :   {
//            var type = Math.floor(Math.random() * 2.99)
//            display("Kutuphaneler yuklenirken hata olustu." , type)
//        }
//    }

    Component   {
        id          :   toastComponent

        Rectangle   {
            property string     message     :   "Mesaj Yok"
            property int        type        :   0
            readonly property variant    backgroundColors   :   ["#bbf5bb" , "#ffeaa7" , "#f67975"]
            readonly property variant    fontColors         :   ["#30875c" , "#735f22" , "#fee2ee"]
            id          :   toastItem
            width       :   text.contentWidth * rectWidthMultiplier
            height      :   text.contentHeight * rectHeightMultiplier
            y           :   container.height - height - (container.height * 0.1)
            color       :   backgroundColors[type]
            clip        :   true
            radius      :   5
            border.color:   "#b05652"
            border.width:   1
            anchors.horizontalCenter:   parent.horizontalCenter

            Text    {
                id                  :   text
                anchors.centerIn    :   parent
                font.pointSize      :   16
                font.family         :   FontCollection.toastFont
                font.bold           :   true
                text                :   message
                color               :   toastItem.fontColors[toastItem.type]
            }

            NumberAnimation {
                id          :   easingAnimation
                properties  :   "y"
                target      :   toastItem
                from        :   toastItem.parent.height + toastItem.height
                to          :   toastItem.y
                duration    :   600
                easing.type :   Easing.InOutBack
            }

            SequentialAnimation{
                id          :   showAndFade
                running     :   true

                NumberAnimation{
                    target      :   toastItem
                    property    :   "scale"
                    from        :   0.5
                    to          :   1
                    duration    :   250
                    easing.type :   Easing.InCirc
                }

                PauseAnimation {
                    duration    :   1200
                }

                NumberAnimation{
                    target      :   toastItem
                    property    :   "opacity"
                    from        :   1
                    to          :   0
                    duration    :   1000
                }

                ScriptAction    {
                    script      :   {
                        toastItem.destroy()
                    }
                }
            }

            Component.onCompleted: {
                showAndFade.running =   true
            }
        }
    }
}
