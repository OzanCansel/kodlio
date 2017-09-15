#ifndef COMPILECONFIGURATION_H
#define COMPILECONFIGURATION_H

#include <QObject>
#include <QQuickItem>

class CompileConfiguration : public QObject
{

    Q_OBJECT

public:

    static void registerQmlType();
    CompileConfiguration(QObject *parent = Q_NULLPTR);

    QString     getCParameters();
    QString     getCppParameters();
    QString     getSParameters();
    QString     getArchiveParameters();
    QString     getElfParameters();
    QString     getEepParameters();
    QString     getHexParameters();

};

#endif // COMPILECONFIGURATION_H
