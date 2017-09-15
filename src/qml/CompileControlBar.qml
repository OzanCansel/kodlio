import QtQuick 2.0
import QtQuick.Controls 2.1
import Kodlio 1.0
import "project"
import "singleton"
import "control"

Rectangle {

    property Project    currentProject      :   ({})

    color           :  "transparent"

    signal compileRequired()
    signal uploadRequired()

    Column{

        width           :   parent.width
        height          :   100
        anchors.bottom  :   parent.bottom
        anchors.bottomMargin    :   50
        spacing         :   10

        IdeMenuItem {
            mouseArea.onClicked :   compileRequired()
            width               :   parent.width
            height              :   48
            color               :   Theme.compileButtonBackgroundColor
            img.source          :   "/res/icon/compile.png"
            txt.text            :   "Derle"
            enabled             :   !currentProject.toolchain.busy
            tooltipEnabled      :   true
            tooltipText         :   "Projenizi derlemek için tıklayınız"
        }

        IdeMenuItem {
            mouseArea.onClicked :   {
                uploadRequired()
            }
            width               :   parent.width
            height              :   48
            color               :   Theme.uploadButtonBackgroundColor
            img.source          :   "/res/icon/upload.png"
            txt.text            :   "Yükle"
            enabled             :   !currentProject.runner.busy
            tooltipEnabled      :   true
            tooltipText         :   "Projenizi mikroişlemcinize yüklemek için tıklayınız"
        }
    }
}
