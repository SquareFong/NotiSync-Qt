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
    serverCfgName = dir.absolutePath().toStdString() + "/" + serverCfgName;
}

map<string, string>& ConfigsManager::getServerconfig()
{
    return serverConfig;
}

bool ConfigsManager::readServerConfig()
{
    bool success = false;
    string content = readFile(serverCfgName);
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

bool ConfigsManager::saveServerConfig()
{
    bool isSuccess = false;
    QJsonObject jsonObj;
    for (auto& it : serverConfig) {
        jsonObj.insert(it.first.c_str(), it.second.c_str());
    }
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);
    QByteArray jsonBytes = jsonDoc.toJson(QJsonDocument::Indented);

    ofstream outFileStream(serverCfgName);
    if (outFileStream.is_open()) {
        outFileStream << jsonBytes.toStdString();
        outFileStream.close();
        isSuccess = true;
    }

    return isSuccess;
}

string ConfigsManager::readFile(const string& path)
{
    string contents;
    ifstream inputFileStream(path);
    if (inputFileStream.is_open()) {
        int linesize = 1000;
        while (!inputFileStream.eof()) {
            char is[linesize];
            inputFileStream.getline(is, linesize);
            contents.append(is);
        }
        inputFileStream.close();
    }
    return contents;
}
