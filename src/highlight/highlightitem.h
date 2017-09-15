#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <QQuickItem>

class HighlightItem : public QQuickItem
{

public:

    static void registerQmlType();
    HighlightItem(QQuickItem *parent = Q_NULLPTR);

};

#endif // HIGHLIGHT_H
