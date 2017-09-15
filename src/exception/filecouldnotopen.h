#ifndef FILECOULDNOTOPEN_H
#define FILECOULDNOTOPEN_H

#include <QException>
#include <QDebug>

class FileCouldNotOpen : public QException
{

public:

    FileCouldNotOpen(QString file);
    void    raise() const {
        qDebug() << "Error !!! -> FileCouldNotOpen " << _file << " acilamiyor.";

        throw *this;
    }
    FileCouldNotOpen    *clone() const {    return new FileCouldNotOpen(*this); }

private:

    QString     _file;
};

#endif // FILECOULDNOTOPEN_H
