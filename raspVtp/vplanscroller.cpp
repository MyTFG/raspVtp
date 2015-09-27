#include "vplanscroller.h"

VplanScroller::VplanScroller(QObject *parent) :
    QObject(parent)
{

}

void VplanScroller::init(Parser *parser) {
    this->parser = parser;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(scroll()));
    timer->start(15);
}

void VplanScroller::scroll() {
    this->parser->loop(15);
}
