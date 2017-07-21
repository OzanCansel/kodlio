import QtQuick 2.0
import Kodlio 1.0
import "../control"

Item {

    implicitWidth   :   400
    implicitHeight  :   150

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

        LabelSpinnerControl {
            id      :   fontSizeCtl
            width   :   parent.width
            height  :   50
            label   :   "Font Büyüklük"
            value   :   EditorSettings.fontPointSize
            min     :   8
            max     :   128
        }

//        LabelSpinnerControl{
//            id      :   tabSizeCtl
//            width   :   parent.width
//            height  :   50
//            label   :   "Tab Boşluk"
//            value   :   EditorSettings.tabSize
//            min     :   2
//            max     :   128
//        }

//        GenericButton{
//            id      :   saveButton
//            width   :   120
//            height  :   40
//            text    :   "Kaydet"
//            anchors.right       :   parent.right
//            anchors.rightMargin :   10
//            onClicked   :   EditorSettings.save()
//        }

        Component.onCompleted: {
            EditorSettings.tabSize         =   Qt.binding(function() {
                return tabSizeCtl.value
            })
            EditorSettings.fontPointSize   =   Qt.binding(function() {
                return fontSizeCtl.value    })
        }
    }
}
