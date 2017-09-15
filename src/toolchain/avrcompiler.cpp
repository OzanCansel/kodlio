#include "avrcompiler.h"
#include "sdkextractor.h"
#include <QDebug>

AvrCompiler::AvrCompiler(QObject *parent) : QObject(parent)
{
    //Arduinoyu compoile etmek için gerekli dosya isimleri veriliyor
    coreFiles << "wiring_pulse.S" << "WInterrupts.c" << "hooks.c" << "wiring.c";
    coreFiles << "wiring_analog.c" << "wiring_digital.c" << "wiring_pulse.c" << "wiring_shift.c";
    coreFiles << "wiring_shift.c" << "CDC.cpp" << "HardwareSerial.cpp" << "HardwareSerial0.cpp";
    coreFiles << "HardwareSerial1.cpp" << "HardwareSerial2.cpp" << "HardwareSerial3.cpp" << "IPAddress.cpp";
    coreFiles << "PluggableUSB.cpp" << "Print.cpp" << "Stream.cpp" << "Tone.cpp" << "USBCore.cpp" << "WMath.cpp" << "WString.cpp";
    coreFiles << "abi.cpp" << "main.cpp" << "new.cpp";

    _standardOutputEnabled  =   false;
    _errorOutputEnabled     =   false;
    _debugEnabled           =   false;

}

bool AvrCompiler::compileCoreFiles(QString outputFolder){

    QString libName = QString(outputFolder).append("/core");


    foreach (QString coreFile, coreFiles) {

        bool result = generateObjectCode(getArduinoCoreFilesPath().append("/").append(coreFile) , outputFolder);

        if(!result)
            return false;
    }

    foreach (QString coreFile, coreFiles) {
        bool result = archiveObjectCodeToLib(outputFolder + QString("/").append(coreFile.append(".o")) , libName);

        if(!result)
            return false;
    }

    _archivedLibPath = QString(libName).append(".a");

    return true;
}

bool AvrCompiler::generateObjectCode(QString inputFile, QString outputPath){
    QString     fileExtension = getFileExtension(inputFile);

    if(fileExtension == ".S"){
        compileSFile(inputFile , outputPath);
    }   else if(fileExtension == ".c"){
        compileCFile(inputFile , outputPath);
    }   else if(fileExtension == ".cpp"){
        compileCppFile(inputFile , outputPath);
    }

    return true;
}

bool AvrCompiler::compileSFile(QString inputPath , QString outputFolder){

    QString command;

    command.append("avr-gcc ");
//    command.append(SdkExtractor::avrBinPath().append("/avr-gcc "));
    command.append(getSParameters());
    command.append(" ");
    command.append(QString("-I").append(getArduinoCoreFilesPath()));
    command.append(" ");
    command.append(QString("-I").append(getArduinoStandardVariantsPath()));
    command.append(" ");
    command.append(inputPath);
    command.append(" -o ");
    command.append(QString(outputFolder).append("/").append(extractFileNameWithExtension(inputPath)).append(".o"));

    if(_debugEnabled)
        qDebug() << command;

    if(_standardOutputEnabled)
        emit standardOutput(command);

    QProcess    process;

    process.start("sh" , QStringList() << "-c" << command);

    bool result = process.waitForFinished();

    //Eğer işlem başarısızsa
    if(!result){

        QString     error = getErrorOutput(process);

        if(_errorOutputEnabled)
            emit    errorOutput(error);

        if(_debugEnabled)
            qDebug() << error;
    }

    return result;
}

bool AvrCompiler::compileCFile(QString inputPath, QString outputFolder){

    QString      command;

    command.append("avr-gcc ");
//    command.append(SdkExtractor::avrBinPath().append("/avr-gcc "));
    command.append(getCParameters());
    command.append(" ");
    command.append(QString("-I").append(getArduinoCoreFilesPath()));
    command.append(" ");
    command.append(QString("-I").append(getArduinoStandardVariantsPath()));
    command.append(" ");
    command.append(inputPath);
    command.append(" -o ");
    command.append(QString(outputFolder).append("/").append(extractFileNameWithExtension(inputPath)).append(".o"));

    if(_debugEnabled)
        qDebug() << command;

    if(_standardOutputEnabled)
        emit standardOutput(command);

    QProcess    process;

    process.start("sh" , QStringList() << "-c" << command);

    bool result = process.waitForFinished();

    //Eğer işlem başarısızsa
    if(!result){
        QString     error = getErrorOutput(process);
        if(_errorOutputEnabled)
            emit    errorOutput(error);
        if(_debugEnabled)
            qDebug() << error;
    }

    return result;
}

