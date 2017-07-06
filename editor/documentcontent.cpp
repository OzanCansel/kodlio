#include "documentcontent.h"
#include <QFile>
#include <QTextStream>
#include <QtQml>

void DocumentContent::registerQmlType(){
    qmlRegisterType<DocumentContent>("Kodlio" , 1 , 0 , "DocumentContent");
}

DocumentContent::DocumentContent(QQuickItem *parent) : QQuickItem(parent)
{
    _doc = Q_NULLPTR;
}

//Setter
void DocumentContent::setAbsolutePath(QString val){
    _path = val;

    emit absolutePathChanged();

    QFile   doc(val);
    qDebug() << "Path << " << val;

    //Mevcut degilse hata firlatiliyor
    if(!doc.exists()){
        emit fileNotFound();
        setContent(QString());
        return;
    }

    if(!doc.open(QIODevice::ReadOnly)){
        emit fileReadError();
        setContent(QString());
        return;
    }

    //Dosya okunuyor
    QTextStream ss(&doc);
    setContent(ss.readAll());

    //Dosya kapatiliyor
    doc.close();
}

void DocumentContent::setContent(QString val){
    _content = val;
    emit contentChanged();
}

void DocumentContent::setTextDocument(QQuickTextDocument *doc){
    _doc = doc;
}

//Getter
QString DocumentContent::absolutePath(){
    return _path;
}

QString DocumentContent::content(){
    return _content;
}

QString DocumentContent::fileName(){
    QFileInfo info(_path);

    qDebug() << "FileName -> " << info.fileName();

    return info.fileName();
}

QQuickTextDocument* DocumentContent::textDocument(){
    return _doc;
}

//Slots
bool    DocumentContent::save(){
    QString content = _doc->textDocument()->toPlainText();
    QFile   doc(_path);

    //Eger dosya yoksa
    if(!doc.exists()){
        emit fileNotFound();
        return false;
    }

    if(!doc.open(QIODevice::WriteOnly)){
        emit fileReadError();
        return false;
    }

    QTextStream ss(&doc);

    ss << content;

    doc.close();

    return true;
}
