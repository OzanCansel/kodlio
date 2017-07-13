#include "toolchainplugin.h"
#include "compilerv2.h"
#include "toolchainV2.h"
#include "compileoptions.h"
#include "avr/avrcompilerV2.h"
#include "avr/avrtoolchain.h"
#include "avr/avrcompileoptions.h"

void ToolchainPlugin::attach(){
    CompilerV2::registerQmlType();
    ToolchainV2::registerQmlType();
    CompileOptions::registerQmlType();
    AvrCompilerV2::registerQmlType();
    AvrToolchain::registerQmlType();
    AvrCompileOptions::registerQmlType();
}

ToolchainPlugin::ToolchainPlugin()  {

}
