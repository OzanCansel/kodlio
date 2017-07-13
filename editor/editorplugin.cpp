#include "editorplugin.h"
#include "documentcontent.h"

void  EditorPlugin::attach(){
    DocumentContent::registerQmlType();
}

EditorPlugin::EditorPlugin()
{

}
