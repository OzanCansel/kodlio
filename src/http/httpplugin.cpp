#include "httpplugin.h"
#include <QtQml>
#include "internetaccessibility.h"

void HttpPlugin::attach(){
    InternetAccessibility::registerQmlType();
}

HttpPlugin::HttpPlugin()
{

}