bool AvrCompiler::compileCppFile(QString inputPath, QString outputFolder){

    QString      command;

    command.append("avr-g++ ");
//    command.append(SdkExtractor::avrBinPath().append("/avr-g++ "));
    command.append(getCppParameters());
    command.append(" ");
    command.append(QString("-I").append(getArduinoCoreFilesPath()));
    command.append(" ");
    command.append(QString("-I").append(getArduinoStandardVariantsPath()));
    command.append(" ");
    command.append(inputPath);
    command.append(" -o ");
    command.append(QString(outputFolder).append("/").append(extractFileNameWithExtension(inputPath)).append(".o"));

    if(_debugEnabled)
        qDebug() << command;

    if(_standardOutputEnabled)
        emit standardOutput(command);

    QProcess    process;

    process.start("sh" , QStringList() << "-c" << command);

    bool result = process.waitForFinished();

//    //Eğer işlem başarısızsa
//    if(!result){

//        QString     error = getErrorOutput(process);

//        if(_errorOutputEnabled)
//            emit    errorOutput(error);

//        if(_debugEnabled)
//            qDebug() << error;
//    }

    QString     error = getErrorOutput(process);

    if(!error.isEmpty())
        emit errorOutput(error);

    return result;
}

bool AvrCompiler::archiveObjectCodeToLib(QString inputFile, QString outputFileWithoutExtension){
    QString     command;

    command.append("avr-gcc-ar rcs ");
//    command.append(SdkExtractor::avrBinPath().append("/avr-gcc-ar rcs "));
    command.append(outputFileWithoutExtension.append(".a"));
    command.append(" ");
    command.append(inputFile);

    if(_debugEnabled)
        qDebug() << command;

    if(_standardOutputEnabled)
        emit standardOutput(command);

    QProcess    process;

    process.start("sh" , QStringList() << "-c" << command);

    bool result = process.waitForFinished();

    //Eğer işlem başarısızsa
    if(!result){

        QString     error = getErrorOutput(process);

        if(_errorOutputEnabled)
            emit    errorOutput(error);

        if(_debugEnabled)
            qDebug() << error;
    }

    return result;
}

QString AvrCompiler::extractFileNameWithExtension(QString &fileFullPath){
    int idx = fileFullPath.lastIndexOf("/");

    QStringRef  fileName(&fileFullPath , idx + 1 , fileFullPath.length() - idx - 1);

    return fileName.toString();
}

QString AvrCompiler::getArduinoCoreFilesPath(){
    //    return "/home/arnest/Downloads/arduino-1.6.13/hardware/arduino/avr/cores/arduino";
//    return "/usr/share/arduino/hardware/arduino/cores/arduino";
    return SdkExtractor::arduinoCorePath();
}

QString AvrCompiler::getArduinoStandardVariantsPath(){
    //    return  "/home/arnest/Downloads/arduino-1.6.13/hardware/arduino/avr/variants/standard";
//    return "/usr/share/arduino/hardware/arduino/variants/standard";
    return SdkExtractor::variantsStandardPath();
}

QString AvrCompiler::getFileExtension(QString &file){
    //Eğer gelen string boşsa geriye boş string döndürülüyor
    if(file.isEmpty())
        return "";

    int dotLastIndex = file.lastIndexOf(".");

    //Eğer ki gelen dosya adı nokta içermiyorsa g eriye boş string döndürülüyor
    if(dotLastIndex == -1)
        return "";

    QStringRef extensionRef(&file , dotLastIndex , file.length() - dotLastIndex);

    return extensionRef.toString();
}

bool AvrCompiler::generateElfFile(QString inputFile, QString libFile, QString output){
    QString      command;

    command.append("avr-gcc ");
//    command.append(SdkExtractor::avrBinPath().append("/avr-gcc "));
    command.append(getLinkParameters());
    command.append(" -o ");
    command.append(QString(output).append("/").append(inputFile).append(".elf"));
    command.append(" ");
    command.append(QString(output).append("/").append(inputFile).append(".o"));
    command.append(" ");
    command.append(libFile);
    command.append(" -L");
    command.append(output);
    command.append(" -lm");

    if(_debugEnabled)
        qDebug() << command;

    if(_standardOutputEnabled)
        emit standardOutput(command);

    QProcess    process;

    process.start("sh" , QStringList() << "-c" << command);

    bool result = process.waitForFinished();

    //Eğer işlem başarısızsa
    if(!result){

        QString     error = getErrorOutput(process);

        if(_errorOutputEnabled)
            emit    errorOutput(error);

        if(_debugEnabled)
            qDebug() << error;
    }

    return result;
}

