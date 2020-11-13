#ifndef CONFIGSMANAGER_H
#define CONFIGSMANAGER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <fstream>
#include <map>
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
    string serverCfgName;
    string clientCfgName;
    map<string, string> serverConfig;

public:
    ConfigsManager();
    map<string, string>& getServerconfig();
    bool readServerConfig();
    bool saveServerConfig();

private:
    string readFile(const string& path);
};

#endif // CONFIGSMANAGER_H
