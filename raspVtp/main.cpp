#include "mytfgapi.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QScrollArea>
#include <QTextCodec>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <QTimer>

#include "jsonCpp/include/json/json.h"
#include "jsonCpp/include/json/value.h"
#include "parser.h"
#include "vplanscroller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    std::string location;
    std::cout << argc << std::endl;
    if (argc < 2) {
        location = "LZ";
    } else {
        location = argv[1];
    }

    QApplication::setOverrideCursor(Qt::BlankCursor);

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    // This is the main Layout to align the plan(s)
    QVBoxLayout *layout = new QVBoxLayout;

    QWidget *window = new QWidget;
    window->setWindowTitle("MyTFG VPlan");
    window->setLayout(layout);
    window->setWindowState(Qt::WindowFullScreen);
    window->setStyleSheet("QWidget {background-color: #394689;}");
    window->show();


    Parser *plan = new Parser(layout);;
    plan->update(location);
    //plan->startLoop();

    VplanScroller *scroller = new VplanScroller;
    scroller->init(plan);

    return app.exec();
}

