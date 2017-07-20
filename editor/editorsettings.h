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
    Q_PROPERTY(QString family READ family WRITE setFamily NOTIFY familyChanged)

public:

    static void registerQmlType();
    EditorSettings(QQuickItem *parent = Q_NULLPTR);
    void            setTabSize(int val);
    void            setFontPointSize(int pointSize);
    void            setFamily(QString val);
    int             tabSize();
    int             fontPointSize();
    QString         family();

signals:

    void            tabSizeChanged();
    void            fontPointSizeChanged();
    void            familyChanged();

};

#endif // EDITORSETTINGS_H
