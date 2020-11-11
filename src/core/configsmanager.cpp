#include "configsmanager.h"
#include <dirent.h>
//#include<sys/types.h>
#include <sys/stat.h>

ConfigsManager::ConfigsManager()
    : path("~/.config/NotiSyncQt/")
    , serverCfgName("server.json")
    , clientCfgName("NotiSyncQt.json")
{
    if (opendir(path.c_str()) == NULL) //如果文件夹不存在
    {
        int ret = mkdir(path.c_str(), 0660);
        if (ret != 0) {
            throw "Fail to local config files";
        }
    }
}
