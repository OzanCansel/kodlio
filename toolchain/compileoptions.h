#ifndef ITOOLCHAINOPTIONS_H
#define ITOOLCHAINOPTIONS_H

#include <QString>
#include <QVariant>
#include "options.h"

class CompileOptions : public Options
{

public:

    static void     registerQmlType();
    CompileOptions(QQuickItem *parent = Q_NULLPTR);

};

#endif // ITOOLCHAINOPTIONS_H
