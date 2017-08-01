#include "cloudplugin.h"
#include "cloud.h"

void CloudPlugin::attach(){
    Cloud::registerQmlType();
}

CloudPlugin::CloudPlugin()
{

}
