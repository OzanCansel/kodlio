#ifndef OPTIONS_H
#define OPTIONS_H

#include <QQuickItem>
#include <QVariantMap>

class Options : public QQuickItem
{

    Q_OBJECT

public:

    Options(QQuickItem *parent = Q_NULLPTR);

public slots:

    void            set(QString key , QVariantMap val);
    void            set(QString key, QVariant val);
    QVariant        get(QString key);

protected:

    QVariantMap     _map;

};

#endif // OPTIONS_H
