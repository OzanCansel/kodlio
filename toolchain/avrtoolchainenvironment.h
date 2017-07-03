#ifndef AVRTOOLCHAINENVIRONMENT_H
#define AVRTOOLCHAINENVIRONMENT_H

#include "environment.h"

class AvrToolchainEnvironment : public Environment
{

public:

    AvrToolchainEnvironment(QQuickItem *parent = Q_NULLPTR);
    QString     coreLibs();
    QString     standardVariants();
    QString     variants(QString boardName);

};

#endif // AVRTOOLCHAINENVIRONMENT_H
