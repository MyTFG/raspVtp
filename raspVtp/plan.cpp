#include "plan.h"

Plan::Plan()
{
    this->currentRow = -1;
    this->currentCol = 0;

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
    this->row->setMargin(0);
    QWidget *frame = new QWidget;
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    frame->setStyleSheet("QWidget { background-color: #FFFFFF;}");
    frame->setLayout(this->row);

    this->layout->addWidget(frame);
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
        label->setStyleSheet("QLabel { color : white; border: 0px; font-size: 15pt; text-align: center;}");
        label->setText("<b>" + QString::fromStdString(content) + "</b>");
    } else {
        label->setText(QString::fromStdString(content));
        frame->setStyleSheet("QFrame {background-color: #586FC7; font-size: 14pt; margin: 0px; padding: 5px;}");
        label->setStyleSheet("QLabel { color : white; border: 0px;}");
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
