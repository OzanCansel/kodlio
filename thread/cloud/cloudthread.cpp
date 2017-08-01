#include "cloudthread.h"

void CloudThread::registerQmlType(){
    qmlRegisterType<CloudThread>("Kodlio" , 1 , 0 , "CloudThread");
}

CloudThread::CloudThread(QQuickItem* parent) : QQuickItem(parent)
{
    _cloud = Q_NULLPTR;
    _worker = new CloudWorker();
    _worker->moveToThread(&cloudThread);

    connect(this , SIGNAL(uploadProjectSignal(QString)), _worker , SLOT(uploadProject(QString)));

    //Thread baslatiliyor
    cloudThread.start();
}

CloudThread::~CloudThread(){
    cloudThread.terminate();
    cloudThread.wait();
}

//Getter
Cloud* CloudThread::cloud(){
    return _cloud;
}

//Setter
void CloudThread::setCloud(Cloud *cloud){
    _cloud = cloud;
    _worker->setCloud(_cloud);

    emit cloudChanged();
}

void CloudThread::uploadProject(QString root){
    emit uploadProjectSignal(root);
}
