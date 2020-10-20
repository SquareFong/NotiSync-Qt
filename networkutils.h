#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <string>
#include <QByteArray>
#include <curl/curl.h>
using namespace std;

class NetworkUtils
{
    static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);
public:
    NetworkUtils();
    static inline string toBase64(string);
    static inline string fromBase64(string);


    static void post(string url, string jsonObj);

    static void get(string url, string UUID, string Time, string Type);
};


inline string NetworkUtils::toBase64(string utf8){
    QByteArray text(utf8.c_str());
    return string(text.toBase64());
}

inline string NetworkUtils::fromBase64(string base64){
    QByteArray text = QByteArray::fromBase64(base64.c_str());
    return text.data();
}
#endif // NETWORKUTILS_H
