#include "fileutil.h"
#include <QFile>
#include <QTextStream>
#include "exception/filenotexists.h"
#include "exception/filecouldnotopen.h"

FileUtil::FileUtil()
{

}

QString FileUtil::readContent(QString &file){
    QFile   f(file);

    //Dosya mevcut degilse
    if(!f.exists()){
        //Hata firlatiliyor
        FileNotExists(file).raise();
    }

    //Acilamadiysa
    if(!f.open(QIODevice::ReadOnly)){
        //Hata firlatiliyor
        FileCouldNotOpen(file).raise();
    }

    QTextStream ss(&f);

    return ss.readAll();
}
