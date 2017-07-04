import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick 2.7
import "../singleton"
import "../control"

Item {

    id      :   control

    signal  loginClicked()
    signal  logoutClicked()
    signal  uploadClicked()
    signal  listProjectsRequired()

    width   :   cloudStateRow.width
    height  :   50

    states  :   [
        State {
            name        :   "authenticated"; when   :   cloudApi.authenticated
        }
    ]

    transitions :   [
        Transition {
            to      :   "authenticated"
            SequentialAnimation{
                ScaleAnimator{
                    from        :   1
                    to          :   1.2
                    duration    :   500
                    easing.type :      Easing.InBounce
                    target      :   cloudStateIcon
                }
                ScaleAnimator{
                    from        :   1.2
                    to          :   1
                    duration    :   500
                    easing.type :      Easing.Linear
                    target      :   cloudStateIcon
                }
            }
        }
    ]

    Row {

        id          :   cloudStateRow
        spacing     :   10
        height      :   parent.height

        Item {
            width   :   60
            height  :   50
            visible :   cloudApi.authenticated
            Text {
                id              :   userName
                anchors.centerIn:   parent
                text            :   cloudApi.userName
                font.pointSize  :   12
                color           :   "white"
            }
        }

        Item{
            id          :   cloudControl
            width       :   50
            height      :   50
            anchors.verticalCenter  :   parent.verticalCenter

            Image{
                id      :   cloudStateIcon
                source  :   cloudApi.authenticated ? "/res/icon/cloud-icon.png" : "/res/icon/cloud-icon-unconnected.png"
                anchors.fill    :   parent
                smooth  :   true
            }

            MouseArea{
                anchors.fill    :   parent
                cursorShape     :   Qt.OpenHandCursor
                onClicked       :   {
                    if(cloudApi.authenticated){
                        cloudMenu.open()
                    }
                    else
                        control.loginClicked()
                }
            }
        }
    }

    Menu    {
        id              :   cloudMenu
        y               :   50
        x               :   -75
        z               :   5
        enter           :   Transition {
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
        }
        MenuItem    {
            text        :   "Yükle"
            onTriggered :   {
                uploadClicked()
            }
        }
        MenuItem    {
            id          :   it
            text        :   "Projelerim"
            onTriggered :   {
                listProjectsRequired()
            }
        }
        MenuItem    {
            id          :   logoutIt
            text        :   "Çıkış"
            onTriggered :   logoutClicked()
        }
    }
}
