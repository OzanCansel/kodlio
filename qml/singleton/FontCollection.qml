pragma Singleton
import QtQuick 2.0

Item {
    readonly property string    documentHeaderFont  :   ""
    readonly property string    editorFont          :   ""
    readonly property string    messageFont         :   ""

    FontLoader{
        id      :   editorFont
        source  :   "/res/font/inconsolata.otf"
    }

    FontLoader{
        id      :   documentHeaderFont
        source  :   "/res/font/ubuntu-mono-r.ttf"
    }
}
