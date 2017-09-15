#ifndef FILENOTEXISTS_H
#define FILENOTEXISTS_H

#include <QException>
#include <QDebug>

class FileNotExists : public QException
{

public:

    FileNotExists(QString file);
    void    raise() const{
        qDebug() << _file << " mevcut degil";
        throw *this;
    }
    FileNotExists*  clone() const{return new FileNotExists(*this);}

private:

    QString _file;

};

#endif // FILENOTEXISTS_H
