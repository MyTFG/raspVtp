#include "mytfgapi.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QScrollArea>
#include <QTextCodec>
#include <iostream>

#include "jsonCpp/include/json/json.h"
#include "jsonCpp/include/json/value.h"
#include "parser.h"

void scroll(QScrollArea *plans) {

}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QWidget *window = new QWidget;
    window->setWindowTitle("MyTFG VPlan");

    // This is the main Layout to align the plan(s)
    QVBoxLayout *layout = new QVBoxLayout;

    Plan *plan = new Plan(layout);
    plan->update("LZ");

    window->setLayout(layout);
    window->setWindowState(Qt::WindowFullScreen);
    window->show();

    return app.exec();
}
