#ifndef CONFIGSMANAGER_H
#define CONFIGSMANAGER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <fstream>
#include <set>
#include <string>
using namespace std;

class ServerConfig {
public:
    string protocol;
    string address;
    string port;
    string uuid;
    bool isRun;
};

class ConfigsManager {
    const string path;
    const string serverCfgName;
    const string clientCfgName;
    ServerConfig serverConfig;

public:
    ConfigsManager();
    bool readServerConfig()
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

public:
    static string readFile(const string& path)
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
        }
        return contents;
    }
};

#endif // CONFIGSMANAGER_H
