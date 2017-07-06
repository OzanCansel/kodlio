import QtQuick 2.7
import Kodlio 1.0
import "../singleton"

Item {

    property string     relativePath    :   ""
    property string     absolutePath    :   ""
    property string     type            :   ""
    readonly property   string fileName :   documentContent.fileName()

    property alias      textFlickable   :   textFlickable

    id                  :   doc

    DocumentContent     {
        id              :   documentContent
        absolutePath    :   doc.absolutePath
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
    }

    Shortcut    {
        id                  :   saveShortcut
        sequence            :   StandardKey.Save
        onActivated         :   console.log("save")
    }
}
