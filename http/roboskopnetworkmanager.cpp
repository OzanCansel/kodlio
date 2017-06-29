#include "roboskopnetworkmanager.h"
#include <QEventLoop>

RoboskopNetworkAccessManager::RoboskopNetworkAccessManager(QObject *parent) : QNetworkAccessManager(parent){
    _timedOut = false;
    _timeoutTimer.setInterval(10000);

    connect(&_timeoutTimer , SIGNAL(timeout()) , this , SLOT(requestTimedOut()));
}

QNetworkReply* RoboskopNetworkAccessManager::getSync(const QNetworkRequest &req , int timeout){
    QNetworkReply   *reply = get(req);

    _timedOut = false;
    _timeoutTimer.setInterval(timeout);
    _timeoutTimer.start();
    QEventLoop  loop;
    connect(&_timeoutTimer , SIGNAL(timeout()) , &loop , SLOT(quit()));
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    return reply;
}

void RoboskopNetworkAccessManager::requestTimedOut(){
    _timedOut = true;
}

bool RoboskopNetworkAccessManager::timedOut(){
    return _timedOut;
}
