#include "parser.h"

#include <iostream>
#include <QScrollArea>
#include <QTableWidget>
#include <QTimer>
#include <string>

#include "jsonCpp/include/json/json.h"
#include "plan.h"

Parser::Parser(QVBoxLayout *layout)
{
    this->layout = layout;
    this->api = new MytfgApi;
    this->timestamp = 0;
    this->untilUpdate = this->updateInterval;
    this->autoLocation = "";
}

void Parser::update(std::string location) {
    this->autoLocation = location;
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
                int lastUpdate = json["update"].asInt();
                if (lastUpdate != this->timestamp) {
                    this->timestamp = lastUpdate;
                    this->parse(plans);
                } else {
                    std::cout << "Plans are already up to date" << std::endl;
                }
            } else {
                // No plans found
                std::cout << "No plans received" << std::endl;
            }
        } else {
            std::cout << "API returned error Code" << std::endl;
            std::cout << result << std::endl;
        }
    }
}

void Parser::remove(QLayout* layout) {
    QLayoutItem* child;
    while(layout->count()!=0)
    {
        child = layout->takeAt(0);
        if(child->layout() != 0)
        {
            remove(child->layout());
        }
        else if(child->widget() != 0)
        {
            delete child->widget();
        }

        delete child;
    }
}

void Parser::parse(Json::Value plans) {
    // Remove all children
    remove(this->layout);
    this->untilUpdate = this->updateInterval;
    this->scrolls = new std::vector<QScrollArea*>();
    this->scrollPositions = new std::vector<int>();

    for (int i = 0; i < plans.size(); i++) {
        QScrollArea *scroll = new QScrollArea;
        scroll->setStyleSheet("QScrollArea {background-color: #FFFFFF; padding: 0; margin: 0}");
        scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

        this->layout->addWidget(scroll);

        Json::Value p = plans[i];
        if (p["status"].asString() != "1") {
            std::cout << "Plan " << i << " has errors " << std::endl;
            continue;
        }

        Plan *plan = new Plan;
        // HEADER
        plan->addCell(p["status_message"].asString(), 4, true);

        plan->nextRow();
        plan->addCell("Letzte Änderung", 1, true);
        plan->addCell(p["changed"].asString(), 3);

        plan->nextRow();
        plan->addCell("Mitteilungen", 1, true);
        std::string msg = "";
        for (int j = 0; j < p["marquee"].size(); j++) {
            if (j > 0) {
                msg += "\n";
            }
            msg += p["marquee"][j].asString();
        }
        plan->addCell(msg, 3);

        plan->nextRow();
        plan->addCell("Stunde", 1, true);
        plan->addCell("Nach Plan", 1, true);
        plan->addCell("Vertretung", 1, true);
        plan->addCell("Bemerkung", 1, true);

        std::string cl = "";
        // Read plan
        if (p["entries"].isArray ()) {
            for (int j = 0; j < p["entries"].size(); j++) {
                Json::Value entry = p["entries"][j];
                if (entry["class"].asString() != cl) {
                    cl = entry["class"].asString();
                    plan->nextRow();
                    plan->addCell(cl, 4, true);
                }
                plan->nextRow();
                plan->addCell(entry["lesson"].asString());
                plan->addCell(entry["plan"].asString());
                plan->addCell(entry["substitution"].asString());
                plan->addCell(entry["comment"].asString());
            }
        } else {
            plan->nextRow();
            plan->addCell("Keine Einträge vorhanden", 4);
        }


        QVBoxLayout *planlayout = plan->getWidget();
        // planlayout->setGeometry(this->layout->geometry());

        QWidget *holderW = new QWidget;
        holderW->setLayout(planlayout);
        holderW->setStyleSheet("QWidget {background-color: #00FF00;}");
        holderW->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        scroll->setWidget(holderW);
        scroll->setWidgetResizable(true);

        scrolls->push_back(scroll);
        scrollPositions->push_back(0);
    }
}

void Parser::scroll(int delay) {
    for (int i = 0; i < scrolls->size(); i++) {
        QScrollArea *s = scrolls->at(i);
        int current = scrollPositions->at(i);


        if (current == 0) {
            current = s->height() - overScroll;
        }

        if (current >= s->widget()->height() + overScroll) {
            current = 0;
        } else {
            current++;
        }

        scrollPositions->at(i) = current;

        s->ensureVisible(0, current, 0, 0);
    }
}

void Parser::loop(int delay) {
    this->untilUpdate -= delay;
    if (this->untilUpdate <= 0) {
        this->update(this->autoLocation);
    }
    this->scroll(delay);
}
