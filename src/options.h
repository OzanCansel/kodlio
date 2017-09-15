#ifndef OPTIONS_H
#define OPTIONS_H

#include <QQuickItem>
#include <QVariantMap>

class Options : public QQuickItem
{

    Q_OBJECT

public:

    static void     registerQmlType();
    Options(QQuickItem *parent = Q_NULLPTR);

public slots:

    void            set(QString key , QVariantMap val);
    void            set(QString key, QVariant val);
    QVariant        get(QString key , bool ensureExists = false) const;
    bool            load();
    bool            save();

protected:

    QVariantMap     _map;
    void            setFile(QString val);
    QString         file();

private:

    QString         _file;

};

#endif // OPTIONS_H
