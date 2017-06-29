#ifndef COMPILERV2_H
#define COMPILERV2_H

#include <QQuickItem>

class CompilerV2 : public  QQuickItem
{

    Q_OBJECT

public:

    CompilerV2(QQuickItem *parent = Q_NULLPTR);
    void        setDebugEnabled(bool enabled);
    bool        debugEnabled();

protected:

    void        sendStdOutput(QString output);
    void        sendStdError(QString err);
    void        sendCommandOutput(QString command);

signals:

    void        stdOutput(QString   output);
    void        stdError(QString error);
    void        commandOutput(QString command);

private:\

    bool        _debugEnabled;

};

#endif // COMPILERV2_H
