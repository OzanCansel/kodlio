pragma Singleton
import QtQuick 2.0

QtObject {

    property string currentTheme   :   "techTheme"

    //Colors
    readonly property color     documentHeaderDefaultColor      :   themes[currentTheme].documentHeaderDefaultColor
    readonly property color     documentHeaderSelectedHoverColor:   themes[currentTheme].documentHeaderSelectedHoverColor
    readonly property color     documentProjectHeaderColor      :   themes[currentTheme].documentProjectHeaderColor
    readonly property color     lineNumeratorTextColor          :   themes[currentTheme].lineNumeratorTextColor
    readonly property color     lineNumeratorBackgroundColor    :   themes[currentTheme].lineNumeratorBackgroundColor
    readonly property real      lineNumeratorOpacity            :   themes[currentTheme].lineNumeratorOpacity
    readonly property real      controlSpacing                  :   themes[currentTheme].controlSpacing
    readonly property real      controlXMargin                  :   themes[currentTheme].controlXMargin
    readonly property real      controlYMargin                  :   themes[currentTheme].controlYMargin
    readonly property color     genericContainerBackground      :   themes[currentTheme].genericContainerBackground
    readonly property color     consoleBackgroundColor          :   themes[currentTheme].consoleBackgroundColor
    readonly property color     controlsHeaderTextColor         :   themes[currentTheme].controlsHeaderTextColor
    readonly property color     panelHeadersBackgroundColor     :   themes[currentTheme].panelHeadersBackgroundColor
    readonly property color     editorBackgroundColor           :   themes[currentTheme].editorBackgroundColor
    readonly property color     editorStandardFontColor         :   themes[currentTheme].editorStandardFontColor
    readonly property color     editorModifiedBorderColor       :   themes[currentTheme].editorModifiedBorderColor
    readonly property color     autoCompleteDescriptionColor    :   themes[currentTheme].autoCompleteDescriptionColor
    readonly property color     autoCompleteDescriptionFontColor:   themes[currentTheme].autoCompleteDescriptionFontColor
    readonly property color     compileButtonBackgroundColor    :   themes[currentTheme].compileButtonBackgroundColor
    readonly property color     uploadButtonBackgroundColor     :   themes[currentTheme].uploadButtonBackgroundColor
    readonly property color     dropdownMenuButtonBackColor     :   themes[currentTheme].dropdownMenuButtonBackColor
    readonly property color     dropdownMenuButtonHoverColor    :   themes[currentTheme].dropdownMenuButtonHoverColor
    readonly property color     ideMenuItemHoverBackColor       :   themes[currentTheme].ideMenuItemHoverBackColor
    readonly property color     ideMenuItemBackColor            :   themes[currentTheme].ideMenuItemBackColor
    readonly property color     outputConsoleBackColor          :   themes[currentTheme].outputConsoleBackColor
    readonly property color     stdErrConsoleColor              :   themes[currentTheme].stdErrConsoleColor
    readonly property color     stdOutConsoleColor              :   themes[currentTheme].stdOutConsoleColor
    readonly property color     commandOutConsoleColor          :   themes[currentTheme].commandOutConsoleColor
    readonly property color     genericButtonBackColor          :   themes[currentTheme].genericButtonBackColor
    readonly property color     genericButtonHoverColor         :   themes[currentTheme].genericButtonHoverColor
    readonly property color     genericButtonTextColor          :   themes[currentTheme].genericButtonTextColor
    readonly property color     serialMonitorOutputBackColor    :   themes[currentTheme].serialMonitorOutputBackColor
    readonly property color     dialogBackgroundColor           :   themes[currentTheme].dialogBackgroundColor
    readonly property color     serialMonitorIn                 :   themes[currentTheme].serialMonitorIn
    readonly property color     serialMonitorOut                :   themes[currentTheme].serialMonitorOut
    readonly property color     serialMonitorInfo               :   themes[currentTheme].serialMonitorInfo

    readonly property int       headersLeftMargin               :   10
    readonly property int       headersTopMargin                :   20
    readonly property int       internalControlsMargin          :   6
    readonly property int       consoleNormalHeight             :   220
    readonly property int       consoleCollapsedHeight          :   52

    readonly property variant   themes :   {
        "techTheme"     :   {
            documentProjectHeaderColor          :   "#FFA500",
            documentHeaderDefaultColor          :   "#006f98",
            documentHeaderSelectedHoverColor    :   Qt.lighter(documentHeaderDefaultColor , 1.5),
            controlXMargin                      :   7 ,
            controlYMargin                      :   5 ,
            controlSpacing                      :   6,
            lineNumeratorOpacity                :   1,
            lineNumeratorTextColor              :   "white" ,
//            lineNumeratorBackgroundColor        :   "#006f98",
            lineNumeratorBackgroundColor        :   "#FFA500",
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
