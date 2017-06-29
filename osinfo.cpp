#include "osinfo.h"

QString OsInfo::osName(){
#if defined(Q_OS_ANDROID)
    return QLatin1String("android");
#elif defined(Q_OS_BLACKBERRY)
    return QLatin1String("blackberry");
#elif defined(Q_OS_IOS)
    return QLatin1String("ios");
#elif defined(Q_OS_MACOS)
    return QLatin1String("macos");
#elif defined(Q_OS_TVOS)
    return QLatin1String("tvos");
#elif defined(Q_OS_WATCHOS)
    return QLatin1String("watchos");
#elif defined(Q_OS_WINCE)
    return QLatin1String("wince");
#elif defined(Q_OS_WIN)
    return QLatin1String("windows");
#elif defined(Q_OS_LINUX)
    return QLatin1String("linux");
#elif defined(Q_OS_UNIX)
    return QLatin1String("unix");
#else
    return QLatin1String("unknown");
#endif
}

QString OsInfo::os(){
    return osName();
}
