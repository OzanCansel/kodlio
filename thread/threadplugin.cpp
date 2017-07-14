#include "threadplugin.h"
#include "avr/avrtoolchainthread.h"

void ThreadPlugin::attach(){
    AvrToolchainThread::registerQmlType();
}

ThreadPlugin::ThreadPlugin()
{

}
