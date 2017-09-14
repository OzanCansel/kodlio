import QtQuick 2.7
import QtQuick.Controls 2.2
import Kodlio 1.0
import "../singleton"

Item {

    property FlickableTextArea  target          :   ({})
    readonly property int startNumber           :   calculateStartLineIdx()
    property int lineCount                      :   calculateLineCount()
    readonly property int endNumber             :   startNumber + lineCount
    property variant  errors                    :   []

    function    calculateStartLineIdx(){
        //1 den buyuk
        var matchIdx = target.textArea.positionAt(0 , target.contentY)
        return lineNumberCalculator.matchIdxToLineNumber(matchIdx)
        //        return Math.max(1 , Math.round(target.contentY / (metrics.height)))
    }

    function    calculateLineCount(){
        return Math.floor(target.height / metrics.height)
    }

    function    newError(err){
        errors.push(err)
        lineCountRepeater.model = 0
        lineCountRepeater.model = lineCount
    }

    function    clearErrors(){
        while(errors.length > 0) errors.pop()
        lineCountRepeater.model = 0
        lineCountRepeater.model = lineCount
    }

    function    getError(line){
        //Error koleksiyonu kontrol ediliyor
        for(var i = 0 ; i < errors.length; i++){
            var err = errors[i]
            //Eger satirla eslesen hata varsa
            if(err.row === line)
                return err
        }

        return -1
    }

    function    hasError(line){
        //Error koleksiyonu kontrol ediliyor
        for(var i = 0 ; i < errors.length; i++){
            var err = errors[i]
            //Eger satirla eslesen hata varsa
            if(err.row === line)
                return true
        }

        return false
    }

    Connections{
        target              :   lineNumerator.target.textArea
        onTextChanged       :   {
            lineCountRepeater.model = 0
            lineCountRepeater.model = lineCount
        }
    }

    function    calculatePos(lineNumber){
        var matchIdx = lineNumberCalculator.matchIdx(lineNumber)
        if(matchIdx === -1){
            //            lineCount = lineNumber - startNumber
            return {  y : 0 , matched : false }
        }
        return {  y : target.textArea.positionToRectangle(matchIdx).y - target.contentY , matched : true }
    }

    id          :   lineNumerator

    FontMetrics {
        id              :   metrics
        font            :   target.textArea.font
    }

    LineNumber{
        id              :   lineNumberCalculator
        lineStart       :   calculateStartLineIdx()
        lineEnd         :   startNumber + lineCount
        textDocument    :   target.textArea.textDocument
    }

    Item  {
        id                  :  lineNumbersColumn
        anchors.fill        :   parent
        z                   :   2
        clip                :   true

        Repeater{
            id          :   lineCountRepeater
            model       :   lineCount
//            model       :   0
            Item    {
                readonly property  int      lineNumber          :   index + startNumber
                property bool               hasError            :   lineNumerator.hasError(lineNumber)
                property string             message             :   hasError ? getError(lineNumber).message : ""
                readonly property variant   pos                 :   calculatePos(lineNumber)

                id      :   lineNumberItem
                height  :   metrics.height
                width   :   parent.width
                y       :   pos.y
                visible :   pos.matched

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

                MouseArea{
                    id                  :   area
                    anchors.fill        :   parent
                    hoverEnabled        :   true
                    ToolTip.visible     :   lineNumberItem.hasError && area.containsMouse
                    ToolTip.text        :   lineNumberItem.message
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
