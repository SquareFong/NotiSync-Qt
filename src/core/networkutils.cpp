#include "src/core/networkutils.h"

NetworkUtils::NetworkUtils()
{
}

size_t NetworkUtils::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
};

void NetworkUtils::post(string url, string jsonObj)
{
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {
        if (url[url.length() - 1] != '/') {
            url += "/";
        }
        url += "send";
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        //if url is redirected, so we tell libcurl to follow redirection
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonObj.length());

        string response_string;
        string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        //Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        } else
            printf(response_string.c_str());

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void NetworkUtils::get(string url,
    string UUID, string Time, string Type, string& response)
{

    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {
        if (url[url.length() - 1] != '/') {
            url += "/";
        }
        url += "get";
        url += (string("?") + "UUID=" + UUID + "&Time=" + Time + "&Type=" + Type);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // if url is redirected, so we tell libcurl to follow redirection
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        string response_string;
        string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        } else {
            printf("%s\n", response_string.c_str());

            response = response_string;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}
