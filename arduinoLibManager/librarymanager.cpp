#include "librarymanager.h"
#include <QNetworkRequest>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtQml>
#include "http/roboskopnetworkmanager.h"
#include "arduinolibdescription.h"
#include "traverse/filetraverse.h"
#include "arduinolibenvironment.h"
#include "arduinolibdownloader.h"
#include "zip/zip7zextractor.h"
#include "osinfo.h"
#include "exception/environmentvariablenotset.h"
#include "roboskopenvironment.h"

void LibraryManager::registerQmlType(){
    qmlRegisterType<LibraryManager>("Kodlio" , 1 , 0 , "ArduinoLibManager");
}

LibraryManager::LibraryManager(QQuickItem *parent) : QQuickItem(parent)
{
    setDownloadingProgress(0);
}

void LibraryManager::retrieveOnlineLibraries(){
    RoboskopNetworkAccessManager    accesManager;
    QNetworkRequest                 request(QUrl(QString("http://downloads.arduino.cc/libraries/library_index.json")));

    QNetworkReply* reply = accesManager.getSync(request);

    //Istek timeouta duserse hata bildiriliyor
    if(accesManager.timedOut() || reply->bytesAvailable() == 0){
        emit retrieveOnlineLibsInternetError();

        return;
    }

    QJsonArray libJsonArray     =   QJsonDocument::fromJson(reply->readAll()).object()["libraries"].toArray();

    //Onceki liste temizleniyor
    _onlineLibs.clear();

    foreach (QJsonValue val, libJsonArray) {
        ArduinoLibDescription   *desc = new ArduinoLibDescription(this);
        QJsonObject obj = val.toObject();
        //Json parse ediliyor
        desc->deserialize(obj);

        _onlineLibs.append(desc);
    }

    emit onlineLibsChanged();
}

void LibraryManager::retrieveLocalLibraries(){
    ArduinoLibEnvironment   env;

    if(!env.isAssigned("installedLibsDir"))
        EnvironmentVariableNotSet("installedLibsDir").raise();

    _localLibs.clear();

    FileTraverse    traverser;
    QList<TraversedFileInfo> files          =   traverser.traverseRecursively(ArduinoLibEnvironment().get("installedLibsDir"));
    QList<TraversedFileInfo> builtInLibs    =   traverser.traverseRecursively(RoboskopEnvironment::getInstance()->getLibrariesPath());

    files.append(builtInLibs);

    foreach(TraversedFileInfo file , files) {

        //Sadece library.properties dosyalarina bakiliyor
        if(file.info().fileName() != "library.properties")
            continue;

        ArduinoLibDescription   *desc = new ArduinoLibDescription(this);
        QString     fPath   =   file.info().filePath();
        desc->deserialize(fPath);

        _localLibs.append(desc);
    }

    _localLibs.append(new ArduinoLibDescription(RoboskopEnvironment::getInstance()->getCoreEnvironment() , "Arduino", this));

    emit localLibsChanged();
}

void    LibraryManager::filterOnlineLibs(QString name){
    foreach (ArduinoLibDescription *desc, _onlineLibs) {
        if(desc->name().contains(name , Qt::CaseInsensitive))
            emit filterOnlineResult(desc->asVariant());
    }
}

void    LibraryManager::filterLocalLibs(QString name){
    foreach (ArduinoLibDescription *desc, _localLibs) {
        if(desc->name().contains(name , Qt::CaseInsensitive))
            emit filterLocalResult(desc->asVariant());
    }
}

void    LibraryManager::installLibs(QVariantList libs){

    ArduinoLibEnvironment   env;
    OsInfo                  osInfo;
    ArduinoLibDownloader    downloader;
    ZipExtractor            *extractor = new Zip7zExtractor();;

    extractor->setDebugEnabled(true);

    //Ortam degiskeni kontrol ediliyor
    if(!env.isAssigned("installedLibsDir"))
        EnvironmentVariableNotSet("installedLibsDir").raise();

    //Kutuphaneler yukleniyor
    foreach (QVariant m, libs) {
        QVariantMap lib = m.toMap();

        QString     libName =   lib["name"].toString();
        QString     version =   lib["version"].toString();

        ArduinoLibDescription   *desc    =   retrieveDescFromOnline(libName , version);

        if(desc == Q_NULLPTR)
            return;

        //Kutuphane var mi diye kontrol ediliyor
        bool exists = libExists(desc->name() , desc->version());

        //Kutuphane mevcutsa pas geciliyor
        if(exists){
            qDebug() << libName << " mevcut. Pas geciliyor.";
            continue;
        }

        QTemporaryDir   dir;
        QString     downloadFPath = dir.path().append("/").append(desc->name().append(".zip"));
        QString     downloadUrl =   desc->url();

        setDownloadingLibName(libName);
        setDownloadingLibVersion(version);
        connect(&downloader , SIGNAL(downloadProgress(double)) , this , SLOT(downloadProgress(double)));
        connect(&downloader , SIGNAL(downloadStarted()) , this , SLOT(downloadStarted()));
        connect(&downloader , SIGNAL(downloadFinished()) , this , SLOT(downloadEnd()));

        bool downloaded = downloader.download(downloadUrl);

        //Indirme sirasinda hata olustuysa
        if(!downloaded){
            emit libInstallErrorOccurred(desc);
            continue;
        }

        //Dosyaya yaziliyor
        bool written = downloader.writeTo(downloadFPath);

        //Yazma sirasinda hata olustuysa
        if(!written){
            emit libInstallErrorOccurred(desc);
            continue;
        }

        QString     installLibPath = env.get("installedLibsDir");

        bool extracted = extractor->unzip(downloadFPath , installLibPath , true);

        if(extracted)
            emit libInstalledSuccessfully(desc);
        else
            emit libInstallErrorOccurred(desc);
    }

    extractor->deleteLater();
}

