#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QTime>
#include <QUrl>
#include <QtWebEngine>

#include "node.h"
#include "way.h"
#include "requeteapi.h"
#include "myadress.h"
#include "datamanager.h"

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

    //Initialize the HTML code related to the map
    QtWebEngine::initialize();

    //Pour passer du C++ au QML
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;    
    engine.rootContext()->setContextProperty("myAdress",myAdress);      //create a variable myAdress usable in our QML code
    engine.rootContext()->setContextProperty("dataManager", db.data()); //create a variable dataManager usable in our QML code

    return app.exec();
}
