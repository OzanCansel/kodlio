import QtQuick 2.0
import Kodlio 1.0

Document {

    ArduinoHighlighter{
        id          :   highlighter
        document    :   textFlickable.textArea.textDocument
    }

    textFlickable.modified  :   highlighter.modified
}
