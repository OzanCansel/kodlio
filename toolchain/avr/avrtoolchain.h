#ifndef AVRTOOLCHAIN_H
#define AVRTOOLCHAIN_H

#include <QQuickItem>
#include "toolchain/toolchain.h"


class AvrToolchain : public Toolchain
{

public:

    AvrToolchain(QQuickItem *parent = Q_NULLPTR);

};

#endif // AVRTOOLCHAIN_H
