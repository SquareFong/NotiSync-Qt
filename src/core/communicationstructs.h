#ifndef COMMUNICATIONSTRUCTS_H
#define COMMUNICATIONSTRUCTS_H

#include <string>

using namespace std;

//#include "json.h"
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

class CommunicationStruct {
public:
    string UUID;
    string Time;
    string Type;
    string Data;
    CommunicationStruct(const string& uuid, const string& time,
        const string& type, const string& data)
        : UUID(uuid)
        , Time(time)
        , Type(type)
        , Data(data)
    {
    }
    QJsonObject toJson() const
    {
        QJsonObject j;
        j.insert("UUID", UUID.c_str());
        j.insert("Time", Time.c_str());
        j.insert("Type", Type.c_str());
        j.insert("Data", Data.c_str());
        return j;
    }
    static QJsonObject fromStructToJson(const string& uuid, const string& time,
        const string& type, const string& data)
    {
        QJsonObject j;
        j.insert("UUID", uuid.c_str());
        j.insert("Time", time.c_str());
        j.insert("Type", type.c_str());
        j.insert("Data", data.c_str());
        return j;
    }
};

class Notification {
public:
    string time;
    string packageName;
    string title;
    string content;

public:
    time_t getTime() const
    {
        return atoi(time.c_str());
    }
    void setTime(time_t time)
    {
        char buff[24];
        snprintf(buff, sizeof(buff),
            "%ld", time);
        this->time = string(buff);
    }
};

class Message {
public:
    string number;
    string name;
    string body;
    string date;
    string type; //1表示接收，2表示发送
public:
    time_t getDate() const
    {
        return stol(date);
    }
    void setDate(time_t date)
    {
        char buff[24];
        snprintf(buff, sizeof(buff),
            "%ld", date);
        this->date = string(buff);
    }
    bool isReceive() const
    {
        return type == "1";
    }
    bool isSend() const
    {
        return type == "2";
    }
};

class PhoneDetail {
public:
    string osVersion;
    string model;
    string kernel;
    string uptime;
    string processor;
    string memoryUsage;
    string storageUsage;

    bool fromJson(const QJsonObject& json)
    {
        string subjects[] = { "OsVersion", "Model", "Kernel",
            "Uptime", "Processor",
            "MemoryUsage", "StorageUsage" };
        PhoneDetail tmp;
        string t;
        bool success = true;
        for (auto i : subjects) {
            if (json.find(i.c_str()) == json.end()) {
                success = false;
                break;
            }
            tmp.get(i) = json.value(i.c_str()).toString().toStdString();
        }
        if (success) {
            *this = tmp;
        }
        return success;
    }

    string& get(const string& attribute)
    {
        if (attribute == "OsVersion") {
            return osVersion;
        } else if (attribute == "Model") {
            return model;
        } else if (attribute == "Kernel") {
            return kernel;
        } else if (attribute == "Uptime") {
            return uptime;
        } else if (attribute == "Processor") {
            return processor;
        } else if (attribute == "MemoryUsage") {
            return memoryUsage;
        } else if (attribute == "StorageUsage") {
            return storageUsage;
        } else {
            throw(string("Fail to get attribute ") + attribute + " in PhoneDetail");
        }
    }

    string get(const string& attribute) const
    {
        string r;
        if (attribute == "OsVersion") {
            r = osVersion;
        } else if (attribute == "Model") {
            r = model;
        } else if (attribute == "Kernel") {
            r = kernel;
        } else if (attribute == "Uptime") {
            r = uptime;
        } else if (attribute == "Processor") {
            r = processor;
        } else if (attribute == "MemoryUsage") {
            r = memoryUsage;
        } else if (attribute == "StorageUsage") {
            r = storageUsage;
        }
        return r;
    }
};

#endif // COMMUNICATIONSTRUCTS_H
