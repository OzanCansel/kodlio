import QtQuick 2.7
import QtQuick.Controls 2.2
import Kodlio 1.0
import "../singleton"

Item {

    property Cloud cloud            :   ({})
    property Item dialogContainer   :   ({})

    id                              :   container
    width                           :   menu.width
    height                          :   childrenRect.height

    signal  uploadProject()
    signal  listProjects()
    signal  logout()

    function open(){
        menu.open()
    }

    Item    {
        id                          :   headerContainer
        width                       :   parent.width
        height                      :   40
        visible                     :   cloud.authenticated && menu.visible

        Text {
            id                      :   userNameText
            text                    :   cloud.userName
            anchors.centerIn        :   parent
            z                       :   2
            color                   :   "white"
            font.family             :   FontCollection.menuFont
            font.bold               :   true
        }

        Rectangle{
            id                      :   back
            anchors.fill            :   parent
            color                   :   "#ffa500"
            radius                  :   10
            anchors.bottomMargin    :   -radius
        }
    }

    GenericMenu {

        id          :   menu
        y           :   headerContainer.height

        GenericMenuItem    {
            id              :   uploadProjectItem
            text            :   "Projeyi Yükle"
            tooltipEnabled  :   true
            tooltipText     :   "Mevcut projeniniz yüklemek için tıklayınız"
            onTriggered     :   uploadProject()
        }

        GenericMenuItem     {
            id              :   listProjectsItem
            text            :   "Projelerim"
            tooltipEnabled  :   true
            tooltipText     :   "Buluttaki projelerinizi listelemek için tıklayınız"
            onTriggered     :   listProjects()
        }

        GenericMenuItem     {
            id              :   logoutItem
            text            :   "Çıkış Yap"
            tooltipEnabled  :   true
            tooltipText     :   "Çıkış yapmak için tıklayınız"
            onTriggered     :   logout()
        }
    }
}
