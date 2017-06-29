#include "editorhighlight.h"
#include <QDebug>

void EditorHighlight::registerQmlType(){
    qmlRegisterType<EditorHighlight>("Roboskop", 1, 0, "HighlightComponent");
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
}

bool EditorHighlight::changed(){
    return _changed;
}

void EditorHighlight::setChanged(bool changed){
    _changed = changed;

    emit onChangedChanged();
}
