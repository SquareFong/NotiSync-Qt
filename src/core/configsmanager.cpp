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

ServerConfig& ConfigsManager::getServerconfig()
{
    return serverConfig;
}

bool ConfigsManager::readServerConfig()
{
    bool success = false;
    string content = readFile(path + serverCfgName);
    if (!content.empty()) {
        QJsonParseError jsonPareseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(
            content.c_str(), &jsonPareseError);
        if (jsonPareseError.error != QJsonParseError::NoError) {
            qDebug() << "ConfigsManager::readServerConfig():\t JSON格式错误";
        } else {
            set<string> properties = { "protocol", "address", "port", "uuid", "isRun" };
            QJsonObject jsonObj = jsonDoc.object();
            bool isLegal = true;
            ServerConfig sc;
            for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
                if (properties.find(it.key().toStdString()) == properties.end()) {
                    isLegal = false;
                    break;
                }
                if (it.key().toStdString() == "protocol") {
                    sc.protocol = it.value().toString().toStdString();
                } else if (it.key().toStdString() == "address") {
                    sc.address = it.value().toString().toStdString();
                } else if (it.key().toStdString() == "port") {
                    sc.port = it.value().toString().toStdString();
                } else if (it.key().toStdString() == "uuid") {
                    sc.uuid = it.value().toString().toStdString();
                } else if (it.key().toStdString() == "isRun") {
                    sc.isRun = it.value().toBool();
                } else {
                    isLegal = false;
                    break;
                }
            }
            if (isLegal) {
                success = true;
                serverConfig = sc;
            } else {
                printf("ConfigsManager::readServerConfig():\t JSON属性有错误");
            }
        }
    }
    return success;
}
