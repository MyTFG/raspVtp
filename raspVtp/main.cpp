#include <QApplication>
#include <QQmlApplicationEngine>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "mytfgapi.h"

using namespace rapidjson;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QWidget *window = new QWidget;
    window->setWindowTitle("MyTFG VPlan");

    // This is the main Layout to align the plan(s)
    QVBoxLayout *layout = new QVBoxLayout;

    // Call the API
    MytfgApi *api = new MytfgApi;
    std::string params[2] = {"location", "lz"};
    std::string result = api->call(params);

    // Parse result
    rapidjson::Document json;
    json.Parse<0>(result.c_str());

    std::cout << result << std::endl << std::endl;

    if (json["status"].GetInt() == 1) {
        // Parse plan(s)
        const Value& plans = json["plans"];
        if (plans.Size() > 0) {
            // Add Table in ScrollView (?) for every Plan
        } else {
            // No plans found
            std::cout << "No plans received" << std::endl;
        }
    } else {
        std::cout << "Invalid API result" << std::endl;
    }

    QTextEdit *edit = new QTextEdit;
    edit->setText(QString::fromStdString(result));

    layout->addWidget(edit);

    window->setLayout(layout);
    window->setWindowState(Qt::WindowFullScreen);
    window->show();

    return app.exec();
}
