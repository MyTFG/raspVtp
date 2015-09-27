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
    QGridLayout *row;
    QVBoxLayout *layout;
public:
    Plan();
    void nextRow();
    void addCell(std::string content, int colspan = 1, bool isTitle = false);
    QVBoxLayout* getWidget();
};

#endif // PLAN_H
