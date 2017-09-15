#ifndef RUNOPTIONS_H
#define RUNOPTIONS_H

#include "options.h"

class RunOptions : public Options
{

    Q_OBJECT

public:

    static void     registerQmlType();
    RunOptions(QQuickItem *parent = Q_NULLPTR);

};

#endif // RUNOPTIONS_H
