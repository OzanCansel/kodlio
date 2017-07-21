#include "editorsettings.h"
#include <QApplication>

static QObject* editorSettingsSingletonProvider(QQmlEngine *engine , QJSEngine *scriptEngine){
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    EditorSettings  *settings = new EditorSettings();
    return settings;
}

void EditorSettings::registerQmlType(){
    qmlRegisterSingletonType<EditorSettings>("Kodlio" , 1 , 0 , "EditorSettings" , editorSettingsSingletonProvider);
}

EditorSettings::EditorSettings(QQuickItem *parent) : Options(parent)    {
    setFile(QString("%0/%1").arg(QApplication::applicationDirPath()).arg("editor-settings.json"));
    load();
}

void EditorSettings::setTabSize(int val){
    set(TAB_SIZE_LABEL , QVariant(val));
    save();
    emit tabSizeChanged();
}

void EditorSettings::setFontPointSize(int pointSize){
    set(FONT_POINT_SIZE_LABEL , QVariant(pointSize));
    save();
    emit fontPointSizeChanged();
}

int EditorSettings::tabSize(){
    return get(TAB_SIZE_LABEL).toInt();
}

int EditorSettings::fontPointSize(){
    return get(FONT_POINT_SIZE_LABEL).toInt();
}
