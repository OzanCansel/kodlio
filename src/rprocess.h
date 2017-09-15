#ifndef ROBOSKOPPROCESS_H
#define ROBOSKOPPROCESS_H

#include <QProcess>

class RProcess : public QProcess
{

public:

    RProcess ();
    int        runWait(QString command , int timeout);

    QString     stdErr();
    QString     stdOut();
    bool        hasStdOut();
    bool        hasStdErr();

public slots:

    void    onStdOut();
    void    onStdErr();

private:

    QString     _stdErr;
    QString     _stdOut;

};

#endif // ROBOSKOPPROCESS_H
