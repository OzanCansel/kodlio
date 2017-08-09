#include "threadplugin.h"
#include "avr/avrtoolchainthread.h"
#include "avr/roboskop/roboskoptoolchainthread.h"
#include "cloud/cloudthread.h"

void ThreadPlugin::attach(){
    AvrToolchainThread::registerQmlType();
    RoboskopToolchainThread::registerQmlType();
    CloudThread::registerQmlType();
}

ThreadPlugin::ThreadPlugin()
{

}
