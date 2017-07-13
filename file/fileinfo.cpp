#include "fileinfo.h"\
#include <QDebug>
#include <QtQml>

void FileInfo::registerQmlType(){
    qmlRegisterType<FileInfo>("Kodlio" , 1 , 0 , "FileInfo");
}

FileInfo::FileInfo(QQuickItem *parent) : QQuickItem(parent){

}

FileInfo::FileInfo(QFileInfo &info , QQuickItem *parent) : QQuickItem(parent)
{
    _info = info;
}

FileInfo::~FileInfo(){

}

FileInfo::FileInfo(const FileInfo &other)   {
    setFile(other.filePath());
}

FileInfo& FileInfo::operator =(const FileInfo &other)   {
    setFile(other.filePath());
}

QString FileInfo::absolutePath(){
    return _info.absolutePath();
}

QString FileInfo::absoluteFilePath(){
    return _info.absoluteFilePath();
}

QString FileInfo::baseName(){
    return _info.baseName();
}

QString FileInfo::bundleName(){
    return _info.bundleName();
}

bool FileInfo::caching(){
    return _info.caching();
}

QString FileInfo::canonicalFilePath() const{
    return _info.canonicalFilePath();
}

QString FileInfo::canonicalPath() const{
    return _info.canonicalPath();
}

QString FileInfo::completeBaseName() const{
    return _info.completeBaseName();
}

QString FileInfo::completeSuffix() const{
    return _info.completeSuffix();
}

bool FileInfo::exists(){
    return _info.exists();
}

QString FileInfo::fileName() const{
    return _info.fileName();
}

QString FileInfo::filePath() const{
    return _info.filePath();
}

QString FileInfo::group(){
    return _info.group();
}

bool FileInfo::isAbsolute(){
    return _info.isAbsolute();
}
\
bool FileInfo::isBundle(){
    return _info.isBundle();
}

bool FileInfo::isDir(){
    return _info.isDir();
}

bool FileInfo::isExecutable(){
    return _info.isExecutable();
}

bool FileInfo::isFile(){
    return _info.isFile();
}

bool FileInfo::isHidden(){
    return _info.isHidden();
}

bool FileInfo::isNativePath(){
    return _info.isNativePath();
}

bool FileInfo::isReadable(){
    return _info.isReadable();
}

bool FileInfo::isRelative(){
    return _info.isRelative();
}

bool FileInfo::isRoot(){
    return _info.isRoot();
}

bool FileInfo::isSymLink(){
    return _info.isSymLink();
}

bool FileInfo::isWritable(){
    return _info.isWritable();
}

QString FileInfo::path(){
    return _info.path();
}

qint64 FileInfo::size(){
    return _info.size();
}

QString FileInfo::suffix(){
    return _info.suffix();
}

QString FileInfo::symLinkTarget(){
    return _info.symLinkTarget();
}

void FileInfo::setFile(QString file){
    _info.setFile(file);

    emit filePathChanged();
}

QString FileInfo::dirName(){
    if(_info.isDir())
        return _info.fileName();
    else
        return _info.absoluteDir().dirName();
}
