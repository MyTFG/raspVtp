#include "mytfgapi.h"

#include <iostream>
#include <string>
#include <curl/curl.h>

MytfgApi::MytfgApi() {

}

static std::size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string MytfgApi::call(std::string *params) {
    std::string paramstr = "";

    int count = sizeof(params)/sizeof(params[0]);

    bool first = true;
    for (int i = 0; i < count; i += 2) {
        if (!first) {
            paramstr += "&";
        }
        paramstr += params[i] + "=" + params[i+1];
        first = false;
    }

    std::string url = "https://mytfg.de/ajax_vplan_presentation.x?" + paramstr;

    CURL *curl;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}
