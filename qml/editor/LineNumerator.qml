import QtQuick 2.7
import "../singleton"

Item {
    property FlickableTextArea  target          :   ({})
    readonly property int startNumber           :   calculateStartLineIdx()
    readonly property int lineCount             :   calculateLineCount()
    readonly property int endNumber             :   startNumber + lineCount

    function    calculateStartLineIdx(){
        //1 den buyuk
        return Math.max(1 , Math.round(target.contentY / metrics.height))
    }

    function    calculateLineCount(){
        return Math.floor(target.height / metrics.height)
    }

    id          :   luneNumerator

    FontMetrics {
        id              :   metrics
        font            :   target.textArea.font
    }

    Column  {
        id                  :  lineNumbersColumn
        anchors.fill        :   parent
        anchors.topMargin   :   5
        anchors.bottomMargin:   5
        spacing             :   metrics.leading
        z                   :   2
        clip                :   true

        Repeater{
            model       :   lineCount
            Item{
                id      :   lineNumberItem
                height  :   metrics.height
                width   :   parent.width
                Text {
                    id                  :   lineNumber
                    text                :   index + startNumber
                    font                :   metrics.font
                    anchors.centerIn    :   parent
                    color               :   Theme.lineNumeratorTextColor
                }
            }
        }
    }

    Rectangle{
        anchors.fill    :   parent
        color           :   Theme.lineNumeratorBackgroundColor
        opacity         :   Theme.lineNumeratorOpacity
        radius          :   0
    }

    Rectangle{
        anchors.top     :   parent.top
        anchors.bottom  :   parent.bottom
        anchors.right   :   parent.right
        width           :   2
        color           :   "black"
        visible         :   false
    }
}
