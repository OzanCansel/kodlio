import QtQuick 2.0
import QtQuick.Controls 2.2

Menu {
    id      :   menu
    enter   :  Transition {
        NumberAnimation{
            property        :   "height"; from : 0; to : menu.implicitHeight
        }
    }
}
