#ifndef INCOMPATIBLEEXTENSION_H
#define INCOMPATIBLEEXTENSION_H

#include <QException>
#include <QDebug>

class IncompatibleExtension : public QException
{

public:

    IncompatibleExtension(QString message);
    void        raise() const {
        qDebug() << "Error !!! IncompatibleException. Mesaj -> ";
    }
    IncompatibleExtension   *clone() const {return new IncompatibleExtension(*this); }

private:

    QString _message;

};

#endif // INCOMPATIBLEEXTENSION_H
