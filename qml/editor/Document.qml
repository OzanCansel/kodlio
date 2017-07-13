import QtQuick 2.7
import Kodlio 1.0
import "../singleton"

Item {

    property int        identity        :   0
    property string     relativePath    :   ""
    property string     absolutePath    :   ""
    property string     type            :   ""
    readonly property   string fileName :   documentContent.fileName()

    property alias      textFlickable   :   textFlickable
    property alias      fileInfo        :   info

    signal      focused(int identity);

    id                  :   doc

    function    save(){
        documentContent.save()
    }

    FileInfo{
        id              :   info
        file            :   doc.absolutePath
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
        id                  :   textFlickable
        anchors.left        :   lineNumerator.right
        anchors.top         :   parent.top
        anchors.bottom      :   parent.bottom
        anchors.right       :   parent.right
        textArea.text       :   documentContent.content
        textArea.onActiveFocusChanged   :   focused(identity)
    }
}
