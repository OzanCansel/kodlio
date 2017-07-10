pragma Singleton
import QtQuick 2.0

Item {

    readonly property string    documentHeaderFont  :   inconsolata.name
    readonly property string    editorFont          :   ""
    readonly property string    messageFont         :   ubuntuMono.name
    readonly property string    fileTreeFont        :   ubuntuMono.name
    readonly property string    menuFont            :   inconsolata.name
    readonly property string    titleFont           :   ubuntuRegular.name
    readonly property string    buttonFont          :   ubuntuRegular.name
    readonly property string    listItemFont        :   ubuntuRegular.name

    FontLoader{
        id      :   inconsolata
        source  :   "/res/font/inconsolata.otf"
    }

    FontLoader{
        id      :   ubuntuMono
        source  :   "/res/font/ubuntu-mono-r.ttf"
    }

    FontLoader{
        id      :   ubuntuRegular
        source  :   "/res/font/ubuntu-R.ttf"
    }

}
