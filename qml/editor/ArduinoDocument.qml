import QtQuick 2.0
import Kodlio 1.0
import "../singleton"

Document {

    property variant    codeDescriptions    :   []

    id              :   arduinoDocument

    ArduinoHighlighter{
        id          :   highlighter
        document    :   textFlickable.textArea.textDocument
    }

    KodlioAsistant{
        id              :   assistant
        textDocument    :   textFlickable.textArea.textDocument
        cooldown        :   2000
        enabled         :   EditorSettings.assistantEnabled
        onParseStarted  :   {
            while(codeDescriptions.length > 0)  {
                var obj = codeDescriptions.pop()
                obj.destroy()
            }
        }
        onNewComment    :   {
            //<map>
            var descText = map.description
            var lineNum = map.lineNumber
            var idx = map.idx

            var commentObj = codeDescriptionComment.createObject(kodlioAssistantViewer , {
                                                                     "desc"     :   descText,
                                                                     "matchIdx" :   idx,
                                                                     "area"     :   textFlickable.textArea
                                                                 })

            codeDescriptions.push(commentObj)
        }
    }

    Item {
        id              :   kodlioAssistantViewer
        Drag.active     :   dragArea.drag.active
        width           :   assistant.enabled ? childrenRect.width : 0
        height          :   parent.height
        clip            :   true
        x               :   parent.width / 2
        z               :   2
        opacity         :   assistant.enabled ? 1 : 0
//        visible         :   assistant.enabled

        Behavior on opacity{
            NumberAnimation{
                duration        :   200
            }
        }
    }


    Rectangle{
        id                  :   asistantHeaderVisual
        anchors.left        :   kodlioAssistantViewer.left
        height              :   parent.height
        width               :   3
        color               :   "#FFA500"
        opacity             :   assistant.enabled ? 1 : 0

        Behavior on opacity{
            NumberAnimation{
                duration    :   200
            }
        }


        MouseArea   {
            id              :   dragArea
            anchors.fill    :   parent
            anchors.leftMargin  :   -width / 2
            anchors.rightMargin :   -width / 2
            cursorShape     :   Qt.SizeHorCursor
            drag.target     :   kodlioAssistantViewer
            drag.axis       :   Drag.XAxis
            drag.maximumX   :   Math.min(arduinoDocument.width - 200 , arduinoDocument.width * 0.8)
            drag.minimumX   :   Math.min(arduinoDocument.width * 0.4 , 200)
        }
    }

    Item {
        id                  :   kodlioAsistantHeaderItem
        anchors.left        :   kodlioAssistantViewer.left
        anchors.leftMargin  :   20
        anchors.top         :   parent.top
        anchors.topMargin   :   10
        anchors.right       :   parent.right
        height              :   childrenRect.height
        z                   :   kodlioAssistantViewer.z + 1
        opacity             :   assistant.enabled ? 1 : 0

        Behavior on opacity{
            NumberAnimation{
                duration    :   200
            }
        }

        Text {
            id              :   kodlioAssistantHeaderText
            text            :   "Kodlio Asistan"
            font.pointSize  :   16
            font.family     :   FontCollection.documentHeaderFont
            font.bold       :   true
            color           :   "#505050"
        }
    }

    Component{
        id      :   codeDescriptionComment
        Item {
            property string    desc     :   ({})
            property int       matchIdx :   ({})
            property TextEdit  area     :   ({})
            id      :   commentContainer
            width   :   name.implicitWidth
            height  :   name.implicitHeight
            x       :   asistantHeaderVisual.width + 5
            y       :   area.positionToRectangle(matchIdx).y - textFlickable.contentY

            Text {
                id      :   name
                text    :   commentContainer.desc
                font    :   textFlickable.textArea.font
                color   :   "#28A828"
            }
        }
    }

    textFlickable.modified  :   highlighter.modified
}
