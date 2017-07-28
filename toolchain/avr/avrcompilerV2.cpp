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
        includesText.append(QString("-I%0 ").arg(includePath));
    }

    includesText.append(QString("-I%0 ").arg(env.variants(boardName)));

    //gcc <parametreler> <includePath> <inputFile> -o <outputFile>
    QString command = QString("%0 %1 %2 %3 -o %4").arg(env.gcc())
            .arg(board->objectCodeParams(fileExtension))
            .arg(includesText)
            .arg(file)
            .arg(output);


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
        QString command = QString("%0 rcs %1 %2").arg(env.gccAr())
                .arg(output)
                .arg(objFile);

        sendCommandOutput(command);
        //Baslatiliyor
        archiveProcess.start(command);
        archiveProcess.waitForFinished();

        //Basarili degilse
        if(archiveProcess.exitCode() != 0){
            QString     err = archiveProcess.readAllStandardError();
            sendStdError(QString("%0 arsivlenirken hata -> ").arg(objFile).arg(err));
            sendCompileError();
            //Hata firlatiliyor
            CompileError(err).raise();
        }
    }
}

QString AvrCompilerV2::generateHex(QString &objFile, QString &archiveFile, QString &buildFolder , QStringList& generatedObjFiles){
    QString elfFilePath = QString(buildFolder).append("/output.elf");
    QString eepFilePath = QString(buildFolder).append("/output.eep");
    QString hexFilePath = QString(buildFolder).append("/output.hex");
    BoardFactory    factory;
    AvrEnvironment  env;
    ArduinoBoard*   board = factory.create("uno");  //Simdilik uno hardcoded olarak uretiliyor

    bool interrupted  = false;  //Islem  yarida kesilirse true

    QString     objFilesText(objFile);

    foreach (QString objFile, generatedObjFiles) {
        objFilesText.append(QString(" %0").arg(objFile));
    }

    //<avr-gcc> <params> -o <outputFile> <inputFile> <archiveFile> -L<buildFolder> -lm
    QString generateElfCommand = QString("%0 %1 -o %2 %3 %4 -L%5 -lm")
            .arg(env.gcc()) //0
            .arg(board->elfParams()) //1
            .arg(elfFilePath) //2
            .arg(objFilesText) //objFiles
            .arg(archiveFile)
            .arg(buildFolder);

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
        CompileError(actualError).raise();
    }

    //<objcopy> <params> <inputElf> <outputEep>
    QString generateEepCommand = QString("%0 %1 %2 %3").arg(env.objcopy())
            .arg(board->eepParams())
            .arg(elfFilePath)
            .arg(eepFilePath);;

    sendCommandOutput(generateEepCommand);
    //Eep uretiliyor
    process.start(generateEepCommand);
    interrupted = !process.waitForFinished();

    if(interrupted || process.exitCode() != 0){
        QString     err(".eep dosyasi uretilirken hata !");
        sendStdError(err);
        sendCompileError();
        CompileError(err).raise();
    }

    //<objcopy> <params> <inputElf> <outputHex>
    QString generateHexCommand = QString("%0 %1 %2 %3").arg(env.objcopy())
            .arg(board->hexParams())
            .arg(elfFilePath)
            .arg(hexFilePath);;

    //Hex uretiliyor
    process.start(generateHexCommand);
    interrupted = !process.waitForFinished();

    //Hata
    if(interrupted || process.exitCode() != 0){
        QString     err(".hex dosyasi uretilirken hata !");
        sendStdError(err);
        sendCompileError();
        CompileError(err).raise();
    }

    return hexFilePath;
}
