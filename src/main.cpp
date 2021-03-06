#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QTime>
#include <QNetworkConfigurationManager>
#include <QStandardPaths>
#include "highlight/arduinohighlightitem.h"
#include "toolchain/unocompiler.h"
#include "directorymanager.h"
#include "sdkextractor.h"
#include "cloudapi/cloud.h"
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
#include "traverse/projecttraverse.h"
#include "traverse/filetraverse.h"
#include "toolchain/cplusplus/gnutoolchain.h"
#include "arduinoLibManager/librarymanager.h"
#include "arduinoLibManager/arduinolibdownloader.h"
#include "http/internetaccessibility.h"
#include "editor/documentcontent.h"
#include "toolchain/toolchainplugin.h"
#include "highlight/highlightplugin.h"
#include "editor/editorplugin.h"
#include "arduinoLibManager/librarymanagerplugin.h"
#include "project/projectplugin.h"
#include "http/httpplugin.h"
#include "traverse/traverseplugin.h"
#include "file/fileplugin.h"
#include "thread/threadplugin.h"
#include "eventcontext.h"
#include "serial/serialplugin.h"
#include "parse/parserplugin.h"
#include "cloudapi/cloudplugin.h"
#include "globalplugin.h"
#include <QStandardPaths>

int main(int argc, char *argv[]){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    //Plugin
    EditorPlugin::attach();
    ToolchainPlugin::attach();
    HighlightPlugin::attach();
    LibraryManagerPlugin::attach();
    ProjectPlugin::attach();
    HttpPlugin::attach();
    TraversePlugin::attach();
    FilePlugin::attach();
    ThreadPlugin::attach();
    SerialPlugin::attach();
    ParserPlugin::attach();
    CloudPlugin::attach();
    GlobalPlugin::attach();
    OsInfo      osInfo;

    QQmlApplicationEngine engine;
    EventContext        eventContext;
    QQmlContext *context = engine.rootContext();
    QString path = QStandardPaths::locate(QStandardPaths::DocumentsLocation , "" , QStandardPaths::LocateDirectory);

    QDir(path).mkpath("kodlio");


    QObject::connect(&engine , SIGNAL(quit()) , &app , SLOT(quit()));
    QObject::connect(&engine , &QQmlApplicationEngine::exit , QApplication::exit);
    context->setContextProperty("eventContext" , &eventContext);
    context->setContextProperty("osInfo" , &osInfo);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
