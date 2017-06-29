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
#include "cloudresponse.h"
#include "jsonstorage.h"

class Cloud : public QObject
{

    Q_OBJECT
    Q_PROPERTY(bool authenticated READ authenticated NOTIFY authenticationStateChanged)
    Q_PROPERTY(bool hasInternetAccess READ hasInternetAccess NOTIFY internetAccessChanged)
    Q_PROPERTY(QString userName  READ userName NOTIFY userNameChanged)

public:

    typedef struct FInfo{
        QString relativePath;
        QString content;
        bool    isFile;
    } FInfo;

    Cloud();
    bool        authenticated();
    bool        hasInternetAccess();
    QString     userName();

public slots:

    bool        authenticate(QString name , QString password);
    bool        uploadProject(QString name ,  QString src);
    bool        uploadProjectV2(QString name , QString root);
    int         getVersionNum(QString projectName);
    bool        deleteProject(QString name);
    QVariantList retrieveProject(QString name , int version = -1);
    bool        checkToken();
    QStringList myProjects();
    void        logout();

private slots:

    void        internetAccessStateChanged(bool online);
    bool        endCommit(QString proj , int version);

signals:

    void        authenticationStateChanged();
    void        internetAccessChanged();
    void        userNameChanged();
    void        projectUploadProgress(double progress);
    void        commandOutput(QString out);
    void        stdOutput(QString out);
    void        stdError(QString err);

private:

    QNetworkAccessManager   *_manager;
    QNetworkConfigurationManager    _confMan;

    QString     _userName;
    QString     _password;
    QString     _url;
    QString     _token;
    JsonStorage *_storage;

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
