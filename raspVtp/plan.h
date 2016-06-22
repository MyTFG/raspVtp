#ifndef PLAN_H
#define PLAN_H

#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QFrame>

class Plan {
private:
    int currentRow;
    int currentCol;
    bool isToday;
    QGridLayout *row;
    QVBoxLayout *layout;
    std::string textPt;
    std::string titlePt;
public:
    Plan(bool day, std::string text, std::string title);
    void nextRow();
    void addCell(std::string content, int colspan = 1, bool isTitle = false);
    QVBoxLayout* getWidget();
};

#endif // PLAN_H
