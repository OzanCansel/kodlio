#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QTime>
#include <QNetworkConfigurationManager>
#include "highlight/arduinohighlightitem.h"
#include "toolchain/unocompiler.h"
#include "directorymanager.h"
#include "projectmanager.h"
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
#include "settings/editorsettings.h"
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
#include <QStandardPaths>

int main(int argc, char *argv[])    {

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

    //    RoboskopEnvironment*            env = RoboskopEnvironment::getInstance();
    //    Compiler                        compiler;
    //    Programmer                      programmer;
    //    Toolchain                       toolchain(&compiler , &programmer);
    //    DirectoryManager                dirMan;
    //    ProjectManager                  manager(&dirMan , &toolchain);
    //    Cloud                           cloud;
    //    ParseHelper                     parseHelper;
    //    CompilerErrorParser             errParser;
        OsInfo                          osInfo;
        EditorSettings                  settings;
    //    CodeDescriptionGenerator        descGen;

    QQmlApplicationEngine engine;
    EventContext        eventContext;
    QQmlContext *context = engine.rootContext();

    context->setContextProperty("eventContext" , &eventContext);
    //    context->setContextProperty("projectManager" , &manager);
    //    context->setContextProperty("cloudApi" , &cloud);
    //    context->setContextProperty("fileSys" , &dirMan);
//        context->setContextProperty("serialPort" , &sPort);
    //    context->setContextProperty("compiler" , &compiler);
    //    context->setContextProperty("programmer", &programmer);
    //    context->setContextProperty("toolchain" , &toolchain);
    //    context->setContextProperty("descriptionGenerator" , &descGen);
    //    context->setContextProperty("parseHelper" , &parseHelper);
    //    context->setContextProperty("compilerErrorParser" , &errParser);
        context->setContextProperty("osInfo" , &osInfo);
        context->setContextProperty("settings" , &settings);
    //    context->setContextProperty("environment" , env);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
