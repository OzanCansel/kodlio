import QtQuick 2.0
import QtQuick.Controls 2.1

Button {

    property string src             :   ""
    property string     color       :   ""

    id              :   control
    clip            :   true
    width           :   40
    height          :   40
    hoverEnabled    :   true
    flat            :   true

    contentItem :   Image {
        id              :   icon
        fillMode        :   Image.PreserveAspectFit
        smooth          :   true
        source          :   src

        Behavior on scale {
            NumberAnimation{
                duration    :   100
            }
        }
    }
}
