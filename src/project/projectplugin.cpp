#include "projectplugin.h"
#include "projectoptions.h"
#include "projectwatcher.h"
#include "projectmanager.h"
#include "arduino/arduinoprojectmanager.h"
#include "arduino/arduinoprojectwatcher.h"
#include "arduino/examplesmanager.h"

ProjectPlugin::ProjectPlugin()
{

}

void ProjectPlugin::attach(){
    ProjectOptions::registerQmlType();
    ProjectManager::registerQmlType();
    ArduinoProjectManager::registerQmlType();
    ProjectWatcher::registerQmlType();
    ArduinoProjectWatcher::registerQmlType();
    ExamplesManager::registerQmlType();
}
