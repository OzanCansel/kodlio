#ifndef COMPILERERRORPARSER_H
#define COMPILERERRORPARSER_H

#include <QQuickItem>
#include <QList>
#include <QVariantMap>

class CompilerErrorParser :  public QQuickItem
{

    Q_OBJECT


public:
    CompilerErrorParser(QQuickItem *parent = Q_NULLPTR);
public slots:
    void    extractErrors(QString text);
signals:
    void    errorOccurred(QVariantMap err);

private:

};

#endif // COMPILERERRORPARSER_H
