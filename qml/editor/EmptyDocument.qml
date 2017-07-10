import QtQuick 2.0
import "../singleton"

Item {

    property bool       projectOpened    :  false

    Item{

        anchors.centerIn:   parent
        width           :   textPositioner.childrenRect.width
        height          :   textPositioner.childrenRect.height
        z               :   2


        Text {
            id                          :   openDocumentText
            text                        :   qsTr("Döküman Aç")
            anchors.bottom              :   textPositioner.top
            anchors.bottomMargin        :   20
            anchors.horizontalCenter    :   parent.horizontalCenter
            font.pointSize              :   20
            font.family                 :   FontCollection.messageFont
        }

        Column{
            id          :   textPositioner
            spacing     :   10

            Row{
                width                   :   childrenRect.width
                height                  :   childrenRect.height

                Text {
                    id                  :   documentText
                    text                :   "- Sol üstteki "
                    font.family         :   FontCollection.messageFont
                    visible             :   !projectOpened
                }

                Image {
                    id          :   menuIconImg
                    source      :   "/res/icon/cog.png"
                    width       :   30
                    height      :   30
                    fillMode    :   Image.PreserveAspectFit
                    anchors.verticalCenter  :   documentText.verticalCenter
                }

                Text {
                    text        :   qsTr("  simgesine tiklayin ve 'Aç' tuşuna basarak proje açın")
                }
            }

            Row{
                width               :   childrenRect.width
                height              :   childrenRect.height
                visible             :   !projectOpened

                Text {
                    id                  :   documentText2
                    text                :   "- Sol üstteki "
                    font.family         :   FontCollection.messageFont
                }

                Image {
                    source                  :   "/res/icon/cog.png"
                    width                   :   30
                    height                  :   30
                    fillMode                :   Image.PreserveAspectFit
                    anchors.verticalCenter  :   documentText2.verticalCenter
                }

                Text {
                    text                :   " simgesine tiklayin ve 'Yeni Proje' tuşuna basarak proje oluşturun"
                    font.family         :   FontCollection.messageFont
                }

            }

            Text {
                id                  :   documentText3
                text                :   "- Sol bölümdeki dosyalardan birine tıklayın"
                font.family         :   FontCollection.messageFont
                visible             :   projectOpened
            }
        }
    }

    Rectangle{
        id                  :   backRect
        color               :   "#dddddd"
        anchors.fill        :   parent
    }

}
