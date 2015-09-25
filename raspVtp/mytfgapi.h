#ifndef MYTFGAPI_H
#define MYTFGAPI_H

#include <string>
#include "rapidjson/document.h"

class MytfgApi
{
private:
    //static std::size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
public:
    MytfgApi();
    std::string call(std::string *params);
    // rapidjson::Document parse(std::string json);
};

#endif // MYTFGAPI_H
