#include "editorsettings.h"

EditorSettings* EditorSettings::self = Q_NULLPTR;

EditorSettings* EditorSettings::getInstance(){
    if(self == Q_NULLPTR)
        self = new EditorSettings();

    return self;
}

EditorSettings::EditorSettings(QQuickItem *parent) : QQuickItem(parent){
    _storage.setFile("settings.json");
    _storage.load();
}

void EditorSettings::saveSettings(){
    _storage.save();
}

void EditorSettings::setFontSize(int val){
    _storage.set("fontSize" , QVariant(val));
    emit fontSizeChanged();
}

void EditorSettings::setTabSize(int val){
    _storage.set("tabSize",  QVariant(val));
    emit tabSizeChanged();
}

int EditorSettings::fontSize(){
    if(_storage.get("fontSize").isNull())
        return 12;
    else
        return _storage.get("fontSize").toInt();
}

int EditorSettings::tabSize(){
    if(_storage.get("tabSize").isNull())
        return 2;
    else
        return _storage.get("tabSize").toInt();
}
