#include "cloud.h"
#include "cloudresponse.h"
#include <QEventLoop>
#include <QUrlQuery>
#include <QDir>
#include <QVariantMap>
#include <QVariantList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

Cloud::Cloud()
{

    _manager = new QNetworkAccessManager(this);
//    _url = QString("http://160.153.230.248/api");
    _url    =   QString("http://localhost:3000/api");
    _storage = new JsonStorage("cloud-mem.json" , this);
    loadUserInfo();

    connect(&_confMan , SIGNAL(onlineStateChanged(bool)) , this , SLOT(internetAccessStateChanged(bool)));
}


bool Cloud::authenticate(QString name , QString password){

    //Json oluşturuluyor
    QJsonObject obj;

    obj["name"]         =   name;
    obj["password"]     =   password;

    QByteArray  jsonString =   QJsonDocument(obj).toJson(QJsonDocument::Compact);
    QUrl    url(QString(_url).append("/user/authenticate"));
    QNetworkRequest     postReq(url);

    //Headerlar ayarlanıyor.
    setJsonHeader(&postReq);

    //İstek gönderiliyor
    QNetworkReply *reply = _manager->post(postReq , jsonString);
    QEventLoop      loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    CloudResponse   resp;
    extractResponse( reply , &resp );

    if(resp.success()){
        _token = resp.body()["token"].toString();

        //Kullanıcı adı ayarlanıyor
        setUserName(name);
        saveUserInfo();

        emit authenticationStateChanged();
    }

    return resp.success();
}

bool Cloud::uploadProject(QString projName , QString src){
    QJsonObject obj;

    obj["name"]  = projName;
    obj["src"]  =   src;

    QByteArray  jsonStr = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    QNetworkRequest postReq(QUrl(QString(_url).append("/project/upsertProject")));
    setJsonHeader(&postReq);
    setHeaderToken(&postReq);

    QNetworkReply   *reply = _manager->post(postReq , jsonStr);
    QEventLoop  loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    CloudResponse   resp;
    extractResponse(reply , &resp);

    if(resp.success()){
        qDebug() << "Proje başarıyla yüklendi.";
    }
    else{
        qDebug() << "Proje yüklenemedi." << resp.message();
    }

    return resp.success();
}

bool Cloud::checkToken(){
    QNetworkRequest req(QUrl(QString(_url).append("/user/checkToken")));
    setHeaderToken(&req);

    QNetworkReply   *reply = _manager->get(req);
    QEventLoop  loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    CloudResponse   resp;
    extractResponse(reply , &resp);

    return resp.success();
}

QStringList Cloud::myProjects(){
    QNetworkRequest postReq(QUrl(QString(_url).append("/user/listProjects")));
    setHeaderToken(&postReq);

    QNetworkReply   *reply = _manager->get(postReq);
    QEventLoop  loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    CloudResponse   resp;
    extractResponse(reply , &resp);

    QStringList projects;

    if(resp.success()){
        QJsonArray arr = resp.body()["list"].toArray();

        foreach (QJsonValue val, arr) {
            projects << val.toObject()["name"].toString();
            qDebug() << val.toObject()["name"].toString();
        }
    }
    else{
        qDebug() << "Proje yüklenemedi." << resp.message();
    }

    return projects;
}

bool Cloud::deleteProject(QString name){
    QNetworkRequest deleteReq(QUrl(QString(_url).append("/user/removeProject")));
    setJsonHeader(&deleteReq);
    setHeaderToken(&deleteReq);

    QJsonObject obj;
    obj["name"] = name;

    QNetworkReply   *reply = _manager->post(deleteReq , QJsonDocument(obj).toJson(QJsonDocument::Compact));
    QEventLoop  loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    CloudResponse   resp;
    extractResponse(reply , &resp);


    if(resp.success()){
        qDebug() << name <<"Proje başarılya silindi.";
    }
    else{
        qDebug() << "Proje silinemedi." << resp.message();
        return false;
    }

    return true;
}

void Cloud::extractResponse(QNetworkReply *reply, CloudResponse *resp){
    QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();

    resp->parse(obj);
}

void Cloud::setJsonHeader(QNetworkRequest *req){
    req->setRawHeader("Content-Type" , "application/json");
}

void Cloud::setHeaderToken(QNetworkRequest *req){
    req->setRawHeader(QString("x-access-token").toLatin1() , QString(_token).toLatin1());
}

bool Cloud::authenticated(){
    return !_token.isEmpty();
}

void Cloud::internetAccessStateChanged(bool online){
    emit internetAccessChanged();
}

bool Cloud::hasInternetAccess(){
    return _confMan.isOnline();
}

void Cloud::logout(){
    _token = QString();
    _userName = QString();

    saveUserInfo();

    emit authenticationStateChanged();
}

QString Cloud::userName(){
    return _userName;
}

void Cloud::setUserName(QString name){
    _userName = name;

    emit userNameChanged();
}

void Cloud::saveUserInfo(){
    _storage->set("token" , _token);
    _storage->set("userName" , _userName);
    _storage->save();
}

void Cloud::loadUserInfo(){

    _storage->load();

    _token      =   _storage->get("token").toString();

    if(!checkToken()){
        _token = "";

        return;
    }

    setUserName(_storage->get("userName").toString());
}

