#include "editorplugin.h"
#include "documentcontent.h"
#include "documentstyle.h"
#include "editorsettings.h"
#include "linenumber.h"

void  EditorPlugin::attach(){
    DocumentContent::registerQmlType();
    DocumentStyle::registerQmlType();
    EditorSettings::registerQmlType();
    LineNumber::registerQmlType();
}

EditorPlugin::EditorPlugin()
{

}