bool AvrCompiler::generateEepFile(QString inputFile){

    QString     command;

    command.append("avr-objcopy ");
//    command.append(SdkExtractor::avrBinPath().append("/avr-objcopy "));
    command.append(getEepFileCompilingArgs());
    command.append(" ");
    command.append(QString(inputFile).append(".elf"));
    command.append(" ");
    command.append(QString(inputFile).append(".eep"));

    if(_debugEnabled)
        qDebug() << command;

    if(_standardOutputEnabled)
        emit standardOutput(command);

    QProcess    process;

    process.start("sh" , QStringList() << "-c" << command);

    bool result = process.waitForFinished();

    //Eğer işlem başarısızsa
    if(!result){

        QString     error = getErrorOutput(process);

        if(_errorOutputEnabled)
            emit    errorOutput(error);

        if(_debugEnabled)
            qDebug() << error;
    }

    return result;
}

bool AvrCompiler::generateHexFile(QString inputFile){

    QString     command;

    command.append("avr-objcopy ");
//    command.append(SdkExtractor::avrBinPath().append("/avr-objcopy "));
    command.append(getHexFileCompilingArgs());
    command.append(" ");
    command.append(QString(inputFile).append(".elf"));
    command.append(" ");
    command.append(QString(inputFile).append(".hex"));

    if(_debugEnabled)
        qDebug() << command;

    if(_standardOutputEnabled)
        emit standardOutput(command);

    QProcess    process;

    process.start("sh" , QStringList() << "-c" << command);

    bool result = process.waitForFinished();

    //Eğer işlem başarısızsa
    if(!result){

        QString     error = getErrorOutput(process);

        if(_errorOutputEnabled)
            emit    errorOutput(error);

        if(_debugEnabled)
            qDebug() << error;
    }

    return result;
}

bool AvrCompiler::uploadHexFile(QString inputFile , QString port){
    QString     command;

    command.append(SdkExtractor::avrBinPath().append("avrdude "));
    command.append("-C").append(SdkExtractor::avrdudeConfPath());
    command.append(getUploadHexArgs(port));
    command.append(inputFile);
    command.append(":i");

    if(_debugEnabled)
        qDebug() << command;

    if(_standardOutputEnabled)
        emit standardOutput(command);

    QProcess    process;

    process.start("sh" , QStringList() << "-c" << command);

    bool result = process.waitForFinished();

    //Eğer işlem başarısızsa
    if(!result){

        QString     error = getErrorOutput(process);

        if(_errorOutputEnabled)
            emit    errorOutput(error);

        if(_debugEnabled)
            qDebug() << error;
    }

    QString     out = getErrorOutput(process);
    emit standardOutput(out);

    qDebug() << out;

    return result;
}

bool AvrCompiler::compileProject(QString projFolder){

    QString mainFileName = "sketch.cpp";

    compileCoreFiles(projFolder);
    generateObjectCode(QString(projFolder).append("/").append(mainFileName) , projFolder);
    generateElfFile("sketch.cpp" , _archivedLibPath , projFolder);
    generateEepFile(QString(projFolder).append("/").append(mainFileName));
    generateHexFile(QString(projFolder).append("/").append(mainFileName));

    return true;
}

bool AvrCompiler::uploadProject(QString projFolder){
    return uploadHexFile(projFolder.append("/sketch.cpp.hex") , "/dev/ttyUSB0");
}

QString AvrCompiler::getErrorOutput(QProcess &process){
    return QString((process.readAllStandardError()));
}

void AvrCompiler::setStandardOutputEnabled(bool enabled){
    _standardOutputEnabled = enabled;
}

void AvrCompiler::setErrorOutputEnabled(bool enabled){
    _errorOutputEnabled = enabled;
}

void AvrCompiler::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

bool AvrCompiler::standardOutputEnabled(){
    return _standardOutputEnabled;
}

bool AvrCompiler::errorOutputEnabled(){
    return _errorOutputEnabled;
}
