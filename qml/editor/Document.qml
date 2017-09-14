import QtQuick 2.7
import QtQuick.Controls 2.2
import Kodlio 1.0
import "../singleton"

Item {

    property int        identity        :   0
    property string     relativePath    :   ""
    property string     absolutePath    :   ""
    property string     type            :   ""
    property bool       isReadOnly      :   false
    readonly property bool modified     :   textFlickable.modified
    readonly property   string fileName :   documentContent.fileName()

    property alias      textFlickable   :   textFlickable
    property alias      fileInfo        :   info

    signal      focused(int identity);

    id                  :   doc

    function    save(){
        documentContent.save()
    }

    function    error(errObj){
        var     row = errObj.row
        var     column = errObj.column
        var     message = errObj.message

        lineNumerator.newError(errObj)
    }

    function    clearErrors(){
        lineNumerator.clearErrors()
    }

    FileInfo{
        id              :   info
        file            :   doc.absolutePath
    }

    DocumentStyle{
        id              :   style
        editorSettings  :   EditorSettings
        textDocument    :   textFlickable.textArea.textDocument
    }

    DocumentContent     {
        id              :   documentContent
        absolutePath    :   doc.absolutePath
        textDocument    :   textFlickable.textArea.textDocument
    }

    LineNumerator       {
        id              :   lineNumerator
        width           :   50
        target          :   textFlickable
        anchors.top     :   parent.top
        anchors.bottom  :   parent.bottom
    }

    FlickableTextArea   {
        id                      :   textFlickable
        anchors.left            :   lineNumerator.right
        anchors.top             :   parent.top
        anchors.bottom          :   parent.bottom
        anchors.right           :   parent.right
        textArea.text           :   documentContent.content
        textArea.onActiveFocusChanged   :   focused(identity)
        textArea.readOnly       :   doc.isReadOnly
        textArea.font.family    :   FontCollection.editorFont
        textArea.font.pointSize :   EditorSettings.fontPointSize
    }

    Item {
        id                      :   modifiedIndicatorContainer
        z                       :   5
        anchors.right           :   parent.right
        anchors.rightMargin     :   10
        anchors.bottom          :   parent.bottom
        anchors.bottomMargin    :   10
        width                   :   20
        height                  :   20
        opacity                 :   textFlickable.modified ? 1 : 0
        ToolTip.visible         :   area.containsMouse
        ToolTip.text            :   "Döküman kaydedilmedi"

        Behavior on opacity{
            NumberAnimation{

            }
        }

        Rectangle   {
            id          :   modifiedIndicatorVisual
            anchors.fill:   parent
            radius      :   height * 0.5
            border.width:   1
            color       :   textFlickable.modified ? "#ff1a00" : "#28A828"
            antialiasing:   true
            opacity     :   0.9
        }

        MouseArea   {
            id              :   area
            anchors.fill    :   parent
            hoverEnabled    :   true
        }
    }
}
