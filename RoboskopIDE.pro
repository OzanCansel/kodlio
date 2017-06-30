QT += qml quick widgets serialport

CONFIG += c++11
            qml_debug

#QMAKE_LFLAGS += -static-libgcc -static-libstdc++

win32 {
        CONFIG(debug, debug|release) {
                PWD_WIN = $${PWD}
                PWD_WIN ~= s,/,\\,g
                OUT_PWD_WIN = $${OUT_PWD}
                OUT_PWD_WIN ~= s,/,\\,g
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\* $${OUT_PWD_WIN}\\debug\\ /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\sdk $${OUT_PWD_WIN}\\debug\\sdk /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\drivers $${OUT_PWD_WIN}\\debug\\drivers /e

                message(robocopy $${PWD_WIN}\\extFiles\\windows\\drivers $${OUT_PWD_WIN}\\debug\\drivers /e)

        } else {
                PWD_WIN = $${PWD}
                PWD_WIN ~= s,/,\\,g
                OUT_PWD_WIN = $${OUT_PWD}
                OUT_PWD_WIN ~= s,/,\\,g
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\* $${OUT_PWD_WIN}\\release\\ /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\sdk $${OUT_PWD_WIN}\\release\\sdk /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\drivers $${OUT_PWD_WIN}\\release\\drivers /e

        }
}

