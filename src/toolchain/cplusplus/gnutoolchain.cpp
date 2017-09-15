#include "gnutoolchain.h"
#include <QList>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include "traverse/filetraverse.h"
#include "traverse/traversedfileinfo.h"
#include "toolchain/cplusplus/cplusenvironment.h"

GnuToolChain::GnuToolChain(QQuickItem *parent) : ToolchainV2(parent)
{

}

void GnuToolChain::run(RunOptions *options){

}

void GnuToolChain::compile(QString folder , CompileOptions *opts){
    FileTraverse                traverser;
    _compiler.setDebugEnabled(true);
    QList<TraversedFileInfo>    files           =   traverser.traverseRecursively(folder);
    QString                     outputFolder    =   opts->get("buildFolder").toString();
    QString                     appName         =   opts->get("appName").toString();
    QStringList                 objectFiles;

    //Derlenilecek klasor olusturuluyor
    QDir    dir;
    dir.mkpath(outputFolder);

    foreach (TraversedFileInfo file, files) {

        if(!file.info().isFile() || !file.info().fileName().contains(".cpp"))
            continue;

        //Bilgilendirme mesaji bastiriliyor
        if(debugEnabled()){
            QString     infoStr =   QString(file.info().fileName()).append(" derleniyor...");
            qDebug() << infoStr;
            sendCommandOutput(infoStr);
        }

        //Klasordeki tum dosyalar derleniyor
        QString     objCodeOutput   =   QDir(outputFolder).filePath(file.info().fileName()).append(".o");
        objectFiles.append(objCodeOutput);
        _compiler.generateObjectCode(file.info().filePath() ,  objCodeOutput , opts);
    }

    if(debugEnabled()) qDebug() << "Makine kodu uretiliyor.";
    _compiler.createExecutable(QString(outputFolder).append("/").append(appName) , objectFiles);
}


CompilerV2* GnuToolChain::compiler(){
    return &_compiler;
}
