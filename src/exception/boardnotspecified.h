#ifndef BOARDNOTSPECIFIED_H
#define BOARDNOTSPECIFIED_H

#include <QDebug>
#include <QException>

class BoardNotSpecified : public QException
{

public:

    BoardNotSpecified(QString message);
    void    raise() const {
        qDebug() << "Error !!! BoardNotSpecified -> Mesaj -> " << _message;
        throw *this;
    }
    BoardNotSpecified   *clone() const {    return new BoardNotSpecified(*this); }

private:

    QString     _message;

};

#endif // BOARDNOTSPECIFIED_H
