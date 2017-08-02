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
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\drivers $${OUT_PWD_WIN}\\debug\\drivers /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\tools $${OUT_PWD_WIN}\\release\\tools /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\template $${OUT_PWD_WIN}\\release\\template /e

                message(robocopy $${PWD_WIN}\\extFiles\\windows\\drivers $${OUT_PWD_WIN}\\debug\\drivers /e)

        } else {
                PWD_WIN = $${PWD}
                PWD_WIN ~= s,/,\\,g
                OUT_PWD_WIN = $${OUT_PWD}
                OUT_PWD_WIN ~= s,/,\\,g
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\* $${OUT_PWD_WIN}\\release\\ /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\sdk $${OUT_PWD_WIN}\\release\\sdk /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\drivers $${OUT_PWD_WIN}\\release\\drivers /e &
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\tools $${OUT_PWD_WIN}\\release\\tools /e
                QMAKE_POST_LINK  += robocopy $${PWD_WIN}\\extFiles\\windows\\tools $${OUT_PWD_WIN}\\release\\template /e

        }
}

unix    {
    QMAKE_POST_LINK     +=  cp -r $${PWD}/extFiles/linux/* $${OUT_PWD}
}

SOURCES += main.cpp \
    toolchain/avrcompiler.cpp \
    toolchain/unocompiler.cpp \
    directorymanager.cpp \
    exception/workingdirectorynull.cpp \
    exception/invalidprojectdirectory.cpp \
    exception/tempdirectorycreationfailed.cpp \
    exception/workingdirectorynotset.cpp \
    shprocess.cpp \
    sdkextractor.cpp \
    cloudapi/cloud.cpp \
    cloudapi/cloudresponse.cpp \
    jsonstorage.cpp \
    serial/serialport.cpp \
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
    traverse/arduinolibrarytraverse.cpp \
    toolchain/avrtoolchainenvironment.cpp \
    editor/documentcontent.cpp \
    file/filetree.cpp \
    traverse/arduinoprojecttraverse.cpp \
    project/projectwatcher.cpp \
    project/arduino/arduinoprojectwatcher.cpp \
    file/fileinfo.cpp \
    toolchain/avr/avrtoolchain.cpp \
    parse/includedheaders.cpp \
    exception/filecouldnotopen.cpp \
    toolchain/avr/avrcompilerV2.cpp \
    exception/boardnotspecified.cpp \
    exception/incompatibleextension.cpp \
    toolchain/avr/board/arduinoboard.cpp \
    toolchain/avr/board/unoboard.cpp \
    toolchain/avr/board/boardfactory.cpp \
    toolchain/avr/avrenvironment.cpp \
    file/fileutil.cpp \
    exception/filenotexists.cpp \
    collection/stringlistutil.cpp \
    toolchain/avr/avrcompileoptions.cpp \
    toolchain/toolchainplugin.cpp \
    highlight/arduinohighlightitem.cpp \
    highlight/arduinohighlighter.cpp \
    highlight/highlightitem.cpp \
    highlight/highlightplugin.cpp \
    editor/editorplugin.cpp \
    arduinoLibManager/librarymanagerplugin.cpp \
    project/projectplugin.cpp \
    http/httpplugin.cpp \
    traverse/traverseplugin.cpp \
    file/fileplugin.cpp \
    eventcontext.cpp \
    thread/avr/avrtoolchainthread.cpp \
    thread/threadplugin.cpp \
    thread/avr/compileworkerV2.cpp \
    toolchain/runner.cpp \
    toolchain/avr/avrrunner.cpp \
    exception/optionkeynotexists.cpp \
    exception/runerror.cpp \
    toolchain/avr/avrrunoptions.cpp \
    thread/avr/runworker.cpp \
    thread/avr/avrtoolchainworker.cpp \
    serial/serialoptions.cpp \
    serial/serialplugin.cpp \
    serial/serialportscanner.cpp \
    exception/portnamenotspecified.cpp \
    parse/errorparser.cpp \
    parse/avr/avrerrorparser.cpp \
    parse/parserplugin.cpp \
    file/file.cpp \
    editor/documentstyle.cpp \
    editor/editorsettings.cpp \
    project/projectmanager.cpp \
    project/projectoptions.cpp \
    project/arduino/arduinoprojectmanager.cpp \
    texttemplate/arduino/arduinomainfiletemplate.cpp \
    texttemplate/genericfiletemplate.cpp \
    parse/kodlioasistant.cpp \
    editor/linenumber.cpp \
    parse/headerparser.cpp \
    cloudapi/cloudplugin.cpp \
    thread/cloud/cloudthread.cpp \
    thread/cloud/cloudworker.cpp

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
    qml/Global.qml \
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
    qml/control/GenericTabButton.qml \
    qml/editor/Document.qml \
    qml/editor/ArduinoDocument.qml \
    qml/editor/LineNumerator.qml \
    qml/editor/FlickableTextArea.qml \
    qml/project/ArduinoProject.qml \
    qml/project/Project.qml \
    qml/control/DocumentHeader.qml \
    qml/singleton/FontCollection.qml \
    qml/editor/EmptyDocument.qml \
    qml/project/DocumentNumerator.qml \
    qml/singleton/EventLabels.qml \
    qml/singleton/SerialOption.qml \
    qml/animation/RunAnimation.qml \
    qml/animation/ShowAndFadeAnimation.qml \
    qml/dialog/CreateFileDialog.qml \
    qml/form/CreateFileForm.qml \
    qml/project/ContextMenu.qml \
    qml/project/GenericEditorMenu.qml \
    qml/control/ToolImageButton.qml \
    qml/control/CloudMenu.qml \
    qml/control/GenericMenuItem.qml \
    qml/control/GenericMenu.qml


HEADERS += \
    toolchain/avrcompiler.h \
    toolchain/unocompiler.h \
    directorymanager.h \
    exception/workingdirectorynull.h \
    exception/invalidprojectdirectory.h \
    exception/tempdirectorycreationfailed.h \
    exception/workingdirectorynotset.h \
    shprocess.h \
    sdkextractor.h \
    cloudapi/cloud.h \
    cloudapi/cloudresponse.h \
    jsonstorage.h \
    serial/serialport.h \
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
    traverse/arduinolibrarytraverse.h \
    toolchain/avrtoolchainenvironment.h \
    editor/documentcontent.h \
    file/filetree.h \
    traverse/arduinoprojecttraverse.h \
    project/projectwatcher.h \
    project/arduino/arduinoprojectwatcher.h \
    file/fileinfo.h \
    toolchain/avr/avrtoolchain.h \
    parse/includedheaders.h \
    exception/filecouldnotopen.h \
    toolchain/avr/avrcompilerV2.h \
    exception/boardnotspecified.h \
    exception/incompatibleextension.h \
    toolchain/avr/board/arduinoboard.h \
    toolchain/avr/board/unoboard.h \
    toolchain/avr/board/boardfactory.h \
    toolchain/avr/avrenvironment.h \
    file/fileutil.h \
    exception/filenotexists.h \
    collection/stringlistutil.h \
    toolchain/avr/avrcompileoptions.h \
    toolchain/toolchainplugin.h \
    highlight/arduinohighlightitem.h \
    highlight/arduinohighlighter.h \
    highlight/highlightitem.h \
    highlight/highlightplugin.h \
    editor/editorplugin.h \
    arduinoLibManager/librarymanagerplugin.h \
    project/projectplugin.h \
    http/httpplugin.h \
    traverse/traverseplugin.h \
    file/fileplugin.h \
    eventcontext.h \
    thread/avr/avrtoolchainthread.h \
    thread/threadplugin.h \
    thread/avr/compileworkerV2.h \
    toolchain/runner.h \
    toolchain/avr/avrrunner.h \
    exception/optionkeynotexists.h \
    exception/runerror.h \
    toolchain/avr/avrrunoptions.h \
    thread/avr/runworker.h \
    thread/avr/avrtoolchainworker.h \
    serial/serialoptions.h \
    serial/serialplugin.h \
    serial/serialportscanner.h \
    exception/portnamenotspecified.h \
    parse/errorparser.h \
    parse/avr/avrerrorparser.h \
    parse/parserplugin.h \
    file/file.h \
    editor/documentstyle.h \
    editor/editorsettings.h \
    project/projectmanager.h \
    project/projectoptions.h \
    project/arduino/arduinoprojectmanager.h \
    texttemplate/arduino/arduinomainfiletemplate.h \
    texttemplate/genericfiletemplate.h \
    parse/kodlioasistant.h \
    editor/linenumber.h \
    parse/headerparser.h \
    cloudapi/cloudplugin.h \
    thread/cloud/cloudthread.h \
    thread/cloud/cloudworker.h

