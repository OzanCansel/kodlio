#include "highlightplugin.h"
#include "highlightitem.h"
#include "arduinohighlightitem.h"

void HighlightPlugin::attach(){
    HighlightItem::registerQmlType();
    ArduinoHighlightItem::registerQmlType();
}

HighlightPlugin::HighlightPlugin()
{

}
