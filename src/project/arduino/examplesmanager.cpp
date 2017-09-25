#include "examplesmanager.h"
#include <QDir>

void ExamplesManager::registerQmlType(){
    qmlRegisterType<ExamplesManager>("Kodlio" , 1 ,  0 , "ExamplesManager");
}

ExamplesManager::ExamplesManager(QQuickItem *parent) :
    QQuickItem(parent) ,
    m_manager(nullptr)
{

}

QVariantMap ExamplesManager::load(){

    if(m_manager == nullptr)
        return QVariantMap();

    //Lokaldeki kutuphaneler yukleniyor
    m_manager->retrieveLocalLibraries();

    QList<ArduinoLibDescription*> localLibs = m_manager->getLocalLibs();

    QVariantMap     map;

    foreach(ArduinoLibDescription* desc , localLibs) {

        QVariantMap descMap;
        QString examplesDirPath = desc->examplesDir();
        //Eger ki bu kutuphaneyle ilgili ornek mevcut degilse geri donuluyor
        if(examplesDirPath.isEmpty())
            continue;
        QDir examplesDir(examplesDirPath);
        foreach(QFileInfo folder , examplesDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
            QVariantMap exampleMap;

            exampleMap["name"] = folder.baseName();
            exampleMap["path"] = folder.absoluteFilePath();
            exampleMap["isCategory"] = QVariant(false);
            descMap[folder.baseName()] = exampleMap;
        }

        map[desc->name()] = descMap;
    }

    return map;
}

LibraryManager* ExamplesManager::libManager(){
    return m_manager;
}

void ExamplesManager::setLibManager(LibraryManager* manager){
    m_manager = manager;
}
