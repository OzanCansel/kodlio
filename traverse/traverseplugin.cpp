#include "traverseplugin.h"
#include "projecttraverse.h"

void TraversePlugin::attach(){
    ProjectTraverse::registerQmlType();
}

TraversePlugin::TraversePlugin()
{

}
