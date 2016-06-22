#include "mytfgapi.h"

#include <iostream>
#include <string>
#include <QString>
#include <QRegExp>
#include <curl/curl.h>

MytfgApi::MytfgApi() {

}

static std::size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

QString MytfgApi::call(std::string *params, size_t count) {
    std::string paramstr = "";

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

    QString str = QString::fromStdString(readBuffer);

    // This will convert the unicode escape chars
    QRegExp rx("(\\\\u[0-9a-fA-F]{4})");
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        str.replace(pos++, 6, QChar(rx.cap(1).right(4).toUShort(0, 16)));
    }

    return str;
}
