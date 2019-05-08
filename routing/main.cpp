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
#include "requeteapi.h"
#include "myadress.h"
#include "datamanager.h"
#include "card.h"



int main(int argc, char *argv[])
{
    //for the webengineview
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("QtExamples");
    QGuiApplication app(argc, argv);

    //create the datamanger class
    QScopedPointer<DataManager> db(new DataManager);
    db->requestRoads();

    MyAdress* myAdress = new MyAdress();

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
    engine.rootContext()->setContextProperty("maCarte",carte);
    engine.rootContext()->setContextProperty("path",path);

    return app.exec();
}
