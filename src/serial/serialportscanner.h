#ifndef SERIALPORTSCANNER_H
#define SERIALPORTSCANNER_H

#include <QQuickItem>
#include <QHash>

class SerialPortScanner : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QVariantList ports READ ports NOTIFY portsChanged)

public:

    static void     registerQmlType();
    SerialPortScanner(QQuickItem *parent = Q_NULLPTR);
    QVariantList    ports();

    struct IdPair{
        int vid;
        int pid;
        IdPair(int vid, int pid): vid(vid), pid(pid) {}
    };

    typedef struct{
        QList<IdPair>   pairs;
        QString         board;
    } PortInfo;

public slots:

    void            refresh();

signals:

    void        portsChanged();

private:

    QVariantList            _variants;
    QList<PortInfo>         _definedBoards;

    QString    retrieveBoardName(int vid , int pid);
};

#endif // SERIALPORTSCANNER_H
