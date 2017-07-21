import QtQuick 2.0
import QtQuick.Controls 2.2

import "../control"
import "../editor"

Item {

    property Document   currentDocument :   ({})

    id          :   editorMenu
    width       :   childrenRect.width + 5
    height      :   childrenRect.height + 5

    Row {
        width               :   childrenRect.width
        height              :   childrenRect.height
        anchors.centerIn    :   parent
        z                   :   2

        ToolImageButton {
            id              :   undoButton
            src             :   currentDocument.textFlickable.textArea.canUndo ? "/res/icon/undo-available.png" :  "/res/icon/undo-unavailable.png"
            color           :   "transparent"
            onClicked       :   currentDocument.textFlickable.textArea.undo()
            ToolTip.visible :   hovered
            ToolTip.text    :   "Geri Al (Ctrl+Z)"
        }

        ToolImageButton{
            id          :   redoButton
            src         :   currentDocument.textFlickable.textArea.canRedo ? "/res/icon/redo-available.png" :  "/res/icon/redo-unavailable.png"
            color       :   "transparent"
            onClicked   :   currentDocument.textFlickable.textArea.redo()
            ToolTip.visible :   hovered
            ToolTip.text    :   "İleri al (Ctrl+Shift+Z)"
        }

        ToolImageButton{
            id          :   saveButton
            src         :   currentDocument.modified ? "/res/icon/save-modified-icon.png" :  "/res/icon/save-icon.png"
            color       :   "transparent"
            onClicked   :   currentDocument.save()
            ToolTip.visible :   hovered
            ToolTip.text    :   "Dökümanı kaydet (Ctrl+S)"
        }
    }
}
