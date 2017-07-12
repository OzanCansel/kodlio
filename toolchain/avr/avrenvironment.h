#ifndef AVRENVIRONMENT_H
#define AVRENVIRONMENT_H

#include "environment.h"

class AvrEnvironment : public Environment
{

public:

    AvrEnvironment(QQuickItem *parent = Q_NULLPTR);
    QString     gPlusPlus();
    QString     gcc();
    QString     gccAr();
    QString     objcopy();
};

#endif // AVRENVIRONMENT_H
