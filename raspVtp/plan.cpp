#include "plan.h"

Plan::Plan(bool day, std::string text, std::string title)
{
    this->currentRow = -1;
    this->currentCol = 0;
    this->isToday = day;
    this->textPt = text;
    this->titlePt = title;

    this->layout = new QVBoxLayout;
    this->layout->setMargin(0);
    this->layout->setSpacing(1);

    this->nextRow();
}

void Plan::nextRow() {
    this->currentRow++;
    this->currentCol = 0;

    this->row = new QGridLayout;
    this->row->setSpacing(0);
    this->row->setMargin(1);

    QWidget *frame = new QWidget;
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    if (this->isToday) {
        frame->setStyleSheet("QWidget { background-color: #0081f2;}");
    } else {
        frame->setStyleSheet("QWidget { background-color: #00b31b;}");
    }
    frame->setLayout(this->row);

    this->layout->addWidget(frame, 0, Qt::AlignTop);
}

void Plan::addCell(std::string content, int colspan, bool isTitle) {
    QWidget *frame = new QWidget;
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel *label = new QLabel;
    label->setMargin(0);
    label->setAlignment(Qt::AlignCenter);

    QHBoxLayout *frameLayout = new QHBoxLayout;
    frameLayout->setSpacing(0);
    frameLayout->setMargin(0);
    frame->setLayout(frameLayout);
    if (isTitle) {
        frame->setStyleSheet("QFrame {background-color: #00014a; margin: 0px; padding: 5px; border: 2px solid #AA0000;}");
        label->setStyleSheet("QLabel { color : white; border: 0px; font-size: " + QString::fromStdString(this->titlePt) + "; text-align: center;}");
        label->setText("<b>" + QString::fromStdString(content) + "</b>");
    } else {
        label->setText(QString::fromStdString(content));
        frame->setStyleSheet("QFrame {background-color: #586FC7; font-size: " + QString::fromStdString(this->textPt) + "; margin: 0px; padding: 5px;}");
        label->setStyleSheet("QLabel { color : white; border: 0px; font-weight: bold;}");
    }
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    frameLayout->addWidget(label);


    this->row->addWidget(frame, 0, this->currentCol);
    this->row->setColumnStretch(this->currentCol, colspan);
    this->currentCol++;
}

QVBoxLayout* Plan::getWidget() {
    return this->layout;
}
