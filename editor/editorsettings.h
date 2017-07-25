#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H

#include <QQuickItem>
#include "options.h"

#define FONT_POINT_SIZE_LABEL       "fontPointSize"
#define TAB_SIZE_LABEL              "tabSize"
#define ASSISTANT_ENABLED_LABEL     "assistantEnabled"

class EditorSettings : public Options
{

    Q_OBJECT
    Q_PROPERTY(int tabSize READ tabSize WRITE setTabSize NOTIFY tabSizeChanged)
    Q_PROPERTY(int fontPointSize READ fontPointSize WRITE setFontPointSize NOTIFY fontPointSizeChanged)
    Q_PROPERTY(bool assistantEnabled READ assistantEnabled WRITE setAssistantEnabled NOTIFY assistantEnabledChanged)

public:

    static void registerQmlType();
    EditorSettings(QQuickItem *parent = Q_NULLPTR);
    void            setTabSize(int val);
    void            setFontPointSize(int pointSize);
    void            setAssistantEnabled(bool enabled);
    int             tabSize();
    int             fontPointSize();
    bool            assistantEnabled();

signals:

    void            tabSizeChanged();
    void            fontPointSizeChanged();
    void            assistantEnabledChanged();

};

#endif // EDITORSETTINGS_H
