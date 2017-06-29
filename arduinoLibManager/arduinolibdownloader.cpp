#include "arduinolibdownloader.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

ArduinoLibDownloader::ArduinoLibDownloader(QQuickItem *parent) : QQuickItem(parent)
{
    _timeoutTimer.setInterval(10000);

    connect(&_timeoutTimer , SIGNAL(timeout()) , this , SLOT(timedOut()));
}

bool ArduinoLibDownloader::download(QString &url){

    _downloadedFile.clear();

    QNetworkAccessManager    man;
    QNetworkReply   *reply = man.get(QNetworkRequest(QUrl(url)));
    connect(reply , SIGNAL(downloadProgress(qint64,qint64)) , this , SLOT(progress(qint64 , qint64)));
    connect(reply , SIGNAL(finished()) , this , SLOT(dFinished()));

    emit downloadStarted();
    _timedOut   =   false;
    _timeoutTimer.start();
    //Indirmenin bitmesi bekleniyor
    QEventLoop  loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    connect(&_timeoutTimer , SIGNAL(timeout()) , &loop , SLOT(quit()));
    loop.exec();

    _downloadedFile = reply->readAll();

    return !_timedOut;
}

bool ArduinoLibDownloader::writeTo(QString path){

    if(_downloadedFile.isEmpty()){
        qDebug() << "ArduinoLibDownloader::writeTo() Herhangi bir dosya indirilmemis.";
        return false;
    }

    QFile   f(path);

    if(!f.open(QFile::WriteOnly)){
        qDebug() << "ArduinoLibDonwloader::writeTo() Dosya acilamiyor -> " << path;

        return false;
    }

    //Dosyaya yaziliyor
    f.write(_downloadedFile);
    f.close();

    return true;
}

void ArduinoLibDownloader::progress(qint64 read, qint64 total){
    _timeoutTimer.stop();
    _timeoutTimer.start();
    double  percentage = read / (double)total;
    qDebug() << "ArduinoLibDownloader::progress -> " << percentage * 100 << "%";
    emit downloadProgress(percentage);
}

void ArduinoLibDownloader::dFinished(){
    qDebug() << "ArduinoLibDownloader::downloadFinished() Indirme bitti.";
    emit downloadFinished();
}

void ArduinoLibDownloader::setTimeout(int timeout){
    _timeoutTimer.setInterval(timeout);
}

void ArduinoLibDownloader::timedOut(){
    _timedOut = true;
}
