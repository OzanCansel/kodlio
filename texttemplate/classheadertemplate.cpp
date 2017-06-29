#include "classheadertemplate.h"

ClassHeaderTemplate::ClassHeaderTemplate()
{
    _textTemplate.append("#ifndef __<<defineText>>_H\n")
                    .append("#define __<<defineText>>_H\n\n\n")
            .append("class <<className>>{\n\n")
            .append("public   :\n\n")
            .append("private  :\n\n")
            .append("};\n\n")
            .append("#endif");
}

void ClassHeaderTemplate::setClassName(QString className){
    setValue("defineText" , className.toUpper());
    setValue("className" , className);
}
