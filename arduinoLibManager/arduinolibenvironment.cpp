#include "arduinolibenvironment.h"

ArduinoLibEnvironment::ArduinoLibEnvironment(QQuickItem *parent) : Environment(parent)
{
    set("installedLibsDir" , get("appStartDir").append("/arduino/libs"));
}
