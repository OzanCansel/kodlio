#include "arduinohighlightitem.h"
#include <QDebug>

void ArduinoHighlightItem::registerQmlType(){
    qmlRegisterType<ArduinoHighlightItem>("Kodlio", 1, 0, "ArduinoHighlighter");
}

ArduinoHighlightItem::ArduinoHighlightItem(QQuickItem *parent) : QQuickItem(parent)
{
    _document = Q_NULLPTR;
}

QQuickTextDocument* ArduinoHighlightItem::document(){
    return _document;
}

void ArduinoHighlightItem::setDocument(QQuickTextDocument *val){
    _document = val;

    _highlighter.setDocument(_document->textDocument());

    connect(_document->textDocument() , SIGNAL(modificationChanged(bool)) , this , SLOT(contentChanged(bool)));
}

bool ArduinoHighlightItem::modified(){
    if(_document != NULL)
        return _document->textDocument()->isModified();
    else
        return false;
}

void ArduinoHighlightItem::contentChanged(bool enabled){
    emit onModifiedChanged();
}
