#include "classcpptemplate.h"

ClassCppTemplate::ClassCppTemplate()
{
    _textTemplate.append("#include \"<<className>>.h\"\n\n");
}

void ClassCppTemplate::setClassName(QString className){
    setValue("className" , className);
}
