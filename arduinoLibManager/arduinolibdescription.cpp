#include "arduinolibdescription.h"
#include <QtQml>
#include <QFile>
#include <QTextStream>
#include "traverse/filetraverse.h"

void ArduinoLibDescription::registerQmlType(){
    qmlRegisterType<ArduinoLibDescription>("Kodlio" , 1 , 0 , "ArduinoLibDescription");
}

ArduinoLibDescription::ArduinoLibDescription(QQuickItem *parent) : QQuickItem(parent)
{

}

ArduinoLibDescription::ArduinoLibDescription(const ArduinoLibDescription &other){
    setName(other.name());
    setVersion(other.version());
    setAuthor(other.author());
    setMaintainer(other.maintainer());
    setSentence(other.sentence());
    setParagraph(other.paragraph());
    setWebsite(other.website());
    setCategory(other.category());
    setUrl(other.url());
    setArchivedFileName(other.archivedFileName());
    _libDir = other.localDir();
}

ArduinoLibDescription& ArduinoLibDescription::operator =(const ArduinoLibDescription &other){
    setName(other.name());
    setVersion(other.version());
    setAuthor(other.author());
    setMaintainer(other.maintainer());
    setSentence(other.sentence());
    setParagraph(other.paragraph());
    setWebsite(other.website());
    setCategory(other.category());
    setUrl(other.url());
    setArchivedFileName(other.archivedFileName());
}

void ArduinoLibDescription::deserialize(QJsonObject &obj){
    setName(obj["name"].toString());
    setVersion(obj["version"].toString());
    setAuthor(obj["author"].toString());
    setMaintainer(obj["maintainer"].toString());
    setSentence(obj["sentence"].toString());
    setParagraph(obj["paragraph"].toString());
    setWebsite(obj["website"].toString());
    setCategory( obj["category"].toString());
    setUrl(obj["url"].toString());
    setArchivedFileName(obj["archiveFileName"].toString());
}

void ArduinoLibDescription::deserialize(QString &fileName){
    QFile   f(fileName);

    if(!f.open(QFile::ReadOnly)){
        qDebug() << "ArduinoLibDescription:;deserialize(QString &fileName) err -> " << fileName << " acilamiyor.";
        return;
    }

    QTextStream stream(&f);
    QJsonObject obj;

    while(!stream.atEnd()){
        QString line = stream.readLine();
        int     seperatorIdx = line.indexOf("=");
        QString label = line.left(seperatorIdx);
        QString value = line.right(line.length() - seperatorIdx - 1);

        obj[label]  =   value;
    }

    deserialize(obj);

    _libDir = fileName.left(fileName.lastIndexOf("/"));
    emit localDirChanged();
}

QVariantMap ArduinoLibDescription::asVariant(){
    QVariantMap map;

    map["name"]         =    name();
    map["version"]      =   version();
    map["author"]       =   author();
    map["maintainer"]   =   maintainer();
    map["sentence"]     =   sentence();
    map["paragraph"]    =   paragraph();
    map["website"]      =   website();
    map["category"]     =   category();
    map["url"]          =   url();
    map["archivedFileName"] =   archivedFileName();

    return map;
}

QString ArduinoLibDescription::name() const{
    return _name;
}

QString ArduinoLibDescription::version() const{
    return _version;
}

QString ArduinoLibDescription::author() const{
    return _author;
}

QString ArduinoLibDescription::maintainer() const{
    return _maintainer;
}

QString ArduinoLibDescription::sentence() const{
    return _sentence;
}

QString ArduinoLibDescription::paragraph() const{
    return _paragraph;
}

QString ArduinoLibDescription::website() const{
    return _website;
}

QString ArduinoLibDescription::category() const{
    return _category;
}

QString ArduinoLibDescription::url() const{
    return _url;
}

QString ArduinoLibDescription::archivedFileName() const{
    return _archivedFileName;
}

QString ArduinoLibDescription::localDir() const{
    return _libDir;
}

void ArduinoLibDescription::setName(QString val){
    _name = val;

    emit nameChanged();
}\

void ArduinoLibDescription::setVersion(QString val){
    _version = val;

    emit versionChanged();
}

void ArduinoLibDescription::setAuthor(QString val){
    _author = val;

    emit authorChanged();
}

void ArduinoLibDescription::setMaintainer(QString val){
    _maintainer =  val;

    emit maintainerChanged();
}

void ArduinoLibDescription::setSentence(QString val){
    _sentence = val;

    emit sentenceChanged();
}

void ArduinoLibDescription::setParagraph(QString val){
    _paragraph = val;

    emit paragraphChanged();
}

void ArduinoLibDescription::setWebsite(QString val){
    _website = val;

    emit websiteChanged();
}

void ArduinoLibDescription::setCategory(QString val){
    _category = val;

    emit categoryChanged();
}

void ArduinoLibDescription::setUrl(QString val){
    _url = val;

    emit  urlChanged();
}

void ArduinoLibDescription::setArchivedFileName(QString val){
    _archivedFileName = val;

    emit archivedFileNameChanged();
}

QStringList ArduinoLibDescription::headerNames(){

    if(_libDir.isEmpty())
        return QStringList();

    QStringList headers;
    FileTraverse traverser;

    QList<TraversedFileInfo>    files = traverser.traverseRecursively(_libDir);

    foreach (TraversedFileInfo file, files) {
        if(file.info().fileName().endsWith(".h")){
            headers.append(file.info().fileName());
        }
    }

    return headers;
}
