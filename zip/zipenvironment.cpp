#include "zipenvironment.h"

ZipEnvironment::ZipEnvironment(QQuickItem *parent ) : Environment(parent)
{
    set("zipDir" , get("toolsDir").append("/7zip"));
    set("zipExecutable" , get("zipDir").append("/7za"));
}
