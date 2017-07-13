import QtQuick 2.0

Item {

    readonly property int    idx :   0

    function    generate(){
        idx++
        return idx
    }

}
