import QtQuick 2.0
import "../control"

Item {
    implicitWidth   :   400
    implicitHeight  :   250

    Column{
        width   :   parent.width
        spacing :   10

        Item{
            width   :   parent.width
            height  :   50
            GenericBackgroundContainer{
                anchors.fill        :   parent
            }
            Text {
                id      :   headerTxt
                text    :   "Editör Ayarları"
                font.pointSize  :   14
                color   :   "white"
                z       :   2
                anchors.centerIn    :   parent
            }
        }

        LabelSpinnerControl{
            id      :   fontSizeCtl
            width   :   parent.width
            height  :   50
            label   :   "Font Büyüklük"
            value   :   settings.fontSize
            min     :   8
            max     :   128
        }

        LabelSpinnerControl{
            id      :   tabSizeCtl
            width   :   parent.width
            height  :   50
            label   :   "Tab Boşluk"
            value   :   settings.tabSize
            min     :   2
            max     :   128
        }

        GenericButton{
            id      :   saveButton
            width   :   120
            height  :   40
            text    :   "Kaydet"
            anchors.right       :   parent.right
            anchors.rightMargin :   10
            onClicked   :   settings.saveSettings()
        }

        Component.onCompleted: {
            settings.tabSize    =   Qt.binding(function() {
                return tabSizeCtl.value
            })
            settings.fontSize   =   Qt.binding(function() {
                return fontSizeCtl.value    })
        }
    }
}
