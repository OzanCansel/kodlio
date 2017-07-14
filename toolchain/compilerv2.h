#ifndef COMPILERV2_H
#define COMPILERV2_H

#include <QQuickItem>

class CompilerV2 : public  QQuickItem
{

    Q_OBJECT

public:

    static void registerQmlType();
    CompilerV2(QQuickItem *parent = Q_NULLPTR);
    void        setDebugEnabled(bool enabled);
    bool        debugEnabled();

protected:

    void        sendStdOutput(QString output);
    void        sendStdError(QString err);
    void        sendCommandOutput(QString &command);
    void        sendInfo(QString info);

signals:

    void        stdOutput(QString   output);
    void        stdError(QString output);
    void        commandOutput(QString output);
    void        infoOutput(QString output);

private:\

    bool        _debugEnabled;

};

#endif // COMPILERV2_H
