#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QNetworkConfigurationManager>
#include <QDir>
#include <QQuickItem>
#include "cloudresponse.h"
#include "jsonstorage.h"

class Cloud : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(bool authenticated READ authenticated NOTIFY authenticationStateChanged)
    Q_PROPERTY(bool hasInternetAccess READ hasInternetAccess NOTIFY internetAccessChanged)
    Q_PROPERTY(QString userName  READ userName NOTIFY userNameChanged)
    Q_PROPERTY(bool projectUploadBusy READ projectUploadBusy NOTIFY projectUploadBusyChanged)
//    Q_PROPERTY(bool retrieveProjectBusy READ retrieveProjectBusy NOTIFY retrieveProjectBusyChanged)

public:

    typedef struct FInfo{
        QString relativePath;
        QString content;
        bool    isFile;
    } FInfo;

    static void     registerQmlType();
    Cloud(QQuickItem* parent = nullptr);
    bool        authenticated();
    bool        hasInternetAccess();
    bool        projectUploadBusy();
    bool        retrieveProjectBusy();
    QString     userName();

public slots:

    bool        authenticate(QString name , QString password);
    bool        uploadProject(QString name);
    bool        uploadProjectV2(QString _root);
    int         getVersionNum(QString projectName);
    bool        deleteProject(QString name);
    void        retrieveProject(QString name , int version = -1);
    bool        checkToken();
    QStringList myProjects();
    void        logout();
    void        downloadSources(QString projectName , QString _root);

private slots:

    void        internetAccessStateChanged(bool online);
    bool        endCommit(QString proj , int version);
    void        retrieveProjectDownloadProgress(qint64 read , qint64 total);
    void        retrieveProjectDownloadFinished();
    void        retrieveProjectErrorOccurred();
    void        downloadSourcesStepTwo();

signals:

    void        authenticationStateChanged();
    void        internetAccessChanged();
    void        userNameChanged();
    void        projectUploadProgress(double progress);
    void        commandOutput(QString out);
    void        stdOutput(QString out);
    void        stdError(QString err);
    void        projectUploadBusyChanged();
    void        downloadProjectError();
    void        retrieveProjectBusyChanged();
    void        retrieveProjectProgress(double progress);

protected:

    void        setProjectUploadBusy(bool val);
    void        setRetrieveProjectDownloadBusy(bool val);

private:

    QNetworkAccessManager   *_manager;
    QNetworkConfigurationManager    _confMan;

    bool        _projectUploadBusy;
    bool        _retrieveProjectBusy;
    bool        _writeSourceFlag;
    QString     _userName;
    QString     _password;
    QString     _url;
    QString     _token;
    QString     _root;
    JsonStorage *_storage;
    QVariantList _projectSources;

    void        extractResponse(QNetworkReply *reply , CloudResponse   *resp);
    void        setJsonHeader(QNetworkRequest *req);
    void        setHeaderToken(QNetworkRequest *req);
    void        setUserName(QString name);
    void        saveUserInfo();
    void        loadUserInfo();

    QList<FInfo>        fInfo(QString current,  QString filterPattern , QString relativeToRoot = QString());
    QString             readContent(QString file);

};

#endif // SERVERCONNECTOR_H
