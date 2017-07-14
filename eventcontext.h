#ifndef EVENTCONTEXT_H
#define EVENTCONTEXT_H

#include <QQuickItem>

class EventContext : public QQuickItem
{

    Q_OBJECT

public:

    EventContext(QQuickItem *parent = Q_NULLPTR);

public slots:

    void    send(int message , QVariantList args);

signals:

    void    message(int message , QVariantList  args);

};

#endif // EVENTCONTEXT_H
