#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H

#include <QQuickItem>
#include "options.h"

#define FONT_POINT_SIZE_LABEL       "fontPointSize"
#define TAB_SIZE_LABEL              "tabSize"
#define FONT_FAMILY                 "family"

class EditorSettings : public Options
{

    Q_OBJECT
    Q_PROPERTY(int tabSize READ tabSize WRITE setTabSize NOTIFY tabSizeChanged)
    Q_PROPERTY(int fontPointSize READ fontPointSize WRITE setFontPointSize NOTIFY fontPointSizeChanged)

public:

    static void registerQmlType();
    EditorSettings(QQuickItem *parent = Q_NULLPTR);
    void            setTabSize(int val);
    void            setFontPointSize(int pointSize);
    int             tabSize();
    int             fontPointSize();

signals:

    void            tabSizeChanged();
    void            fontPointSizeChanged();

};

#endif // EDITORSETTINGS_H
