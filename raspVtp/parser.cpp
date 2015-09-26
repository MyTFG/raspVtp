#include "parser.h"

#include <iostream>
#include <QScrollArea>

#include "jsonCpp/include/json/json.h"

Plan::Plan(QVBoxLayout *layout)
{
    this->layout = layout;
    this->api = new MytfgApi;
    this->timestamp = 0;
}

void Plan::update(std::string location) {
    // Call the API
    std::string params[2] = {"location", location};
    //std::string result = api->call(params);
    QString qstring = api->call(params);
    std::string result = qstring.toStdString();

    // Parse result
    Json::Value json;
    Json::Reader reader;

    if (!reader.parse(result, json)) {
        std::cout << "Error parsing JSON" << std::endl;
    } else {
        if (json.get("status", "0").asString() == "1") {
            std::cout << "API result ok" << std::endl;
            // Parse plan(s)
            Json::Value plans = json["plans"];
            if (plans.size() > 0) {
                // Check if received plan is newer than currently displayed plan

                // Add Table in ScrollView (?) for every Plan
                std::cout << "Number of Plans: " << plans.size() << std::endl;

                for (int i = 0; i < plans.size(); ++i) {
                    QScrollArea *scroll = new QScrollArea;
                    Json::Value plan = plans[i];
                }

            } else {
                // No plans found
                std::cout << "No plans received" << std::endl;
            }
        } else {
            std::cout << "API returned error Code" << std::endl;
        }
    }
}
