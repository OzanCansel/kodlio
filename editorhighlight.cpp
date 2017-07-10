#include "editorhighlight.h"
#include <QDebug>

void EditorHighlight::registerQmlType(){
    qmlRegisterType<EditorHighlight>("Kodlio", 1, 0, "ArduinoHighlighter");
}

EditorHighlight::EditorHighlight(QQuickItem *parent) : QQuickItem(parent)
{
    _document = Q_NULLPTR;
}

QQuickTextDocument* EditorHighlight::document(){
    return _document;
}

void EditorHighlight::setDocument(QQuickTextDocument *val){
    _document = val;

    _highlighter.setDocument(_document->textDocument());

    connect(_document->textDocument() , SIGNAL(modificationChanged(bool)) , this , SLOT(contentChanged(bool)));
}

bool EditorHighlight::modified(){
    if(_document != NULL)
        return _document->textDocument()->isModified();
    else
        return false;
}

void EditorHighlight::contentChanged(bool enabled){
    emit onModifiedChanged();
}
