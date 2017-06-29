pragma Singleton
import QtQuick 2.0

QtObject {

    property string currentTheme   :   "techTheme"

    //Colors
    readonly property color     genericContainerBackground      :   orangeTheme[currentTheme].genericContainerBackground
    readonly property color     consoleBackgroundColor          :   orangeTheme[currentTheme].consoleBackgroundColor
    readonly property color     controlsHeaderTextColor         :   orangeTheme[currentTheme].controlsHeaderTextColor
    readonly property color     panelHeadersBackgroundColor     :   orangeTheme[currentTheme].panelHeadersBackgroundColor
    readonly property color     editorBackgroundColor           :   orangeTheme[currentTheme].editorBackgroundColor
    readonly property color     editorStandardFontColor         :   orangeTheme[currentTheme].editorStandardFontColor
    readonly property color     editorModifiedBorderColor       :   orangeTheme[currentTheme].editorModifiedBorderColor
    readonly property color     autoCompleteDescriptionColor    :   orangeTheme[currentTheme].autoCompleteDescriptionColor
    readonly property color     autoCompleteDescriptionFontColor:   orangeTheme[currentTheme].autoCompleteDescriptionFontColor
    readonly property color     compileButtonBackgroundColor    :   orangeTheme[currentTheme].compileButtonBackgroundColor
    readonly property color     uploadButtonBackgroundColor     :   orangeTheme[currentTheme].uploadButtonBackgroundColor
    readonly property color     dropdownMenuButtonBackColor     :   orangeTheme[currentTheme].dropdownMenuButtonBackColor
    readonly property color     dropdownMenuButtonHoverColor    :   orangeTheme[currentTheme].dropdownMenuButtonHoverColor
    readonly property color     ideMenuItemHoverBackColor       :   orangeTheme[currentTheme].ideMenuItemHoverBackColor
    readonly property color     ideMenuItemBackColor            :   orangeTheme[currentTheme].ideMenuItemBackColor
    readonly property color     outputConsoleBackColor          :   orangeTheme[currentTheme].outputConsoleBackColor
    readonly property color     stdErrConsoleColor              :   orangeTheme[currentTheme].stdErrConsoleColor
    readonly property color     stdOutConsoleColor              :   orangeTheme[currentTheme].stdOutConsoleColor
    readonly property color     commandOutConsoleColor          :   orangeTheme[currentTheme].commandOutConsoleColor
    readonly property color     genericButtonBackColor          :   orangeTheme[currentTheme].genericButtonBackColor
    readonly property color     genericButtonHoverColor         :   orangeTheme[currentTheme].genericButtonHoverColor
    readonly property color     genericButtonTextColor          :   orangeTheme[currentTheme].genericButtonTextColor
    readonly property color     serialMonitorOutputBackColor    :   orangeTheme[currentTheme].serialMonitorOutputBackColor
    readonly property color     dialogBackgroundColor           :   orangeTheme[currentTheme].dialogBackgroundColor
    readonly property color     serialMonitorIn                 :   orangeTheme[currentTheme].serialMonitorIn
    readonly property color     serialMonitorOut                :   orangeTheme[currentTheme].serialMonitorOut
    readonly property color     serialMonitorInfo               :   orangeTheme[currentTheme].serialMonitorInfo

    readonly property int       headersLeftMargin               :   10
    readonly property int       headersTopMargin                :   20
    readonly property int       internalControlsMargin          :   6
    readonly property int       consoleNormalHeight             :   220
    readonly property int       consoleCollapsedHeight          :   52

    readonly property variant   orangeTheme :   {
        "orangeTheme"    :  {
            "genericContainerBackground"        :   "#282828" ,
            "consoleBackgroundColor"            :   "black" ,
            "controlsHeaderTextColor"           :   "white" ,
            "panelHeadersBackgroundColor"       :   "#01303f" ,
            "editorBackgroundColor"             :   "white" ,
            "editorStandardFontColor"           :   "#2f2f2f" ,
            "editorModifiedBorderColor"         :   "lightsteelblue" ,
            "autoCompleteDescriptionColor"      :   "#FFA500" ,
            "autoCompleteDescriptionFontColor"  :   "#333334" ,
            "autoCompleteDescriptionFontColor"  :   "#333334" ,
            "compileButtonBackgroundColor"      :   "#027af7" ,
            "uploadButtonBackgroundColor"       :   "#027af7" ,
            "dropdownMenuButtonBackColor"       :   "#00bc8f" ,
            "dropdownMenuButtonHoverColor"      :   "#00a782" ,
            "ideMenuItemBackColor"              :   "#ff6e00",
            "ideMenuItemHoverBackColor"         :   "#ffff00" ,
            "outputConsoleBackColor"            :   "#ffa500" ,
            "stdErrConsoleColor"                :   "#ff0700" ,
            "stdOutConsoleColor"                :   "#ffa500" ,
            "commandOutConsoleColor"            :   "#00DF00" ,
            "genericButtonBackColor"            :   "#ff6e00" ,
            "genericButtonHoverColor"           :   "#ff4f00" ,
            "genericButtonTextColor"            :   "#ffffff" ,
            "serialMonitorOutputBackColor"      :   "white"   ,
            "dialogBackgroundColor"             :   "#01303f"
        }   ,
        "techTheme"     :   {
            "genericContainerBackground"        :   "#282828" ,
            "consoleBackgroundColor"            :   "black" ,
            "controlsHeaderTextColor"           :   "white" ,
            "panelHeadersBackgroundColor"       :   "#FFA500" ,
            "editorBackgroundColor"             :   "white" ,
            "editorStandardFontColor"           :   "#2f2f2f" ,
            "editorModifiedBorderColor"         :   "#ff5500" ,
            "autoCompleteDescriptionColor"      :   "#FFA500" ,
            "autoCompleteDescriptionFontColor"  :   "#333334" ,
            "autoCompleteDescriptionFontColor"  :   "#333334" ,
            "compileButtonBackgroundColor"      :   "#027af7" ,
            "uploadButtonBackgroundColor"       :   "#027af7" ,
            "dropdownMenuButtonBackColor"       :   "#0064cf" ,
            "dropdownMenuButtonHoverColor"      :   "#ff4b17" ,
            "ideMenuItemBackColor"              :   "#ff8e10" ,
            "ideMenuItemHoverBackColor"         :   "#fffc00" ,
            "outputConsoleBackColor"            :   "#00DF00" ,
            "stdErrConsoleColor"                :   "#ff0700" ,
            "stdOutConsoleColor"                :   "#ffa500" ,
            "commandOutConsoleColor"            :   "#00DF00" ,
            "genericButtonBackColor"            :   "#ff6e00" ,
            "genericButtonHoverColor"           :   "#ff4f00" ,
            "genericButtonTextColor"            :   "#000000" ,
            "serialMonitorOutputBackColor"      :   "#0064cf" ,
            "serialMonitorIn"                   :   "#0ad4f8" , //#0a9ff8
            "serialMonitorOut"                  :   "#fff818" ,
            "serialMonitorInfo"                 :   "#00F500" ,
            "dialogBackgroundColor"             :   "#transparent"
        }
    }
}
