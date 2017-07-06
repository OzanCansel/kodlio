import QtQuick 2.0
import "../singleton"

Item {

    Text {
        id                  :   documentText
        text                :   qsTr("Dokuman Acilmadi !")
        font                :   FontCollection.messageFont
        anchors.centerIn    :   parent
    }
}
