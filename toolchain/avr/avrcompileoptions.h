#ifndef AVRCOMPILEOPTIONS_H
#define AVRCOMPILEOPTIONS_H

#include "toolchain/compileoptions.h"

class AvrCompileOptions : public CompileOptions
{

public:

    static void     registerQmlType();
    AvrCompileOptions(QQuickItem *parent = Q_NULLPTR);

};

#endif // AVRCOMPILEOPTIONS_H
