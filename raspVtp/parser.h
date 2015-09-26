#ifndef PARSER_H
#define PARSER_H

#include <QVBoxLayout>
#include <string>
#include "jsonCpp/include/json/value.h"
#include "mytfgapi.h"

class Plan
{
private:
    QVBoxLayout *layout;
    MytfgApi *api;
    int timestamp;

    void parse(Json::Value result);
public:
    Plan(QVBoxLayout *layout);
    void update(std::string location);
};

#endif // PARSER_H
