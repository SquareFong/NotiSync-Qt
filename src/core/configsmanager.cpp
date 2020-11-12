#include "configsmanager.h"
#include <dirent.h>
//#include<sys/types.h>
#include <QDir>
#include <sys/stat.h>

ConfigsManager::ConfigsManager()
    : path(".config/NotiSyncQt/")
    , serverCfgName("server.json")
    , clientCfgName("NotiSyncQt.json")
{
    QDir dir(QDir::homePath() + "/" + path.c_str());
    if (!dir.exists()) //如果文件夹不存在
    {
        if (!dir.mkdir(dir.absolutePath())) {
            throw "Fail to make directories for config files";
        }
    }
}

map<string, string>& ConfigsManager::getServerconfig()
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
            map<string, string> sc;
            for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
                string k = it.key().toStdString();
                string v = it.value().toString().toStdString();
                if (properties.find(k) == properties.end()) {
                    isLegal = false;
                    break;
                }
                sc.insert(pair<string, string>(it.key().toStdString(), it.value().toString().toStdString()));
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
