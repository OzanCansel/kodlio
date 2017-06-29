import QtQuick 2.0
import "../control"

Item {

    implicitHeight      :   107
    implicitWidth       :   300

    Column{
        anchors.fill    :   parent
        spacing         :   10

        GenericTextBox  {
            id                  :   classNameTxt
            width               :   parent.width
            height              :   50
            placeholderText    :   "Sınıfın ismini giriniz...";
        }

        Row{
            width                   :   parent.width
            height                  :   50
            spacing                 :   10
            layoutDirection         :   Qt.RightToLeft

            GenericButton   {
                width               :   120
                height              :   parent.height
                text                :   "Oluştur"
                onClicked           :   {
                    projectManager.createNewClass(classNameTxt.text , "./")
                    close()
                }
                backgroundRect.opacity  :   hovered || pressed ? 0.75 : 0.6
                backgroundRect.color    :   "#006f98"
                contentTextItem.color   :   "white"
            }

            GenericButton   {
                width               :   120
                height              :   parent.height
                text                :   "İptal"
                onClicked           :   close()
                contentTextItem.color   :   "white"
                backgroundRect.opacity  :   hovered || pressed ? 0.75 : 0.6
                backgroundRect.color    :   "#006f98"
            }
        }
    }
}