unix    {
    QMAKE_POST_LINK     +=  cp -r $${PWD}/extFiles/linux/* $${OUT_PWD}
}

SOURCES += main.cpp \
    editorhighlight.cpp \
    highlighter.cpp \
    toolchain/avrcompiler.cpp \
    toolchain/unocompiler.cpp \
    directorymanager.cpp \
    projectmanager.cpp \
    exception/workingdirectorynull.cpp \
    exception/invalidprojectdirectory.cpp \
    thread/compileworker.cpp \
    thread/uploadworker.cpp \
    exception/tempdirectorycreationfailed.cpp \
    exception/workingdirectorynotset.cpp \
    shprocess.cpp \
    sdkextractor.cpp \
    cloudapi/cloud.cpp \
    cloudapi/cloudresponse.cpp \
    jsonstorage.cpp \
    serialport.cpp \
    editor/editormanager.cpp \
    editor/editorstyle.cpp \
    toolchain/toolchain.cpp \
    toolchain/compiler.cpp \
    toolchain/roboskopprocess.cpp \
    toolchain/compileconfiguration.cpp \
    roboskopenvironment.cpp \
    toolchain/programmer.cpp \
    toolchain/programmerconfiguration.cpp \
    texttemplate/texttemplate.cpp \
    texttemplate/classheadertemplate.cpp \
    texttemplate/classcpptemplate.cpp \
    thread/compileworkerv2.cpp \
    thread/compileanduploadworkerv2.cpp \
    exception/compileerror.cpp \
    parse/functionparser.cpp \
    parse/functionusageparsed.cpp \
    generate/func/digitalwritedescgenerator.cpp \
    generate/func/funcdescgenerator.cpp \
    parse/parsehelper.cpp \
    generate/codedescriptiongenerator.cpp \
    generate/codedescriptioninfo.cpp \
    generate/func/delaydescgenerator.cpp \
    generate/func/serialprintdescgenerator.cpp \
    generate/func/pinmodedescgenerator.cpp \
    generate/func/serialbegindescgenerator.cpp \
    parse/compilererrorparser.cpp \
    generate/func/digitalreaddescgenerator.cpp \
    generate/func/analogreaddescgenerator.cpp \
    generate/func/tonedescgeneratoro2.cpp \
    generate/func/tonedescgeneratoro1.cpp \
    generate/func/notonedescgenerator.cpp \
    generate/func/pulseindescgeneratoro1.cpp \
    generate/func/pulseindescgeneratoro2.cpp \
    parse/conditionparser.cpp \
    parse/selectorstrings.cpp \
    osinfo.cpp \
    settings/editorsettings.cpp \
    traverse/projecttraverse.cpp \
    toolchain/gnugcctoolchain.cpp \
    toolchain/toolchainV2.cpp \
    toolchain/runoptions.cpp \
    options.cpp \
    toolchain/compileoptions.cpp \
    traverse/filetraverse.cpp \
    traverse/traversedfileinfo.cpp \
    toolchain/cplusplus/gnutoolchain.cpp \
    toolchain/cplusplus/cpluscompiler.cpp \
    toolchain/compilerv2.cpp \
    toolchain/cplusplus/cpluscompileoptions.cpp \
    environment.cpp \
    toolchain/cplusplus/cplusenvironment.cpp \
    rprocess.cpp \
    arduinoLibManager/librarymanager.cpp \
    http/roboskopnetworkmanager.cpp \
    arduinoLibManager/arduinolibdescription.cpp \
    arduinoLibManager/arduinolibenvironment.cpp \
    arduinoLibManager/arduinolibdownloader.cpp \
    zip/zipenvironment.cpp \
    zip/zipextractor.cpp \
    zip/zip7zextractor.cpp \
    exception/environmentvariablenotset.cpp \
    http/internetaccessibility.cpp \
    exception/unziperror.cpp \
    traverse/arduinolibrarytraverse.cpp

RESOURCES += qml.qrc \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = kodlio.ico

DISTFILES += \
    qml/AppMenu.qml \
    main.qml \
    qml/OutputConsole.qml \
    qml/TextEditor.qml \
    qml/qmldir \
    qml/control/ExpandCollapseButton.qml \
    qml/CompileControlBar.qml \
    qml/AutoCompleteItem.qml \
    qml/AutoCompleteItemVisual.qml \
    qml/Enum.qml \
    qml/ArduinoDefinitions.qml \
    qml/autocomplete/AutoCompleteSet.qml \
    qml/autocomplete/AutoCompleteItem.qml   \
    qml/autocomplete/AutoCompleteItemVisual.qml \
    qml/autocomplete/ArduinoFunctionsSet.qml \
    qml/form/LoginForm.qml \
    qml/dialog/LoginDialog.qml \
    qml/control/CloudStateControl.qml \
    qml/dialog/ListProjectsDialog.qml \
    qml/form/ListProjectsForm.qml \
    qml/control/Toast.qml \
    qml/control/ToastComponent.qml \
    qml/form/SerialPortListForm.qml \
    qml/control/IdeMenuItem.qml \
    qml/control/ProjectMenu.qml \
    qml/singleton/Theme.qml \
    qml/singleton/Global.qml \
    qml/singleton/Enum.qml \
    qml/control/DropdownMenuItem.qml \
    qml/form/SerialMonitorForm.qml \
    qml/dialog/SerialMonitorDialog.qml \
    qml/control/GenericButton.qml \
    qml/control/GenericLabel.qml \
    qml/singleton/Color.qml \
    qml/control/GenericCombobox.qml \
    qml/form/CreateProjectForm.qml \
    qml/dialog/CreateProjectDialog.qml \
    qml/singleton/Common.qml \
    qml/control/GenericTextBox.qml \
    qml/dialog/CreateNewClassDialog.qml \
    qml/form/CreateNewClassForm.qml \
    qml/control/FileBrowser.qml \
    qml/control/Logo.qml \
    qml/control/GenericProgressBar.qml \
    qml/control/GenericMessageDialog.qml \
    qml/form/SettingsForm.qml \
    qml/dialog/SettingsDialog.qml \
    qml/control/LabelValueControl.qml \
    qml/control/LabelSpinnerControl.qml \
    qml/control/GenericSpinner.qml \
    qml/control/GenericBackgroundContainer.qml \
    qml/form/ExamplesForm.qml \
    qml/dialog/ExamplesDialog.qml \
    qml/control/GenericDialog.qml \
    qml/dialog/LibrariesDialog.qml \
    qml/form/LibraryManagerForm.qml \
    qml/control/GenericTabButton.qml



HEADERS += \
    editorhighlight.h \
    highlighter.h \
    toolchain/avrcompiler.h \
    toolchain/unocompiler.h \
    directorymanager.h \
    projectmanager.h \
    exception/workingdirectorynull.h \
    exception/invalidprojectdirectory.h \
    thread/compileworker.h \
    thread/uploadworker.h \
    exception/tempdirectorycreationfailed.h \
    exception/workingdirectorynotset.h \
    shprocess.h \
    sdkextractor.h \
    cloudapi/cloud.h \
    cloudapi/cloudresponse.h \
    jsonstorage.h \
    serialport.h \
    editor/editormanager.h \
    editor/editorstyle.h \
    toolchain/toolchain.h \
    toolchain/compiler.h \
    toolchain/roboskopprocess.h \
    toolchain/compileconfiguration.h \
    roboskopenvironment.h \
    toolchain/programmer.h \
    toolchain/programmerconfiguration.h \
    texttemplate/texttemplate.h \
    texttemplate/classheadertemplate.h \
    texttemplate/classcpptemplate.h \
    thread/compileworkerv2.h \
    thread/compileanduploadworkerv2.h \
    exception/compileerror.h \
    parse/functionparser.h \
    parse/functionusageparsed.h \
    generate/func/digitalwritedescgenerator.h \
    generate/func/funcdescgenerator.h \
    parse/parsehelper.h \
    generate/codedescriptiongenerator.h \
    generate/codedescriptioninfo.h \
    generate/func/delaydescgenerator.h \
    generate/func/serialprintdescgenerator.h \
    generate/func/pinmodedescgenerator.h \
    generate/func/serialbegindescgenerator.h \
    parse/compilererrorparser.h \
    generate/func/digitalreaddescgenerator.h \
    generate/func/analogreaddescgenerator.h \
    generate/func/tonedescgeneratoro2.h \
    generate/func/tonedescgeneratoro1.h \
    generate/func/notonedescgenerator.h \
    generate/func/pulseindescgeneratoro1.h \
    generate/func/pulseindescgeneratoro2.h \
    parse/conditionparser.h \
    parse/selectorstrings.h \
    osinfo.h \
    settings/editorsettings.h \
    traverse/projecttraverse.h \
    toolchain/gnugcctoolchain.h \
    toolchain/toolchainV2.h \
    toolchain/runoptions.h \
    options.h \
    toolchain/compileoptions.h \
    traverse/filetraverse.h \
    traverse/traversedfileinfo.h \
    toolchain/cplusplus/gnutoolchain.h \
    toolchain/cplusplus/cpluscompiler.h \
    toolchain/compilerv2.h \
    toolchain/cplusplus/cpluscompileoptions.h \
    environment.h \
    toolchain/cplusplus/cplusenvironment.h \
    rprocess.h \
    arduinoLibManager/librarymanager.h \
    http/roboskopnetworkmanager.h \
    arduinoLibManager/arduinolibdescription.h \
    arduinoLibManager/arduinolibenvironment.h \
    arduinoLibManager/arduinolibdownloader.h \
    zip/zipenvironment.h \
    zip/zipextractor.h \
    zip/zip7zextractor.h \
    exception/environmentvariablenotset.h \
    http/internetaccessibility.h \
    exception/unziperror.h \
    traverse/arduinolibrarytraverse.h

