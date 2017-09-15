#include "highlightitem.h"
#include <QtQml>

void HighlightItem::registerQmlType(){
    qmlRegisterType<HighlightItem>("Kodlio" , 1 , 0 , "Highlighter");
}

HighlightItem::HighlightItem(QQuickItem *parent) : QQuickItem(parent)   {

}
