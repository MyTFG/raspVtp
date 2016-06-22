#ifndef PARSER_H
#define PARSER_H

#include <QVBoxLayout>
#include <string>
#include <QApplication>
#include <QScrollArea>
#include "jsonCpp/include/json/value.h"
#include "mytfgapi.h"

class Parser
{
private:    
    // Update content every 5 minutes
    const int updateInterval = 300000;
    const int scrollSpeed = 2;
    const int overScroll = 300;

    QVBoxLayout *layout;
    MytfgApi *api;
    int timestamp;
    int untilUpdate;
    std::string textPt;
    std::string titlePt;
    std::string autoLocation;

    std::vector<QScrollArea*> *scrolls;
    std::vector<int> *scrollPositions;

    void parse(Json::Value plans);
    void remove(QLayout* layout);
    void scroll(int delay);
public slots:
    void loop(int delay);
public:
    Parser(QVBoxLayout *layout);
    void update(std::string location);
    void size(std::string text, std::string title);
};

#endif // PARSER_H
