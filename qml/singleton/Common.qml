pragma Singleton
import QtQuick 2.0

Item {
    function    extractPathFromUrl(url){
        var fileName = ""
        if(osInfo.os === "windows")
            return url.replace(/^(file:\/{3})|(qrc:\\{3})|(http:\\{3})/, "")
        else
            return url.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/,"")
    }
}
