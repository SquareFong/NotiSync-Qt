#include "networkutils.h"


NetworkUtils::NetworkUtils()
{

}

size_t NetworkUtils::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
};

void NetworkUtils::post(string url, string jsonObj){
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        //if url is redirected, so we tell libcurl to follow redirection
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

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
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
        }
        else
            printf(response_string.c_str());

        curl_easy_cleanup(curl);

    }
    curl_global_cleanup();
}

void NetworkUtils::get(string url, string jsonObj){

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // if url is redirected, so we tell libcurl to follow redirection
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_HTTPGET, jsonObj.c_str());

        string response_string;
        string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);


        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
        }
        else {
            printf(response_string.c_str());
        }

        curl_easy_cleanup(curl);

    }
    curl_global_cleanup();
}
