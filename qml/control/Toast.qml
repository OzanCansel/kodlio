import QtQuick 2.2

Item {

    //Widthh
    readonly property real rectWidthMultiplier      :   1.7
    readonly property real borderWidth              :   0.03

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
    }

    Component   {
        id          :   toastComponent

        Rectangle   {
            property string     message     :   "Mesaj Yok"
            id          :   toastItem
            width       :   text.contentWidth * rectWidthMultiplier
            height      :   text.contentHeight * rectHeightMultiplier
            y           :   container.height - height - (container.height * 0.1)
            color       :   "transparent"
            clip        :   true
            Image {
                id          :   img
                source      :   "/res/icon/backgroundpattern.png"
                fillMode    :   Image.Tile
                anchors.fill:   parent
                z           :   0
            }
            radius      :   height * loader.toastRadius
            border.width:   loader.hasBorder ? height * borderWidth  : 0
            border.color:   loader.borderColor
            anchors.horizontalCenter:   parent.horizontalCenter

            Text    {
                id                  :   text
                anchors.centerIn    :   parent
                font.pointSize      :   16
                text                :   message
                color               :   loader.textColor
            }

            states      :   [
                State{
                    name    :   "hide"
                    PropertyChanges {
                        target      :   toastItem
                        opacity     :   0
                        y           :   toastItem.parent.height + toastItem.height
                    }
                }
            ]

            Behavior on opacity{
                NumberAnimation{
                    duration    :   loader.disappearDuration

                    onRunningChanged    :   {
                        if(!running){
                            toastItem.destroy()
                        }
                    }
                }
            }

            Behavior on y   {
                NumberAnimation {
                    duration    :   loader.disappearDuration
                }
            }

            NumberAnimation{
                id          :   easingAnimation
                properties  :   "y"
                target      :   toastItem
                from        :   toastItem.parent.height + toastItem.height
                to          :   toastItem.y
                duration    :   600
                easing.type :   Easing.InOutBack
            }

            Timer{
                interval        :   loader.showDuration
                running         :   true
                onTriggered     :   {
                    toastItem.state = "hide"
                }
            }

            Component.onCompleted: {
                easingAnimation.running =   true
            }
        }
    }
}
