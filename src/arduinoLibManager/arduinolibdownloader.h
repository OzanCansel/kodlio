#ifndef ARDUINOLIBDOWNLOADER_H
#define ARDUINOLIBDOWNLOADER_H

#include <QTimer>
#include <QByteArray>
#include <QQuickItem>

class ArduinoLibDownloader : public  QQuickItem
{

    Q_OBJECT

public:

    ArduinoLibDownloader(QQuickItem *parent = Q_NULLPTR);
    void            setTimeout(int timeout);
    bool            download(QString &url);
    bool            writeTo(QString outputPath);

signals:

    void        downloadStarted();
    void        downloadProgress(double percentage);
    void        downloadFinished();

private slots:

    void        progress(qint64 read, qint64 total);
    void        dFinished();
    void        timedOut();

private:

    QByteArray  _downloadedFile;
    QTimer      _timeoutTimer;
    bool        _timedOut;

};

#endif // ARDUINOLIBDOWNLOADER_H
