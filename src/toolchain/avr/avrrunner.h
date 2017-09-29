#ifndef AVRRUNNER_H
#define AVRRUNNER_H

#include "toolchain/runner.h"

class AvrRunner : public  Runner
{

    Q_OBJECT

public:

    static void registerQmlType();
    AvrRunner(QQuickItem *parent = Q_NULLPTR);

public slots:

    void        run( RunOptions*  opts);
    QString     normalizePath(QString str);

};

#endif // AVRRUNNER_H
