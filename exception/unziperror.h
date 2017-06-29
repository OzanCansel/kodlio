#ifndef UNZIPERROR_H
#define UNZIPERROR_H

#include <QDebug>
#include <QException>

class UnzipError : public QException
{

public:

    UnzipError(QString unzippingFile);
    void    raise() const {
        qDebug() << "UnzipError Hata -> " << _file << " zip dosyasi cikartilamadi.";

        throw *this;
    }
    UnzipError *clone(){return new UnzipError(*this); }

private:

    QString         _file;


};

#endif // UNZIPERROR_H
