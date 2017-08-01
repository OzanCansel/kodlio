#include "threadplugin.h"
#include "avr/avrtoolchainthread.h"
#include "cloud/cloudthread.h"

void ThreadPlugin::attach(){
    AvrToolchainThread::registerQmlType();
    CloudThread::registerQmlType();
}

ThreadPlugin::ThreadPlugin()
{

}
