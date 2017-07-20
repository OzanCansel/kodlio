#include "documentstyle.h"
#include <QtQml>
#include <QTextOption>
#include <QFontMetrics>

void DocumentStyle::registerQmlType(){
    qmlRegisterType<DocumentStyle>("Kodlio" , 1 , 0 , "DocumentStyle");
}

DocumentStyle::DocumentStyle(QQuickItem *parent) : QQuickItem(parent)  {
    _doc = Q_NULLPTR;
}

void    DocumentStyle::setTextDocument(QQuickTextDocument *doc){
    _doc = doc;
    applySettingsToDoc();
    emit textDocumentChanged();
}

QQuickTextDocument* DocumentStyle::textDocument(){
    return _doc;
}

void DocumentStyle::applySettingsToDoc(){

    if(_doc == Q_NULLPTR)
        return;

    if(_settings == Q_NULLPTR)
        return;

    applyInitialSettings();
    applyTabSize();
    applyFont();
}

void DocumentStyle::setEditorSettings(EditorSettings *val){
    _settings = val;
    connect(_settings , SIGNAL(fontPointSizeChanged()) , this , SLOT(pointSizeChanged()));
    connect(_settings , SIGNAL(tabSizeChanged()), this , SLOT(tabSizeChanged()));
    connect(_settings , SIGNAL(familyChanged()) , this , SLOT(familyChanged()));
    applySettingsToDoc();
    emit editorSettingsChanged();
}

EditorSettings* DocumentStyle::editorSettings(){
    return _settings;
}

void DocumentStyle::applyInitialSettings(){
    QTextDocument*  doc = _doc->textDocument();
    QFont   f = doc->defaultFont();
    f.setFixedPitch(true);
    doc->setDefaultFont(f);
}

void DocumentStyle::applyTabSize(){
    QTextDocument*  doc = _doc->textDocument();
    QFont   font = doc->defaultFont();
    QFontMetrics    m(font);
    QTextOption     opt = doc->defaultTextOption();
    opt.setTabStop(m.width(' ') * _tabSize);
    doc->setDefaultTextOption(opt);
}

void DocumentStyle::applyFont(){
    QTextDocument*  doc = _doc->textDocument();
    QFont   font = doc->defaultFont();
    font.setPointSize(_pointSize);
    font.setFamily(_family);
    doc->setDefaultFont(font);
}

void DocumentStyle::familyChanged(){
    _family = _settings->family();
    applyFont();
}

void DocumentStyle::tabSizeChanged(){
    _tabSize = _settings->tabSize();
    applyTabSize();
}

void DocumentStyle::pointSizeChanged(){
    _pointSize = _settings->fontPointSize();
    applyFont();
}
