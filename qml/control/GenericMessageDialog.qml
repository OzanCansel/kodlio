import QtQuick 2.0
import QtQuick.Controls 2.1

Dialog {
    property string     message     :   ""

    id      :   messageDialogCtl
    modal   :   true
    x           :   (parent.width / 2) - (width / 2)
    y           :   (parent.height / 2) - (height / 2)


    header      :   Item{
        implicitHeight      :   40
        implicitWidth       :   messageDialogCtl.width

        Image {
            id              :   headerBack
            source          :   "/res/icon/backgroundpattern.png"
            anchors.fill    :   parent
            fillMode        :   Image.Tile
        }


        Rectangle{
            id      :   back
            anchors.fill    :   parent
            color   :   "#075688"
            opacity :   0.6
        }
        Text {
            id      :   titleText
            text    :   ":: " + messageDialogCtl.title
            anchors.verticalCenter  :   parent.verticalCenter
            x       :   20
            color   :   "#FFF8DC"
            font.pointSize: 15
        }
    }

    footer      :   DialogButtonBox{
        id              :   dialogBox
        standardButtons :   messageDialogCtl.standardButtons
        position        :   DialogButtonBox.Footer
        alignment       :   Qt.AlignTop | Qt.AlignRight
        spacing         :   10
        delegate:   GenericButton{
            implicitHeight  :   40
            implicitWidth   :   100
        }
        background      :   Item {
            id          :   name
        }
    }

    background  :   Image {
        id          :   img
        source      :   "/res/icon/backgroundpattern.png"
        fillMode    :   Image.Tile
        anchors.fill:   parent
        z           :   0
    }

    contentItem :    Item   {
        implicitWidth   :   messageText.width + 50
        implicitHeight  :   messageText.height + 10

        Text {
            id                  :   messageText
            text                :   message
            font.pointSize      :   12
            color               :   "white"
            z                   :   2
            anchors.centerIn    :   parent
        }
    }
}
