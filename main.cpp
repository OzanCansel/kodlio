#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QTime>
#include <QNetworkConfigurationManager>
#include "editorhighlight.h"
#include "toolchain/unocompiler.h"
#include "directorymanager.h"
#include "projectmanager.h"
#include "sdkextractor.h"
#include "cloudapi/cloud.h"
#include "serialport.h"
#include "toolchain/toolchain.h"
#include "toolchain/compiler.h"
#include "roboskopenvironment.h"
#include "toolchain/compileconfiguration.h"
#include "toolchain/programmerconfiguration.h"
#include "generate/codedescriptiongenerator.h"
#include "generate/codedescriptioninfo.h"
#include "parse/parsehelper.h"
#include "parse/compilererrorparser.h"
#include "osinfo.h"
#include "settings/editorsettings.h"
#include "traverse/projecttraverse.h"
#include "traverse/filetraverse.h"
#include "toolchain/cplusplus/gnutoolchain.h"
#include "arduinoLibManager/librarymanager.h"
#include "arduinoLibManager/arduinolibdownloader.h"
#include "http/internetaccessibility.h"
#include <QStandardPaths>

int main(int argc, char *argv[]){

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);


    //Qml sınıfları ekleniyor
    EditorHighlight::registerQmlType();
    CompileConfiguration::registerQmlType();
    ProgrammerConfiguration::registerQmlType();
    CodeDescriptionInfo::registerQmlType();
    ProjectTraverse::registerQmlType();
    LibraryManager::registerQmlType();
    InternetAccessibility::registerQmlType();

    RoboskopEnvironment*            env = RoboskopEnvironment::getInstance();
    Compiler                        compiler;
    Programmer                      programmer;
    Toolchain                       toolchain(&compiler , &programmer);
    DirectoryManager                dirMan;
    ProjectManager                  manager(&dirMan , &toolchain);
    Cloud                           cloud;
    SerialPort                      sPort;
    ParseHelper                     parseHelper;
    CompilerErrorParser             errParser;
    OsInfo                          osInfo;
    EditorSettings                  settings;
    CodeDescriptionGenerator        descGen;

    QString tempProjPath    =   QDir(QCoreApplication::applicationDirPath()).filePath("temp");
    if(!manager.projectExists(tempProjPath))    manager.createProject(tempProjPath);
    manager.openProject(tempProjPath);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    context->setContextProperty("projectManager" , &manager);
    context->setContextProperty("cloudApi" , &cloud);
    context->setContextProperty("fileSys" , &dirMan);
    context->setContextProperty("serialPort" , &sPort);
    context->setContextProperty("compiler" , &compiler);
    context->setContextProperty("programmer", &programmer);
    context->setContextProperty("toolchain" , &toolchain);
    context->setContextProperty("descriptionGenerator" , &descGen);
    context->setContextProperty("parseHelper" , &parseHelper);
    context->setContextProperty("compilerErrorParser" , &errParser);
    context->setContextProperty("osInfo" , &osInfo);
    context->setContextProperty("settings" , &settings);
    context->setContextProperty("environment" , env);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
