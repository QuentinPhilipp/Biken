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
<<<<<<< routing/main.cpp
#include "card.h"


=======
#include "weather.h"
>>>>>>> routing/main.cpp

int main(int argc, char *argv[])
{
    //for the webengineview
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("QtExamples");
    QGuiApplication app(argc, argv);

<<<<<<< routing/main.cpp
    //create the datamanger class
    QScopedPointer<DataManager> db (new DataManager);
    db->requestRoads();
=======
    //create the datamanager class
    QScopedPointer<DataManager> db(new DataManager);
    db->requestRoads(48.434420,-4.640103,5);   //radius in km
>>>>>>> routing/main.cpp

    MyAdress* myAdress = new MyAdress();
    Weather* weather = new Weather();

    //create the Map class
    Card *carte = new Card(1);

    //Initialize the HTML code related to the map
    QtWebEngine::initialize();

    //Recuperation of the working path
    QString path = QDir::currentPath();
    qDebug()<<path;

    //Pour passer du C++ au QML
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    engine.rootContext()->setContextProperty("myAdress",myAdress);      //create a variable myAdress usable in our QML code
    engine.rootContext()->setContextProperty("dataManager", db.data()); //create a variable dataManager usable in our QML code
<<<<<<< routing/main.cpp
    engine.rootContext()->setContextProperty("maCarte",carte);
    engine.rootContext()->setContextProperty("path",path);
=======
    engine.rootContext()->setContextProperty("weather",weather);        //create a variable weather usable in our QML code
>>>>>>> routing/main.cpp

    return app.exec();
}
