#ifndef MYTFGAPI_H
#define MYTFGAPI_H

#include <string>
#include <QString>

class MytfgApi
{
private:
    //static std::size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
public:
    MytfgApi();
    QString call(std::string *params, size_t count);
};

#endif // MYTFGAPI_H
