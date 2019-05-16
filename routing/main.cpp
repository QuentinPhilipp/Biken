#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QTime>
#include <QUrl>
#include <QtWebEngine>
#include <QString>

#include "node.h"
#include "way.h"
#include "myadress.h"
#include "datamanager.h"
#include "card.h"
#include "weather.h"

int main(int argc, char *argv[])
{
    //for the webengineview
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("QtExamples");
    QGuiApplication app(argc, argv);

    //create the datamanager class
    QScopedPointer<DataManager> db(new DataManager);
    db->requestRoads(48.434420,-4.640103,50);   //radius in km
    //db->requestRoads(48.118463,-1.414886,15);   //radius in km

//    std::vector<Node *> nodes = db->getAllNodes();
//    for (auto elem : nodes) {
//        qDebug() << elem;
//    }


    MyAdress* myAdress = new MyAdress();
    Weather* weather = new Weather();

    //create the Map class
    Card *carte = new Card(1);

    //Initialize the HTML code related to the map
    QtWebEngine::initialize();

    //Recuperation of the working path

    QDir dir = QDir::currentPath();   //return path in the build folder
    dir.cdUp();                         //project folder
    dir.cd("routing/Data");                  //routing folder
    QString path = dir.path();

    //Pour passer du C++ au QML
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    engine.rootContext()->setContextProperty("myAdress",myAdress);      //create a variable myAdress usable in our QML code
    engine.rootContext()->setContextProperty("dataManager", db.data()); //create a variable dataManager usable in our QML code
    engine.rootContext()->setContextProperty("maCarte",carte);
    engine.rootContext()->setContextProperty("path",path);
    engine.rootContext()->setContextProperty("weather",weather);        //create a variable weather usable in our QML code


    return app.exec();
}
