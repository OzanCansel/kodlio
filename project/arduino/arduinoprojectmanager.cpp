#include "arduinoprojectmanager.h"
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include "texttemplate/arduino/arduinomainfiletemplate.h"

void ArduinoProjectManager::registerQmlType(){
    qmlRegisterType<ArduinoProjectManager>("Kodlio" , 1 , 0 , "ArduinoProjectManager");
}

ArduinoProjectManager::ArduinoProjectManager(QQuickItem *parent) : ProjectManager(parent)
{

}

void ArduinoProjectManager::createProject(ProjectOptions *opts){
    QString     path = opts->root();
    QString     projectName = opts->projectName();
    if(path.isEmpty() || projectName.isEmpty()){
        sendProjectCreateError("Proje dizini mevcut degil.");
        return;
    }
    QDir    rootDir(path);
    if(rootDir.exists(projectName)){
        sendProjectCreateError("Bu isimde bir proje veya klasör mevcut.");
        return;
    }

    bool created = rootDir.mkdir(projectName);
    if(!created){
        sendProjectCreateError("Proje oluşturulamadı.");
        return;
    }

    //Proje klasorune giriliyor
    rootDir.cd(projectName);

    QFile   mainFile(rootDir.filePath("sketch.cpp"));
    ArduinoMainFileTemplate mainFileTemplate;
    QString date = QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm");
    mainFileTemplate.setDate(date);
    mainFileTemplate.setFileName("sketch.cpp");
    QString content = mainFileTemplate.extract();

    if(!mainFile.open(QIODevice::WriteOnly)){
        sendProjectCreateError("Dosya olusturulurken hata olustu.");
        rootDir.removeRecursively();
        return;
    }

    QTextStream ss(&mainFile);
    ss << content;

    mainFile.close();
    setProjectRoot(rootDir.absolutePath());
    sendProjectCreated();

}

void ArduinoProjectManager::removeProject(ProjectOptions *opts){
}

