#ifndef AVRRUNOPTIONS_H
#define AVRRUNOPTIONS_H

#include <QQuickItem>
#include "../runoptions.h"

class AvrRunOptions : public RunOptions
{

    Q_OBJECT
    Q_PROPERTY(QString  port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString board READ board WRITE setBoard NOTIFY boardChanged)
    Q_PROPERTY(QString hexFile READ hexFile WRITE setHexFile NOTIFY hexFileChanged)

public:

    static void     registerQmlType();
    AvrRunOptions(QQuickItem *parent = Q_NULLPTR);
    void    setPort(QString val);
    void    setBoard(QString val);
    void    setHexFile(QString val);
    QString     port();
    QString     board();
    QString     hexFile();

signals:

    void    portChanged();
    void    boardChanged();
    void    hexFileChanged();

private:

    QString     _board;
    QString     _port;
    QString     _hexFile;

};

#endif // AVRRUNOPTIONS_H
