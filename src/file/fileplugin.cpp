#include "fileplugin.h"
#include "fileinfo.h"
#include "filetree.h"
#include "file.h"

void FilePlugin::attach(){
    FileInfo::registerQmlType();
    FileTree::registerQmlType();
    File::registerQmlType();
}

FilePlugin::FilePlugin()
{

}
