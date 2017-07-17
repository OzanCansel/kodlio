#include "serialplugin.h"
#include "serialoptions.h"
#include "serialport.h"
#include "serialportscanner.h"

void SerialPlugin::attach(){
    SerialOptions::registerQmlType();
    SerialPort::registerQmlType();
    SerialPortScanner::registerQmlType();
}

SerialPlugin::SerialPlugin()
{

}
