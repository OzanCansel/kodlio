#include "cloudworker.h"

CloudWorker::CloudWorker(QObject *parent) : QObject(parent)
{

}

void CloudWorker::setCloud(Cloud *val){
    _cloud = val;
}

void CloudWorker::uploadProject(QString root){
    if(_cloud == nullptr)
        return;

    _cloud->uploadProjectV2(root);
}
