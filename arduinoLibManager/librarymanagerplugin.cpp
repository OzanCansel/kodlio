#include "librarymanagerplugin.h"
#include "librarymanager.h"

void LibraryManagerPlugin::attach(){
    LibraryManager::registerQmlType();
}

LibraryManagerPlugin::LibraryManagerPlugin()
{

}
