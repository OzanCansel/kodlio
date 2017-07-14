#include "fileplugin.h"
#include "fileinfo.h"
#include "filetree.h"

void FilePlugin::attach(){
    FileInfo::registerQmlType();
    FileTree::registerQmlType();
}

FilePlugin::FilePlugin()
{

}
