#include "configsmanager.h"
#include <dirent.h>
//#include<sys/types.h>
#include <sys/stat.h>

ConfigsManager::ConfigsManager()
    : path("~/.config/NotiSyncQt/")
    , serverCfgName("server.json")
    , clientCfgName("NotiSyncQt.json")
{
    if (opendir(path.c_str()) == 0) //如果文件夹不存在
        mkdir(path.c_str(), 0660);
}
