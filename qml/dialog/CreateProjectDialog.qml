import QtQuick 2.0
import QtQuick.Controls 2.1
import Kodlio 1.0
import "../form"
import "../singleton"

Dialog   {

    property    ProjectManager  manager :   ({})
    property    ProjectOptions  options :   ({})

    id          :   dialog
    x           :   (parent.width / 2) - (width / 2)
    y           :   (parent.height / 2) - (height / 2)
    modal       :   true
    closePolicy :   Popup.CloseOnEscape | Popup.CloseOnReleaseOutside

    contentItem :   CreateProjectForm{
            id      :   form
            manager :   dialog.manager
            options :   dialog.options
    }

    background  :   Image{
        source      :   "/res/icon/backgroundpattern.png"
        fillMode    :   Image.Tile
    }

    Connections{
        target              :   manager
        onProjectCreated    :   close()
    }
}
