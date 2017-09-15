import QtQuick 2.0

Item {

    readonly property real  circlePortion       :   0.4
    property bool   loading                     :   false
    property variant    circles                 :   []
    property int    currIdx                     :   0
    property variant defaultColors              :   ["red" , "white" , "white" , "red"]
    property variant currColorScheme            :   []

    id      :   logo

    Grid{
        id      :   circlesGrid
        columns :   2
        rows    :   2
        anchors.fill    :   parent
        spacing :   parent.width * 0.06

        Repeater{
            model   :   defaultColors
            Rectangle{
                id      :   circle
                radius  :   width * 0.5
                width   :   parent.width * circlePortion
                height  :   parent.height * circlePortion
                color   :   {
                    return modelData
                }
                smooth  :   true

                Component.onCompleted: {
                    circles.push(circle)
                }

                Behavior on color{

                    ColorAnimation {
                        property    :   "color"
                        duration    :   loadingAnimationTimer.interval * 0.9
                    }
                }
            }
        }
    }

    Timer{
        id          :   loadingAnimationTimer
        interval    :   200
        running     :   loading
        repeat      :   true
        onTriggered :   {

            currColorScheme = defaultColors
            var col = currColorScheme.pop()
            currColorScheme.unshift(col)

            for(var i = 0; i < currColorScheme.length; i++){
                circles[i].color = currColorScheme[i]
            }
        }
    }

    Connections{
        target          :   toolchain
        onCompileEnd    :   {
            loading = false
        }
        onCompileStart  :   {
            loading = true
        }
    }
}
