#include "avrcompilerV2.h"
#include "parse/includedheaders.h"
#include "exception/filecouldnotopen.h"
#include "exception/boardnotspecified.h"
#include "exception/incompatibleextension.h"
#include "exception/compileerror.h"
#include "board/boardfactory.h"
#include "avrenvironment.h"
#include <QDebug>
#include <QProcess>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QDir>

void AvrCompilerV2::registerQmlType(){
    qmlRegisterType<AvrCompilerV2>("Kodlio" , 1 , 0 , "AvrCompiler");
}

AvrCompilerV2::AvrCompilerV2(QQuickItem *parent) : CompilerV2(parent)   {
    manager.retrieveLocalLibraries();
    _allowedExtensions << ".cpp" << ".S" << ".s" << ".c" << ".s";
}

void AvrCompilerV2::generateObjFile(QString &file, QString &output , QStringList &includes, QString &boardName) {

    QString     fileExtension = file.right(file.length() - file.lastIndexOf("."));

    //Uzantinin dogrulugu kontrol ediliyor
    if(!_allowedExtensions.contains(fileExtension)){
        QString errorMessage = QString("AvrCompilerV2::compile() %0 uzantisi hatali.").arg(file);

        //Hata firlatiliyor
        IncompatibleExtension(errorMessage).raise();
    }

    //Gerekli parametreler kontrol edildi, compile asamasina geciliyor
    BoardFactory    factory;
    ArduinoBoard    *board = factory.create(boardName);
    AvrEnvironment  env;
    QString         includesText;

    board->setParent(this);

    foreach (QString includePath, includes) {
        includesText
                .append(normalizePath(QString("-I%0").arg(QDir::toNativeSeparators(includePath))))
                .append(" "); //Bosluk birakiliyor
    }

//    includesText.append(QString("\"-I%0\" ").arg(env.variants(boardName)));
    includesText.append(normalizePath(QString("-I%0").arg(env.variants(boardName))));
    includesText.append(" "); //Bosluk birakiliyor

    //gcc <parametreler> <includePath> <inputFile> -o <outputFile>
    QString command = QString("%0 %1 %2 %3 -o %4")
            .arg(normalizePath(env.gcc()))
            .arg(board->objectCodeParams(fileExtension))
            .arg(includesText)
            .arg(normalizePath(file))
            .arg(normalizePath(output));

    sendCommandOutput(command);
    QProcess    compileProcess;

    //Derleme baslatiliyor
    compileProcess.start(command);
    bool interrupted = !compileProcess.waitForFinished();

    //Islem tamamlanmadiysa
    if(interrupted) {
        QString errorText = QString("%0 derlenirken hata olustu.").arg(QFileInfo(file).fileName());
        sendStdError(errorText);
        sendCompileError();

        return;
    }

    //Compile sirasinda hata olustuysa
    if(compileProcess.exitCode() != 0){
        QString err = compileProcess.readAllStandardError();
        sendStdError(err);
        sendCompileError();
        CompileError(err).raise();
    }
}

void AvrCompilerV2::archiveFiles(QStringList &objFiles, QString &output){
    QProcess    archiveProcess;
    AvrEnvironment  env;

    foreach (QString objFile, objFiles) {
        //<compilerName> rcs <output> <input>
        QString command = QString("%0 rcs %1 %2")
                .arg(normalizePath(env.gccAr()))
                .arg(normalizePath(output))
                .arg(normalizePath(objFile));

        sendCommandOutput(command);
        //Baslatiliyor
        archiveProcess.start(command);
        archiveProcess.waitForFinished();

        //Basarili degilse
        if(archiveProcess.exitCode() != 0){
            QString     err = archiveProcess.readAllStandardError();
            sendStdError(QString("%0 arsivlenirken hata -> ")
                         .arg(objFile)
                         .arg(err));
            sendCompileError();
            //Hata firlatiliyor
            CompileError(err).raise();
        }
    }
}

QString AvrCompilerV2::generateHex(QString &archiveFile, QString &buildFolder , QStringList& generatedObjFiles){
    QString elfFilePath = QString(buildFolder).append("/output.elf");
    QString eepFilePath = QString(buildFolder).append("/output.eep");
    QString hexFilePath = QString(buildFolder).append("/output.hex");
    BoardFactory    factory;
    AvrEnvironment  env;
    ArduinoBoard*   board = factory.create("uno");  //Simdilik uno hardcoded olarak uretiliyor

    bool interrupted  = false;  //Islem  yarida kesilirse true

    QString     objFilesText;

    foreach (QString objFile, generatedObjFiles) {
        objFilesText
                .append(normalizePath(QString("%0").arg(objFile)))
                .append(" "); //Bosluk birakiliyor
    }

    //<avr-gcc> <params> -o <outputFile> <inputFile> <archiveFile> -L<buildFolder> -lm
    QString generateElfCommand = QString("%0 %1 -o %2 %3 %4 -L%5 -lm")
            .arg(normalizePath(env.gcc())) //0
            .arg(board->elfParams()) //1
            .arg(normalizePath(elfFilePath)) //2
            .arg(objFilesText) //objFiles
            .arg(normalizePath(archiveFile))
            .arg(normalizePath(buildFolder));

    sendCommandOutput(generateElfCommand);

    QProcess    process;

    //Elf uretiliyor
    process.start(generateElfCommand);
    interrupted = !process.waitForFinished();

    //Islem tamamlanamadiysa
    if(interrupted || process.exitCode() != 0){
        QString     err(".elf dosyasi uretilirken hata !");
        QString     actualError = process.readAllStandardError();
        sendStdError(err);
        sendStdError(actualError);
        sendCompileError();
        CompileError(err).raise();
    }

    //<objcopy> <params> <inputElf> <outputEep>
    QString generateEepCommand = QString("%0 %1 %2 %3")
            .arg(normalizePath(env.objcopy()))
            .arg(board->eepParams())
            .arg(normalizePath(elfFilePath))
            .arg(normalizePath(eepFilePath));

    sendCommandOutput(generateEepCommand);
    //Eep uretiliyor
    process.start(generateEepCommand);
    interrupted = !process.waitForFinished();

    if(interrupted || process.exitCode() != 0){
        QString     stdErr = process.readAllStandardError();
        QString     appErr(".eep dosyasi uretilirken hata !");
        sendStdError(stdErr);
        sendStdError(appErr);
        sendCompileError();
        CompileError(appErr).raise();
    }

    //<objcopy> <params> <inputElf> <outputHex>
    QString generateHexCommand = QString("%0 %1 %2 %3")
            .arg(normalizePath(env.objcopy()))
            .arg(board->hexParams())
            .arg(normalizePath(elfFilePath))
            .arg(normalizePath(hexFilePath));

    //Hex uretiliyor
    process.start(generateHexCommand);
    interrupted = !process.waitForFinished();

    //Hata
    if(interrupted || process.exitCode() != 0){
        QString     err(".hex dosyasi uretilirken hata !");
        QString     stdErr = process.readAllStandardError();
        sendStdError(stdErr);
        sendStdError(err);
        sendCompileError();
        CompileError(err).raise();
    }

    return hexFilePath;
}

QString AvrCompilerV2::normalizePath(QString str){
    return QString("\"%0\"").arg(str);
}
