#ifndef VPLANSCROLLER_H
#define VPLANSCROLLER_H

#include <QObject>
#include <QTimer>
#include "parser.h"

class VplanScroller : public QObject
{
    Q_OBJECT
private:
    Parser *parser;

public:
    explicit VplanScroller(QObject *parent = 0);
    void init(Parser *parser);

signals:

public slots:
    void scroll();

};

#endif // VPLANSCROLLER_H
