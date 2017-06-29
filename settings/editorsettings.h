#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H

#include "jsonstorage.h"
#include <QQuickItem>

class EditorSettings : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
    Q_PROPERTY(int tabSize READ tabSize WRITE setTabSize NOTIFY tabSizeChanged)

public:

    EditorSettings(QQuickItem *parent = Q_NULLPTR);
    static      EditorSettings  *self;
    static      EditorSettings*  getInstance();
    void        setFontSize(int val);
    void        setTabSize(int val);
    int         fontSize();
    int         tabSize();

signals:

    void    fontSizeChanged();
    void    tabSizeChanged();

public slots:

    void        saveSettings();

private:

    JsonStorage         _storage;
};

#endif // EDITORSETTINGS_H
