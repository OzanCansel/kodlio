import QtQuick 2.0

Item {

    property string     labelText       :   "Label"
    property string     value           :   "Value"

    GenericLabel    {
         id     :   l
         width  :   parent.width * 0.5
         height :   parent.height
         text   :   labelText
    }

    GenericTextBox{
        id      :   txt
        width   :   parent.width * 0.5
        anchors.left    :   l.right
        anchors.top     :   parent.top
        anchors.bottom  :   parent.bottom
        anchors.right   :   parent.right
        text            :   value
    }
}
