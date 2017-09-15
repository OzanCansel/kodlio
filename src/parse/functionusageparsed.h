#ifndef FUNCTIONUSAGEPARSED_H
#define FUNCTIONUSAGEPARSED_H

#include <QQuickItem>

class FunctionUsageParsed : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString funcName READ functionName WRITE setFunctionName NOTIFY functionNameChanged)
    Q_PROPERTY(QStringList arguments READ args WRITE setArguments NOTIFY argsChanged)

public:
    FunctionUsageParsed(QQuickItem  *parent = Q_NULLPTR);
    FunctionUsageParsed(const FunctionUsageParsed &other);
    FunctionUsageParsed &operator =(const FunctionUsageParsed &other);
    void        setFunctionName(QString funcName);
    void        setArguments(QStringList args);
    void        setMatchIdx(int val);
    void        addArgument(QString arg);
    QString     functionName() const;
    QStringList args() const;
    int         matchIdx() const;
signals:
    void    functionNameChanged();
    void    argsChanged();
private:
    QString     _functionName;
    QStringList _args;
    int         _matchIdx;
};

#endif // FUNCTIONUSAGEPARSED_H
