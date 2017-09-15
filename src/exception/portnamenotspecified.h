#ifndef PORTNAMENOTSPECIFIED_H
#define PORTNAMENOTSPECIFIED_H

#include <QException>
#include <QDebug>

class PortNameNotSpecified : public QException
{
public:

    PortNameNotSpecified();
    void    raise() const {
        qDebug() << "PortName not specified";
        throw *this;
    }

    PortNameNotSpecified*   clone() { return new PortNameNotSpecified(*this); }

private:

    QString     _portName;
};

#endif // PORTNAMENOTSPECIFIED_H
