#include "globalplugin.h"
#include "environment.h"

void GlobalPlugin::attach(){
    Environment::registerQmlType();
}

GlobalPlugin::GlobalPlugin()
{

}
