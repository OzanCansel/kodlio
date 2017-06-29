#ifndef INTERNETACCESSIBILITY_H
#define INTERNETACCESSIBILITY_H

#include <QNetworkConfigurationManager>
#include <QQuickItem>

class InternetAccessibility : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(bool online READ online NOTIFY onlineChanged)

public:

    static void registerQmlType();
    InternetAccessibility(QQuickItem *parent = Q_NULLPTR);
    bool        online();

signals:

    void        onlineChanged();

private slots:

    void        internetStatusChanged(bool enabled);

private:

    void        setOnline(bool enabled);

    QNetworkConfigurationManager    _man;
    bool                            _online;
};

#endif // INTERNETACCESSIBILITY_H
