#ifndef EDITORHIGHLIGHT_H
#define EDITORHIGHLIGHT_H

#include <QQuickItem>
#include <QQuickTextDocument>
#include "highlighter.h"

class EditorHighlight : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument* document READ document WRITE setDocument)
    Q_PROPERTY(bool changed READ changed WRITE setChanged NOTIFY onChangedChanged)

public:

    static void     registerQmlType();

    EditorHighlight(QQuickItem *parent = Q_NULLPTR);

    QQuickTextDocument*     document();
    void                    setDocument(QQuickTextDocument  *val);
    bool                    changed();
    void                    setChanged(bool changed = false);

signals:

    void                    onChangedChanged();

private:

    bool                    _changed;

    QQuickTextDocument*     _document;
    Highlighter             _highlighter;

};

#endif // EDITORHIGHLIGHT_H
