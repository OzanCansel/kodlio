#ifndef SHPROCESS_H
#define SHPROCESS_H

#include <QProcess>

class ShProcess : public QProcess
{

public:

    ShProcess(QObject *parent = Q_NULLPTR);

    bool        shSync(QString  command , int timeout = 30000);

};

#endif // SHPROCESS_H
