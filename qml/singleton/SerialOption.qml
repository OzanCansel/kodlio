pragma Singleton
import QtQuick 2.0
import Kodlio 1.0

Item {
    property alias  option  :   options
    property alias  scanner :   scanner

    SerialOptions{
        id      :   options
        onPortNameChanged   :   console.log("Port Changed -> " + portName)
    }

    SerialPortScanner{
        id      :   scanner
    }
}
