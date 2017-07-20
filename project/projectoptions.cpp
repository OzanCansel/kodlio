#include "projectoptions.h"

void ProjectOptions::registerQmlType(){
    qmlRegisterType<ProjectOptions>("Kodlio" , 1 , 0 , "ProjectOptions");
}

ProjectOptions::ProjectOptions(QQuickItem *parent) : Options(parent)
{

}

void ProjectOptions::setRoot(QString root){
    set(ROOT_LABEL , root);
    emit rootChanged();
}

QString ProjectOptions::root(){
    return get(ROOT_LABEL).toString();
}

void ProjectOptions::setProjectName(QString projectName){
    set(PROJECT_NAME_LABEL , QVariant(projectName));
    emit projectNameChanged();
}

QString ProjectOptions::projectName(){
    return get(PROJECT_NAME_LABEL).toString();
}
