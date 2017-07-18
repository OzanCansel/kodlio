import QtQuick 2.0
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0

Item {
    property real   progress                        :   0
    property string header                          :   ""
    property int    hiddenTimeout                   :   2000
    readonly property real   progressBarPortion     :   0.4
    readonly property real   progressBarWidth       :   0.9
    property bool   progressClear                   :   false
    property int    progressVelocity                :   width * 0.7

    id          :   genericProgressBar
    visible     :   false

    onProgressChanged   :   {
        progressClear   =   false
        if(progress !== 0)
            visible         =   true
        if(progress === 1)
            hideAnimation.restart()
        else
            hideAnimation.stop();

        if(progress === -1)
            hideAnimation.restart()
    }

    Text {
        id      :   name
        text    :   header
        color   :   "yellow"
        z       :   2
        y       :   3
        anchors.horizontalCenter    :   parent.horizontalCenter
    }

    ProgressBar{
        id                      :   control
        value                   :   progressClear ? 0 : progress
        z                       :   2
        anchors.bottom          :   parent.bottom
        anchors.bottomMargin    :   parent.height * 0.1
        anchors.horizontalCenter:   parent.horizontalCenter

        background :   Rectangle{
            implicitWidth       :   genericProgressBar.width * progressBarWidth
            implicitHeight      :   genericProgressBar.height * progressBarPortion
            color               :   "transparent"
        }

        contentItem:    Rectangle{
            implicitWidth   :   genericProgressBar.width * progressBarWidth
            implicitHeight  :   genericProgressBar.height * progressBarPortion
            radius          :   height * 0.3

            Rectangle{
                id      :   internalCtl
                width   :   control.visualPosition * parent.width
                height  :   parent.height
                radius  :   parent.radius
                color   :   "#17a81a"
                z       :   3

                Behavior on width {
                    SmoothedAnimation{
                        velocity    :   progressVelocity
                    }
                }
            }
        }
    }

    SequentialAnimation {

        id                  :   hideAnimation

        PauseAnimation {
            duration        :   hiddenTimeout
        }

        ScriptAction{
            script          :   {
                genericProgressBar.visible  =   false
                progressClear               =   true
            }
        }
    }

    Image {
        id          :   img
        source      :   "/res/icon/backgroundpattern.png"
        fillMode    :   Image.Tile
        anchors.fill:   parent
        z           :   0
    }
}
