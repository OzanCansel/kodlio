#include "projectplugin.h"
#include "projectwatcher.h"
#include "arduino/arduinoprojectwatcher.h"

ProjectPlugin::ProjectPlugin()
{

}

void ProjectPlugin::attach(){
    ProjectWatcher::registerQmlType();
    ArduinoProjectWatcher::registerQmlType();
}
