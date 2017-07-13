#ifndef EDITORHIGHLIGHT_H
#define EDITORHIGHLIGHT_H

#include <QQuickItem>
#include <QQuickTextDocument>
#include "arduinohighlighter.h"

class ArduinoHighlightItem : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument* document READ document WRITE setDocument)
    Q_PROPERTY(bool modified READ modified NOTIFY onModifiedChanged)

public:

    static void     registerQmlType();
    ArduinoHighlightItem(QQuickItem *parent = Q_NULLPTR);

    QQuickTextDocument*     document();
    void                    setDocument(QQuickTextDocument  *val);
    bool                    modified();

private slots:

    void                    contentChanged(bool enabled);

signals:

    void                    onModifiedChanged();

private:

    bool                    _changed;

    QQuickTextDocument*     _document;
    ArduinoHighlighter             _highlighter;

};

#endif // EDITORHIGHLIGHT_H
