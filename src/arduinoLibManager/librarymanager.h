#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QQuickItem>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include "arduinolibdescription.h"

class LibraryManager : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(bool isDownloading READ isDownloading NOTIFY isDownloadingChanged)
    Q_PROPERTY(double downloadingProgress READ downloadingProgress NOTIFY downloadingProgressChanged)
    Q_PROPERTY(QString downloadingLibName READ downloadingLibName NOTIFY downloadingLibNameChanged)
    Q_PROPERTY(QString downloadingLibVersion READ downloadingLibVersion NOTIFY downloadingLibVersionChanged)

public:

    static void         registerQmlType();
    LibraryManager(QQuickItem *parent = Q_NULLPTR);
    bool            isDownloading();
    double          downloadingProgress();
    QString         downloadingLibName();
    QString         downloadingLibVersion();
    QList<ArduinoLibDescription*>*      localLibs();
    QList<ArduinoLibDescription*>*      onlineLibs();
    QList<ArduinoLibDescription*>&       getLocalLibs();


public slots:


    void            filterOnlineLibs(QString name);
    void            filterLocalLibs(QString name);
    void            retrieveOnlineLibraries();
    void            retrieveLocalLibraries();
    void            installLibs(QVariantList    libs);
    void            removeLibs(QVariantList     libs);

private slots:

    void    downloadStarted();
    void    downloadProgress(double progress);
    void    downloadEnd();

signals:

    void    onlineLibsChanged();
    void    localLibsChanged();
    void    filterLocalResult(QVariantMap    item);
    void    filterOnlineResult(QVariantMap item);
    void    libDownloadProgress(QString libName , QString version , double multiplier);
    void    downloadingProgressChanged();
    void    downloadingLibNameChanged();
    void    downloadingLibVersionChanged();
    void    isDownloadingChanged();
    void    libInstalledSuccessfully(ArduinoLibDescription *desc);
    void    libInstallErrorOccurred(ArduinoLibDescription *desc);
    void    libRemovedSuccessfully(ArduinoLibDescription *desc);
    void    libRemoveErrorOcurred();
    void    retrieveOnlineLibsInternetError();
    void    libNotRemovable();


private:

    QList<ArduinoLibDescription*>    _onlineLibs;
    QList<ArduinoLibDescription*>    _localLibs;

    ArduinoLibDescription*  retrieveDescFromOnline(QString name , QString version);
    ArduinoLibDescription*  retrieveDescFromLocal(QString name , QString version);
    bool                    libExists(QString name , QString version);
    void                    setDownloading(bool enabled);
    void                    setDownloadingProgress(double progress);
    void                    setDownloadingLibName(QString &libName);
    void                    setDownloadingLibVersion(QString &version);

    QString                 _downloadingLibName;
    QString                 _downloadingLibVersion;
    bool                    _isDownloading;
    double                  _downloadingProgress;

};

#endif // LIBRARYMANAGER_H
