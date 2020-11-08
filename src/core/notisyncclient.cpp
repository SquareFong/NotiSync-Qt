#include "notisyncclient.h"

#include <QStringList>
#include <QtCore/QJsonParseError>

NotiSyncClient::NotiSyncClient() { }

void NotiSyncClient::fetchPhoneDetail()
{
    string output;
    NetworkUtils::get(url, uuid, getTime(), "Detail", output);

    QJsonParseError jsonPareseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(
        output.c_str(), &jsonPareseError); //字符串格式化为JSON

    if (jsonPareseError.error != QJsonParseError::NoError) {
        qDebug() << "NotiSyncClient::fetchPhoneDetail():\t JSON格式错误";
        return;
    } else {
        QJsonObject jsonObj = jsonDoc.object();
        QJsonValue jsonDataVal = jsonObj.value("Data");
        string dataRaw = NetworkUtils::fromBase64(jsonDataVal.toString().toStdString());
        QJsonDocument detailDoc = QJsonDocument::fromJson(dataRaw.c_str(), &jsonPareseError);
        if (jsonPareseError.error == QJsonParseError::NoError) {
            QJsonObject detailJson = detailDoc.object();
            if (!phoneDetail.fromJson(detailJson)) {
                printf("%s \n In function %sdetailJson %s",
                    "***Error***",
                    "NotiSyncClient::fetchPhoneDetail()",
                    "fail to set phoneDetail, an attribute may be null str");
            }
        }
    }
}

QStringList
fromStrToQStringList(const string& str)
{
    QStringList l;
    if (str[0] != '[' || str[str.length() - 1] != ']') {
        printf("notisyncclient.cpp\tfromStrToQStringList(const string& str): "
               "Unsupport json string: \n%s\n",
            str.c_str());
    } else {
        int startP = 0;
        int endP = 0;
        int counter = 0;
        for (unsigned i = 1; i < str.length(); ++i) {
            if (str[i] == '{') {
                if (counter == 0)
                    startP = i;
                ++counter;
            } else if (str[i] == '}') {
                --counter;
                if (counter == 0) {
                    endP = i;
                    if (startP < endP) {
                        string subStr = str.substr(startP, endP - startP + 1);
                        l.append(subStr.c_str());
                    }

                    startP = 0;
                    endP = 0;
                }
            }
        }
    }
    return l;
}

void NotiSyncClient::fetchNotifications()
{
    string output;
    NetworkUtils::get(url, uuid, getTime(), "Notifications", output);
    QJsonParseError jsonPareseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(
        output.c_str(), &jsonPareseError); //字符串格式化为JSON

    if (jsonPareseError.error != QJsonParseError::NoError) {
        qDebug() << "NotiSyncClient::fetchPhoneDetail():\t JSON格式错误";
        return;
    } else {
        QJsonObject jsonObj = jsonDoc.object();
        QJsonValue jsonDataVal = jsonObj.value("Data");
        string dataRaw = NetworkUtils::fromBase64(jsonDataVal.toString().toStdString());
        QStringList dataList = fromStrToQStringList(dataRaw);
        QJsonArray jsonArr = QJsonArray::fromStringList(dataList);
        if (!jsonArr.empty()) {
            QJsonArray notisArray = jsonDoc.array();
            for (auto it : jsonArr) {
                QJsonParseError e;
                QJsonDocument d = QJsonDocument::fromJson(it.toString().toStdString().c_str(), &e);
                if (e.error == QJsonParseError::NoError) {
                    QJsonObject o = d.object();
                    Notification n;
                    n.time = o.value("Time").toString().toStdString();
                    n.packageName = o.value("PackageName").toString().toStdString();
                    n.title = o.value("Title").toString().toStdString();
                    n.content = o.value("Content").toString().toStdString();
                    notifications.push_back(move(n));
                }
            }
        }
    }
}

void NotiSyncClient::fetchMessages()
{
    string output;
    NetworkUtils::get(url, uuid, getTime(), "Messages", output);
    QJsonParseError jsonPareseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(
        output.c_str(), &jsonPareseError); //字符串格式化为JSON

    if (jsonPareseError.error != QJsonParseError::NoError) {
        qDebug() << "NotiSyncClient::fetchPhoneDetail():\t JSON格式错误";
        return;
    } else {
        QJsonObject jsonObj = jsonDoc.object();
        QJsonValue jsonDataVal = jsonObj.value("Data");
        string dataRaw = NetworkUtils::fromBase64(jsonDataVal.toString().toStdString());
        QStringList dataList = fromStrToQStringList(dataRaw);
        QJsonArray jsonArr = QJsonArray::fromStringList(dataList);
        if (!jsonArr.empty()) {
            QJsonArray notisArray = jsonDoc.array();
            vector<Message> newMessages;
            for (auto it : jsonArr) {
                QJsonParseError e;
                QJsonDocument d = QJsonDocument::fromJson(it.toString().toStdString().c_str(), &e);
                if (e.error == QJsonParseError::NoError) {
                    QJsonObject o = d.object();
                    Message n;
                    n.number = o.value("Number").toString().toStdString();
                    n.name = o.value("Name").toString().toStdString();
                    n.body = o.value("Body").toString().toStdString();
                    n.date = o.value("Date").toString().toStdString();
                    n.type = o.value("Type").toString().toStdString();
                    newMessages.push_back(n);
                    messages.push_back(move(n));
                }
            }
            refreshMessageDigestList(newMessages);
        }
    }
}

void NotiSyncClient::sendNewMessage(Message message)
{
    QJsonObject dataObj;
    dataObj.insert("Number", message.number.c_str());
    dataObj.insert("Name", message.name.c_str());
    dataObj.insert("Body", message.body.c_str());
    dataObj.insert("Date", message.date.c_str());
    dataObj.insert("Type", message.type.c_str());
    QJsonDocument dataDoc;
    dataDoc.setObject(dataObj);
    QByteArray dataStr = dataDoc.toJson(QJsonDocument::Compact);
    string dataBase64 = NetworkUtils::toBase64(dataStr.toStdString());

    QJsonObject jsonObj;
    jsonObj.insert("UUID", uuid.c_str());
    jsonObj.insert("Time", getTime().c_str());
    jsonObj.insert("Type", "newSMS");
    jsonObj.insert("Data", dataBase64.c_str());
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);
    string jsonStr = jsonDoc.toJson(QJsonDocument::Compact).toStdString();

    NetworkUtils::post(url, jsonStr);
    messages.push_back(message);
    refreshMessageDigestList(vector<Message>() = { message });
}

PhoneDetail NotiSyncClient::getPhoneDetail() const
{
    return phoneDetail;
}

vector<Notification> NotiSyncClient::getNotifications() const
{
    return notifications;
}

vector<Message> NotiSyncClient::getMessageDigest() const
{
    return digest;
}

vector<Message> NotiSyncClient::getSingleChat(string number) const
{
    vector<Message> singleChat;
    for (auto it = messages.begin(); it != messages.end(); ++it) {
        if ((*it).number == number) {
            singleChat.push_back(*it);
        }
    }
    return singleChat;
}
