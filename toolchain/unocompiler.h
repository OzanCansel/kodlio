#ifndef UNOCOMPILER_H
#define UNOCOMPILER_H

#include "avrcompiler.h"

class UnoCompiler : public  AvrCompiler
{

public:

    UnoCompiler(QObject *parent = Q_NULLPTR);

protected:


    QString     getCppParameters() override;
    QString     getCParameters() override;
    QString     getSParameters() override;
    QString     getLinkParameters() override;
    QString     getEepFileCompilingArgs() override;
    QString     getHexFileCompilingArgs() override;
    QString     getUploadHexArgs(QString port) override;

};

#endif // UNOCOMPILER_H
