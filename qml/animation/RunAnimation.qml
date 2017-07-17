// Show a triangle by pure QML
import QtQuick 2.0

Item{
    id : component
    width: 100
    height: 100

    property int    starting        :   0
    property int    started         :   1
    property int    startError      :   2

    property int    currentState    :   starting

    // The index of corner for the triangle to be attached
    property int    corner      :   0;
    property alias  color       :   triangleRect.color
    property real   border      :   2

    readonly property variant   backgroundColor :   ["#ffcc33" , "#33cc33" , "#940092"]

    Item {

        id                      :   animItem
        width                   :   parent.width
        height                  :   parent.height
        clip : true

        Rectangle {
            x                   :   component.width * ((corner+1) % 4 < 2 ? 0 : 1) - width / 2
            y                   :   component.height * (corner    % 4 < 2 ? 0 : 1) - height / 2
            id                  :   triangleRect
            color               :   backgroundColor[currentState]
            antialiasing        :   true
            width               :   Math.min(component.width,component.height)
            height              :   width
            transformOrigin     :   Item.Center
            rotation            :   45
            scale               :   1.414
            border.width        :   component.border * (1 / scale)
        }

        Rectangle{
            id              :   bottomBorder
            height          :   component.border
            width           :   parent.width - 1
            anchors.top     :   parent.top
            color           :   "black"
            z               :   2
            clip            :   true
        }

        Rectangle{
            width          :    component.border
            height          :   parent.height - 1
            anchors.left    :   parent.left
            color           :   "black"
            z               :   2
            clip            :   true
        }

        SequentialAnimation{
            id              :   startingAnimation
            running         :   currentState === starting
            loops           :   Animation.Infinite

            ColorAnimation {
                target      :   triangleRect.Rect
                from        :   backgroundColor[starting]
                to          :   Qt.lighter(backgroundColor[starting] , 1.5)
                duration    :   400
                property    :   "color"
            }

            ColorAnimation {
                target      :   triangleRect
                property    :   "color"
                from        :   Qt.lighter(backgroundColor[starting] , 1.5)
                to          :   backgroundColor[starting]
                duration    :   400
            }
        }

        ParallelAnimation{
            id              :   startedAnimation
            running         :   currentState === started
            ColorAnimation {
                target      :   triangleRect.Rect
                from        :   triangleRect.color
                to          :   backgroundColor[started]
                duration    :   400
                property    :   "color"
            }
        }

        Timer{
            id          :   mock
            running     :   false
            repeat      :   true
            interval    :   2000
            onTriggered :   currentState = Math.floor(Math.random() * 2.99)
        }
    }
}
