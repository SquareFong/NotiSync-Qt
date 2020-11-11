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
    ServerConfig& getServerconfig();
    bool readServerConfig();

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