QVariantList Cloud::retrieveProject(QString name , int version){
    QUrl    url(QString(_url).append("/project/getProject"));
    QUrlQuery   query;

    query.addQueryItem("project" , name);
    query.addQueryItem("version" , QString::number(version));
    url.setQuery(query);

    QNetworkRequest req(url);
    setHeaderToken(&req);
    QNetworkReply *reply = _manager->get(req);
    QEventLoop  loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    QVariantList    projectList;

    CloudResponse   resp;
    extractResponse(reply , &resp);

    if(resp.success()){
        QJsonArray files = resp.body()["files"].toArray();

        foreach (QJsonValue val , files) {
            QJsonObject fileObj = val.toObject();
            QVariantHash map;
            foreach (QString key, fileObj.keys()) {
                map[key] = fileObj[key].toVariant();
            }

            qDebug()    <<  projectList;
            projectList << map;
        }

        return projectList;
    }   else    {
        qDebug() << "retrieveProject Hata : " << resp.message();
    }

    //Boş string döndürülüyor
    return projectList;
}


int Cloud::getVersionNum(QString projectName){
    QUrl        url(QString(_url).append("/project/newVersionNum"));
    QUrlQuery   query;
    query.addQueryItem("project" , projectName);
    url.setQuery(query);
    QNetworkRequest req(url);
    setHeaderToken(&req);
    QNetworkReply   *reply = _manager->get(req);
    QEventLoop      loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    CloudResponse   resp;
    extractResponse(reply , &resp);

    if(resp.success()){
        int     versionNum = resp.body()["version"].toInt();
        qDebug() << "Yeni versiyon numarası alındı -> " << versionNum;

        return versionNum;
    }
    else{
        qDebug() << "Hata " << resp.message();

        return -1;
    }
}

bool Cloud::endCommit(QString proj , int version){

    QJsonObject obj;
    obj["version"] = version;
    obj["project"] = proj;
    QUrl    url(QString(_url).append("/project/endCommit"));
    QNetworkRequest req(url);
    setHeaderToken(&req);
    setJsonHeader(&req);
    QNetworkReply   *reply = _manager->post(req , QJsonDocument(obj).toJson(QJsonDocument::Compact));
    QEventLoop  loop;
    connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
    loop.exec();

    CloudResponse   resp;
    extractResponse(reply , &resp);

    if(resp.success()){
        qDebug() << "Cloud.endCommit() -> "<< resp.message();

        return true;
    }
    else{
        qDebug() << "Cloud.endCommit() -> " << resp.message();

        return false;
    }

}

bool Cloud::uploadProjectV2(QString name, QString root){

    QString     mainFContent  = readContent(QDir(root).absoluteFilePath("sketch.cpp"));

    uploadProject(name , mainFContent);
    int     versionNum  =   getVersionNum(name);

    QList<FInfo> files =  fInfo(root , "\\.cpp|\\.c|\\.S|\\.h");

    QUrl    url(QString(_url).append("/project/commit"));

    QNetworkRequest req(url);
    setHeaderToken(&req);
    setJsonHeader(&req);

    int     idx = 1;
    foreach (FInfo inf, files) {
        QJsonObject obj;

        obj["project"]      =   name;
        obj["isFile"]       =   inf.isFile;
        obj["rPath"]        =   inf.relativePath;
        obj["content"]      =   inf.content;
        obj["version"]      =   versionNum;
        obj["message"]      =   "Versiyon " + QString::number(versionNum);

        QNetworkReply *reply =  _manager->post(req , QJsonDocument(obj).toJson(QJsonDocument::Compact));
        QEventLoop  loop;
        connect(reply , SIGNAL(finished()) , &loop , SLOT(quit()));
        loop.exec();

        CloudResponse   resp;
        extractResponse(reply , &resp);

        QString     output2;
        if(resp.success()){
            output2.append(inf.relativePath).append(" yüklendi.");
            qDebug() << output2;
            emit commandOutput(output2);
        }else{
            output2.append(inf.relativePath).append(" yüklenirken hata oluştu !.");
            qDebug() << output2;
            emit stdError(output2);
            return false;
        }

        double progress = (idx / (double)files.length());
        qDebug() << progress;
        emit projectUploadProgress(progress);
        idx++;
    }

    emit commandOutput("Yükleme tamamlanıyor...");
    endCommit(name , versionNum);
    emit stdOutput("Proje başarıyla yüklendi...");
    return true;
}

QList<Cloud::FInfo> Cloud::fInfo(QString root , QString filterPattern , QString relativeToRoot){
    QList<FInfo>    files;

    QDir    dir(root);

    foreach(QString nestedFolder , dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
        QString nestedPath = QString(root).append(QDir::separator()).append(nestedFolder);

        FInfo   f;

        f.isFile        =   false;
        f.relativePath  =   QString(relativeToRoot).append(QDir::separator()).append(nestedFolder);


        files.append(f);
        files.append(fInfo(nestedPath , filterPattern , QString(relativeToRoot).append(QDir::separator()).append(nestedFolder)));
    }

    foreach(QString fileName , dir.entryList(QDir::Files)){
        QRegularExpression  re(filterPattern);
        QRegularExpressionMatch match = re.match(fileName);

        if(!match.hasMatch()){
            qDebug() << fileName << " pas geçiliyor.";

            continue;
        }

        FInfo   f;

        f.isFile        =   true;
        f.relativePath  =   QString(relativeToRoot).append(QDir::separator()).append(fileName);
        f.content       =   readContent(dir.absoluteFilePath(fileName));

        files.append(f);
    }

    return files;
}

QString Cloud::readContent(QString file){
    QFile   f(file);

    QString     content;

    if(!f.open(QIODevice::ReadOnly)){
        qDebug() << file << " açılamıyor.";
        return content;
    }

    QTextStream fStream(&f);

    content = fStream.readAll();

    return content;
}
