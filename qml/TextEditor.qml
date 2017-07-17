import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls 1.4 as Quick1
import QtQuick.Layouts 1.1

import Roboskop     1.0
import "singleton"
import "autocomplete"

Rectangle {

    readonly property real margin               :   0.02
    readonly property real areaRadius           :   0.02
    readonly property real editorNumberOffset   :   calculateLineNumberOffset()
    property bool autoCompleteActive            :   false
    property variant lineNumbersMap             :   []
    property variant codeDescriptions           :   []
    property variant errorLines                 :   []
    property variant errorPoints                :   []

    ArduinoFunctionsSet{
        id          :   arduinoFuncs
    }

    AutoCompleteSet {
        id          :   currentModel
    }

    function    setContent(content){
        textControl.text = content
    }

    function    calculateLineNumberOffset(){
        var offset = editorFlickable.visibleArea.yPosition * editorFlickable.contentHeight / 17.5
        return  offset
    }

    function    calculateRepeateLineNum(idx){
        return idx + 1 + Math.ceil(editorNumberOffset)
    }

    function    hasError(lineNum){
        for(var i = 0; i < errorLines.length; i++){
            if(errorLines[i].lineNumber === lineNum)
                return true;
        }

        return false;
    }

    function    calculatePoint(line , column){
        var pos = parseHelper.calculatePosition(textControl.text , line)
        var point = textControl.positionToRectangle(pos + column)
        point.y = point.y - editorFlickable.visibleArea.yPosition * editorFlickable.contentHeight + 6.5

        return point
    }

    function    retrieveError(lineNum){
        for(var i = 0; i < errorLines.length; i++){
            if(errorLines[i].lineNumber === lineNum)
                return errorLines[i].error;
        }

        return ""
    }

    function    clearErrorPoints(){

        while(errorPoints.length > 0){
            var p = errorPoints.pop()
            p.remove()
        }
    }

    function    clearErrorLines(){
        while(errorLines.length > 0)
            errorLines.pop()

        lineNumberRepeater.update()
    }

    function    filterDropdown(){
        textControl.selectWord();

        currentModel.clear()

        var txt = textControl.selectedText

        if(!parseHelper.isVariable(txt))
            txt = ""

        for(var i = 0; i < arduinoFuncs.count; i++){
            var item    =   arduinoFuncs.get(i)
            var result  =   item.name.startsWith(txt);

            if(result){
                currentModel.append(item)
            }
        }

        textControl.deselect()
    }

    function    checkCodeDescriptions(){
        codeAssistantHeader.visible = codeDescriptions.length > 0
    }

    id          :   textEditorCont
    color       :   "transparent"

    Item {
        id              :   errorShow
        anchors.left    :   editorFlickable.left
        anchors.top     :   editorFlickable.top
        z               :   5
    }

    Item {

        Rectangle{
            id      :   codeAssistantHeader
            width   :   10
            height  :   50
            z       :   5
            color   :   "green"
            border.width    :   1
            x       :   0
            y       :   15
            visible :   false

            MouseArea   {
                id              :   dragArea
                anchors.fill    :   parent
                drag.target     :   commentContainer
                drag.axis       :   Drag.XAxis
            }

            Text {
                id      :   commentAssitant
                text    :   "Kodlio Asistan"
                color   :   "green"
                x       :   20
                font.pointSize  :   16
                anchors.verticalCenter  :   parent.verticalCenter
            }

            Drag.active :   dragArea.drag.active
            Behavior on scale{
                NumberAnimation{
                    duration    :   100
                }
            }
        }

        id      :   commentContainer
        z       :   5
        x       :   editorFlickable.x + editorFlickable.width * 0.3
        clip    :   true
        width   :   childrenRect.width + 10
        height  :   childrenRect.height + 20
    }

    Flickable   {
        id      :   lineNumber
        x       :   Theme.internalControlsMargin
        y       :   Theme.internalControlsMargin
        width   :   50
        height  :   parent.height -y -lines.anchors.margins
        clip    :   true

        Rectangle{

            color       :   "#006f98"
            width       :   50
            height      :   textEditorCont.height - Theme.internalControlsMargin * 2
            radius      :   5
            opacity     :   0.6
        }


        Item{
            id              :   lines
            anchors.fill    :   parent
            anchors.margins :   Theme.internalControlsMargin

            Repeater    {
                id          :   lineNumberRepeater
                model       :   45
                Item {
                    height      :   textControl.font.pixelSize
                    width       :   parent.width
                    anchors.horizontalCenter    :   parent.horizontalCenter

                    y       :   {
                        var pos =   parseHelper.calculatePosition(textControl.text , index + 1)
                        //Refresh trick
                        var refreshBinding = textControl.font.pixelSize
                        if(pos < 0)
                            return 0
                        return textControl.positionToRectangle(pos).y - Theme.internalControlsMargin
                    }

                    Text {
                        id      :   lineText
                        text    :   textControl.lineCount < calculateRepeateLineNum(index) ? "" : calculateRepeateLineNum(index)
                        color                       :   hasError(calculateRepeateLineNum(index)) ? "red" : "black"
                        font.pixelSize              :   textControl.font.pixelSize * 0.8
                        font.family                 :   textControl.font.family
                        font.bold                   :   true
                        height                      :   parent.height
                        anchors.centerIn            :   parent
                    }
                }
            }
        }
    }

    ListModel{
        id          :   autoCompleteListModel
    }

    Rectangle   {
        id              :   autoCompleteContainer
        width           :   300
        height          :   {

            var     cnt = currentModel.count >= 10 ? 10 : currentModel.count

            return (cnt * 30) - 1
        }

        x               :   textControl.positionToRectangle(textControl.cursorPosition).x + 15 + lineNumber.width
        y               :   textControl.positionToRectangle(textControl.cursorPosition).y + 25
        border.width    :   1
        visible         :   autoCompleteActive
        z               :   6
        clip            :   false


        ListView    {
            id              :   autoComplete
            width           :   parent.width
            height          :   parent.height
            anchors.margins :   autoCompleteContainer.border.width
            model           :   currentModel

            delegate            :   AutoCompleteItemVisual  {
                id              :   autoCompleteVisItem
                itLabel         :   name
                itDescription   :   description
                itType          :   type
                itExample       :   example
                itTemplate      :   usageTemplate
                width           :   autoCompleteContainer.width - (2 * border.width)
                height          :   30
                descriptionWidth    :   300
                descriptionHeight   :   150

                Connections{
                    target                  :   autoComplete
                    onCurrentIndexChanged   :   {
                        var     openOther   =   false
                        if(autoComplete.currentIndex != index){
                            openOther   =   autoCompleteVisItem.descriptionVisible
                            autoCompleteVisItem.setDescriptionVisible(false)
                        }

                        if(openOther)
                            autoComplete.currentItem.setDescriptionVisible(true)

                    }
                }
            }

            highlight   :   Rectangle {
                width: 180; height: 40
                color: "lightsteelblue"
                radius: 0
                Behavior on y {
                    SpringAnimation {
                        spring: 3
                        damping: 0.2
                    }
                }
            }
        }
    }



    Flickable
    {

        id                  :   editorFlickable
        anchors.left        :   lineNumber.right
//        anchors.leftMargin  :   13
        anchors.right       :   parent.right
        anchors.top         :   parent.top
        anchors.bottom      :   parent.bottom
        anchors.margins     :   Theme.internalControlsMargin
        visibleArea.onYPositionChanged  :    {
            codeComment.restart()
        }


        TextArea.flickable  :   TextArea    {

            property bool autoCompleteOpen  :   false
            readOnly        :   projectManager.readOnly
            id              :   textControl
            anchors.leftMargin  :   0
            selectByMouse   :   true
            color           :   Theme.editorStandardFontColor
            selectionColor  :   "lightsteelblue"

            background      :   Rectangle   {
                id          :   editorBackground
                radius      :   6
                color       :   Theme.editorBackgroundColor
                border.width:   projectManager.modified ? 3 : 0
                border.color:   Theme.editorModifiedBorderColor

                Image {
                    id              :   name
                    source          :   "/res/icon/logo.png"
                    anchors.fill    :   parent
                    anchors.margins :   parent.height * 0.2
                    opacity         :   0.05
                    fillMode        :   Image.PreserveAspectFit
                }
            }

            font.pointSize  :   settings.fontSize

            onTextChanged   :   {
                if(autoCompleteActive)
                    filterDropdown()

                codeComment.restart()
            }

            Keys.onSpacePressed     :   {

                if(event.modifiers & Qt.ControlModifier){
                    textEditorCont.autoCompleteActive  =   true
                    filterDropdown()
                }

                event.accepted = false
            }

            Keys.onDownPressed      :   {
                if(autoCompleteActive){
                    event.accepted = true
                    autoComplete.incrementCurrentIndex()
                }else{
                    event.accepted = false
                }
            }

            Keys.onUpPressed        :   {
                if(autoCompleteActive){
                    event.accepted = true
                    autoComplete.decrementCurrentIndex()
                }else{
                    event.accepted = false
                }
            }

            Keys.onRightPressed     :   {
                if(autoCompleteActive){
                    event.accepted = true
                    autoComplete.currentItem.setDescriptionVisible(true)
                }
                else{
                    event.accepted = false
                }
            }

            Keys.onLeftPressed     :   {
                if(autoCompleteActive){
                    event.accepted = true
                    autoComplete.currentItem.setDescriptionVisible(false)
                }
                else{
                    event.accepted = false
                }
            }

            Keys.onEnterPressed     :   {
                if(textControl.autoCompleteOpen){
                    textControl.append(autoComplete.currentItem.label)
                }
            }

            Keys.onReturnPressed: {
                if(autoCompleteActive){
                    textControl.selectWord()
                    textControl.remove(textControl.selectionStart , textControl.selectionEnd)
                    textControl.insert(textControl.cursorPosition , autoComplete.currentItem.itTemplate)
                    autoCompleteActive  =   false
                    event.accepted      =   true
                }
                else
                    event.accepted = false
            }

            Keys.onEscapePressed    :   {
                textEditorCont.autoCompleteActive  =   false
                event.accepted = false
            }

            Component.onCompleted   :{
                projectManager.document = textControl.textDocument
            }
        }

        ScrollBar.vertical  :   ScrollBar   {   }
    }

    Timer{
        id          :   codeComment
        interval    :   1000
        onTriggered :   {
            while(codeDescriptions.length > 0){
                var obj  =  codeDescriptions.pop()
                obj.remove()
            }

            var functions = descriptionGenerator.retrieveFunctionDescriptions(textControl.text);
            checkCodeDescriptions()
        }
    }

    Connections{
        target      :   descriptionGenerator
        onDescriptionAppend :   {
            //  <description>

            var pos = parseHelper.calculatePosition(textControl.text , description.lineNumber)
            var yPos = textControl.positionToRectangle(pos).y
            yPos = yPos - editorFlickable.visibleArea.yPosition * editorFlickable.contentHeight + 6.5
            if(yPos < 70)
                return;
            var descriptionObj = lineDescriptor.createObject(commentContainer , { "text" : "-" + description.description ,
                                                                 "y" : yPos ,
                                                                 "font.pixelSize" : textControl.font.pixelSize , "z" : 2});

            codeDescriptions.push(descriptionObj)
            checkCodeDescriptions()
        }
    }

    Connections{
        target      :   compiler
        onStdError  :   {
            //<text>
            clearErrorPoints()
            compilerErrorParser.extractErrors(text)
        }
    }

    Connections{
        target      :   compilerErrorParser
        onErrorOccurred :   {
            //<err>
            errorLines.push(err)

            var pos = parseHelper.calculatePosition(textControl.text , err.lineNumber)
            var point = textControl.positionToRectangle(pos + err.columnNumber)
            point.y = point.y - editorFlickable.visibleArea.yPosition * editorFlickable.contentHeight + 6.5

            if(point.y < 70)
                return

            var descriptionObj = errorDescriptor.createObject(errorShow , { "lineNum" : err.lineNumber , "columnNum" : err.columnNumber , "error" : err.error } );

            errorPoints.push(descriptionObj)
        }
    }

    Connections{
        target  :   toolchain
        onCompileStart  :   {
            clearErrorPoints()
            clearErrorLines()
        }
        onCompileEnd    :   {
            //<success>

            if(success)
                compileSuccesAnimation2.restart()
            else
                failureAnimation.restart()
        }
    }

    Image {
        id      :   failureIcon
        source  :   "/res/icon/failure.png"
        width   :   128
        fillMode:   Image.PreserveAspectFit
        x       :   textEditorCont.width * 0.45
        y       :   textEditorCont.height * 0.5
        visible :   failureAnimation.running
    }

    SequentialAnimation{
        id          :   failureAnimation

        ParallelAnimation{

            NumberAnimation{
                target  :   failureIcon
                property:   "scale"
                from    :   0.3
                to      :   1
                duration:   700
            }

            NumberAnimation{
                target  :   failureIcon
                property:   "opacity"
                from    :   0
                to      :   1
                duration:   500
            }
        }



        PauseAnimation {
            duration    :   1000
        }

        NumberAnimation{
            target  :   failureIcon
            property:   "opacity"
            from    :   1
            to      :   0
            duration:   500
        }

    }

    SequentialAnimation{

        id          :   compileFailedAnimation

        ColorAnimation {
            id      :   compileFailedStep1
            target  :   editorBackground
            property:   "color"
            from    :   Theme.editorBackgroundColor
            to      :   "red"
            duration:   500
            easing.type :   Easing.InOutBounce
        }


        ColorAnimation {
            id          :   compileFailedStep2
            target      :   editorBackground
            property    :   "color"
            from        :   "red"
            to          :   Theme.editorBackgroundColor
            duration    :   200
        }
    }

    Component   {
        id          :   lineDescriptor
        Text {
            property int lineNumber :   0
            id      :   text
            text    :   qsTr("text")
            z       :   5
            color   :   "green"
            function    remove(){
                destroy()
            }
        }
    }

    Component{
        id          :   errorDescriptor
        Rectangle   {
            property int lineNum            :   0
            property int columnNum          :   0
            property string     error       :   ""
            property bool       expanded    :   false
            id      :   errDescIt
            width   :   expanded ? (errorText.width + 5) * 1.1 : 0
            height  :   expanded ? errorText.height : 0
            color   :   "transparent"
            z       :   5
            x       :   calculatePoint(lineNum , columnNum).x
            y       :   calculatePoint(lineNum , columnNum).y + 13
            radius  :   10

            Behavior on height{
                SmoothedAnimation{
                    velocity    :   150
                }
            }

            Behavior on width{
                SmoothedAnimation{
                    velocity    :   errorText.width > 0 ? errorText.width * 0.7 : 0
                }
            }

            Canvas{
                id      :   triangle
                width   :   15
                height  :   15
                y       :   -height + 1
                x       :   parent.radius * 0.6
                onPaint :   {
                    var ctx = getContext("2d");
                    ctx.fillStyle = "#d9140c"
                    ctx.beginPath()
                    ctx.moveTo(triangle.width * 0.5 , 0)
                    ctx.lineTo(0 , triangle.height)
                    ctx.lineTo(triangle.width , triangle.height)
                    ctx.closePath()
                    ctx.fill()
                    ctx.strokeStyle = "white"
                }
                z       :   5
                MouseArea{
                    id              :   area
                    anchors.fill    :   parent
                    onClicked       :   errDescIt.expanded = !errDescIt.expanded
                }
            }

            function    remove(){
                destroy()
            }

            Item{
                clip        :   true
                anchors.fill:   parent
                z           :   2
                Text {
                    id      :   errorText
                    text    :   error
                    x       :   5
                    y       :   5
                    visible :   errDescIt.expanded
                    color   :   "white"
                }
            }

            Rectangle{
                anchors.fill    :   parent
                //                color           :   "#a9040c"
                color           :   "#d9140c"
                radius          :   parent.radius
                opacity         :   1
            }
        }
    }
}
