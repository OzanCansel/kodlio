#include "editorplugin.h"
#include "documentcontent.h"
#include "documentstyle.h"
#include "editorsettings.h"

void  EditorPlugin::attach(){
    DocumentContent::registerQmlType();
    DocumentStyle::registerQmlType();
    EditorSettings::registerQmlType();
}

EditorPlugin::EditorPlugin()
{

}
