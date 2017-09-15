#ifndef SYNCREQUEST_H
#define SYNCREQUEST_H

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QQuickItem>
#include <QNetworkAccessManager>
#include <QTimer>

class RoboskopNetworkAccessManager : public QNetworkAccessManager
{

    Q_OBJECT

public:

    RoboskopNetworkAccessManager(QObject *parent = Q_NULLPTR);
    QNetworkReply*    getSync(const QNetworkRequest &req , int timeout = 10000);

    bool        timedOut();

private slots:

    void        requestTimedOut();

private:

    QTimer      _timeoutTimer;
    bool        _timedOut;

};

#endif // SYNCREQUEST_H
