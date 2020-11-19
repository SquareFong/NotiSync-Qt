#ifndef NOTISYNCCLIENT_H
#define NOTISYNCCLIENT_H

#include <algorithm>
#include <set>
#include <vector>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
using namespace std;

#include "communicationstructs.h"
#include "networkutils.h"

class NotiSyncClient {
private:
    string protocol;
    string server;
    string port;
    string url;
    string uuid;

    bool isRun;
    PhoneDetail phoneDetail;
    vector<Notification> notifications;
    vector<Message> messages;
    time_t lastUpdate;

    vector<Message> digest;
    vector<Message>::iterator findDigestByNumber(const string& number)
    {
        vector<Message>::iterator it = digest.begin();
        while (it != digest.end()) {
            if ((*it).number == number) {
                return it;
            }
            ++it;
        }
        return it;
    }
    static inline bool greaterThanByTime(Message& lhs, Message& rhs)
    {
        return lhs.getDate() > rhs.getDate();
    }

    inline string getTime()
    {
        time_t t;
        time(&t);
        return std::to_string(t);
    }

public:
    NotiSyncClient();
    inline void setRunable(bool run)
    {
        this->isRun = run;
    }
    inline bool run()
    {
        return isRun;
    }
    inline void setServer(string protocol, string server, string port)
    {
        this->protocol = protocol;
        this->server = server;
        this->port = port;
        url = this->protocol + "://" + this->server + ":" + this->port;
    }

    inline void setUUID(string uuid)
    {
        this->uuid = uuid;
    }

    //Network functions
    void* fetchPhoneDetail();
    void* fetchNotifications();
    void* fetchMessages();
    void* sendNewMessage(Message message);

    //用于fetchMessages内调用
    void refreshMessageDigestList(const vector<Message>& newMessages)
    {
        auto it = newMessages.begin();
        //bool needSort = false;
        for (; it != newMessages.end(); ++it) {
            auto tmp = findDigestByNumber((*it).number);
            if ((tmp != digest.end())) {
                if ((*tmp).getDate() < (*it).getDate())
                    (*tmp) = (*it);
            } else {
                digest.push_back(*it);
            }
        }
        sort(digest.begin(), digest.end(), &greaterThanByTime);
    }

    //UI获取信息时使用
    PhoneDetail getPhoneDetail() const;
    vector<Notification> getNotifications() const;
    void clearNotifications()
    {
        notifications.clear();
    }
    vector<Message> getMessageDigest() const;
    vector<Message> getSingleChat(string number) const;
};

#endif // NOTISYNCCLIENT_H
