import QtQuick 2.7
import "../singleton"

Item {
    property FlickableTextArea  target          :   ({})
    readonly property int startNumber           :   calculateStartLineIdx()
    property int lineCount                      :   calculateLineCount()
    readonly property int endNumber             :   startNumber + lineCount
    property variant  errors                    :   []

    function    calculateStartLineIdx(){
        //1 den buyuk
        return Math.max(1 , Math.round(target.contentY / metrics.height))
    }

    function    calculateLineCount(){
        return Math.floor(target.height / metrics.height)
    }

    function    newError(row){
        errors.push(row)
        lineCount = 0
        lineCount = Qt.binding(calculateLineCount)
    }

    function    clearErrors(){
        while(errors.length > 0) errors.pop()
        lineCount = 0
        lineCount = Qt.binding(calculateLineCount)
    }

    function    hasError(line){
        return errors.indexOf(line) > -1
    }

    id          :   lineNumerator

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
            id          :   lineCountRepeater
            model       :   lineCount
            Item    {
                readonly property  int lineNumber       :   index + startNumber
                property bool       hasError            :   lineNumerator.hasError(lineNumber)

                id      :   lineNumberItem
                height  :   metrics.height
                width   :   parent.width

                Text {
                    id                  :   lineNumberText
                    text                :   lineNumberItem.lineNumber
                    font                :   metrics.font
                    anchors.centerIn    :   parent
                    color               :   Theme.lineNumeratorTextColor
                    z                   :   2
                }

                Rectangle{
                    id                  :   errorRect
                    color               :   lineNumberItem.hasError ? "red" : "transparent"
                    anchors.fill        :   parent
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
