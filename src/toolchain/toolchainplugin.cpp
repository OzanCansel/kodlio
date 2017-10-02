#include "toolchainplugin.h"
#include "compilerv2.h"
#include "toolchainV2.h"
#include "compileoptions.h"
#include "avr/avrcompilerV2.h"
#include "avr/avrtoolchain.h"
#include "avr/avrcompileoptions.h"
#include "runoptions.h"
#include "avr/avrrunoptions.h"
#include "runner.h"
#include "avr/avrrunner.h"
#include "avr/roboskop/roboskoprunner.h"
#include "avr/scratch/s4arunner.h"

void ToolchainPlugin::attach(){
    CompilerV2::registerQmlType();
    ToolchainV2::registerQmlType();
    CompileOptions::registerQmlType();
    Options::registerQmlType();
    RunOptions::registerQmlType();
    Runner::registerQmlType();
    AvrCompilerV2::registerQmlType();
    AvrToolchain::registerQmlType();
    AvrCompileOptions::registerQmlType();
    AvrRunOptions::registerQmlType();
    AvrRunner::registerQmlType();
    RoboskopRunner::registerQmlType();
    S4ARunner::registerQmlType();

}

ToolchainPlugin::ToolchainPlugin()  {

}
