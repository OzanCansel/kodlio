import QtQuick 2.0
import QtQuick.Controls 2.1

TextField {

    property alias backgroundRect   :   back

    background  :   Rectangle{
            id              :   back
            radius          :   5
            border.width    :   1
    }
}