void LibraryManager::removeLibs(QVariantList libs){
    ArduinoLibEnvironment   env;

    if(!env.isAssigned("installedLibsDir"))
        EnvironmentVariableNotSet("installedLibsDir").raise();

    foreach (QVariant m, libs) {
        QVariantMap lib = m.toMap();

        QString     libName =   lib["name"].toString();
        QString     version =   lib["version"].toString();

        //Kutuphane bilgileri aliniyor
        ArduinoLibDescription* desc = retrieveDescFromLocal(libName , version);

        //Kutuphane siliniyor
        QDir    libDir(desc->localDir());
        libDir.removeRecursively();

        _localLibs.removeOne(desc);

        emit localLibsChanged();
        emit libRemovedSuccessfully(desc);
    }
}

ArduinoLibDescription* LibraryManager::retrieveDescFromOnline(QString name, QString version){

    foreach (ArduinoLibDescription* desc, _onlineLibs) {
        if(desc->name() == name && desc->version() == version)
            return desc;
    }

    return Q_NULLPTR;
}

ArduinoLibDescription* LibraryManager::retrieveDescFromLocal(QString name, QString version){
    foreach (ArduinoLibDescription *desc, _localLibs) {
        if(desc->name() == name && desc->version() == version)
            return desc;
    }

    return Q_NULLPTR;
}

bool LibraryManager::libExists(QString name, QString version){

    ArduinoLibEnvironment   env;

    if(!env.isAssigned("installedLibsDir"))
        EnvironmentVariableNotSet("installedLibsDir").raise();

    FileTraverse    traverser;
    QList<TraversedFileInfo> files = traverser.traverseRecursively(ArduinoLibEnvironment().get("installedLibsDir"));

    foreach(TraversedFileInfo file , files){

        //Sadece library.properties dosyalarina bakiliyor
        if(file.info().fileName() != "library.properties")
            continue;

        ArduinoLibDescription   desc;
        QString     fPath   =   file.info().filePath();
        desc.deserialize(fPath);

        if(desc.name() == name && desc.version() == version)
            return true;
    }

    return false;
}

//Setter
void LibraryManager::setDownloading(bool enabled){
    _isDownloading = enabled;
    emit isDownloadingChanged();
}

void LibraryManager::setDownloadingProgress(double progress){
    _downloadingProgress = progress;

    emit downloadingProgressChanged();
}

void LibraryManager::setDownloadingLibName(QString &libName){
    _downloadingLibName = libName;
    emit downloadingLibNameChanged();
}

void LibraryManager::setDownloadingLibVersion(QString &version){
    _downloadingLibVersion = version;
    emit downloadingLibVersionChanged();
}

//Getter
QString LibraryManager::downloadingLibName(){
    return _downloadingLibName;
}

QString LibraryManager::downloadingLibVersion(){
    return _downloadingLibVersion;
}

bool    LibraryManager::isDownloading(){
    return _isDownloading;
}

double LibraryManager::downloadingProgress(){
    return _downloadingProgress;
}

QList<ArduinoLibDescription*>*   LibraryManager::localLibs(){
    return &_localLibs;
}

QList<ArduinoLibDescription*>* LibraryManager::onlineLibs(){
    return &_onlineLibs;
}

QList<ArduinoLibDescription*>   LibraryManager::getLocalLibs(){
    return _localLibs;
}

/*Slots*/
void LibraryManager::downloadStarted(){
    setDownloading(true);
}

void LibraryManager::downloadProgress(double progress){
    setDownloadingProgress(progress);
}

void LibraryManager::downloadEnd(){
    setDownloading(false);
}
