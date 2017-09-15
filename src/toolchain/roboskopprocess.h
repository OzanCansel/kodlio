#ifndef ROBOSKOPPROCESS_H
#define ROBOSKOPPROCESS_H

#include <QProcess>

class RoboskopProcess : public  QProcess
{

    Q_OBJECT

public:

    static bool     startProcess(QString command , QStringList args);
    static bool     startProcess(QString command , QString &stdOut , QString &stdErr);
    RoboskopProcess(QObject *parent = Q_NULLPTR);

};

#endif // ROBOSKOPPROCESS_H
