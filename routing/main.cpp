#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QTime>


#include "node.h"
#include "way.h"
#include "myadress.h"
#include "datamanager.h"
#include "weather.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);



    //create the datamanager class
    DataManager db(new DataManager);
    db.requestRoads(48.434420,-4.640103,5);   //radius in km

    MyAdress* myAdress = new MyAdress();
    QStringList listDataToDownload = QStringList() << "29" << "56" << "57";
    listDataToDownload = db.isAlreadyIn(listDataToDownload);

    if(!listDataToDownload.isEmpty()){
        myAdress->downloadDataAround(listDataToDownload);               // download the data you didn't have
    }
    Weather* weather = new Weather();

    //Pour passer du C++ au QML
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;
//    engine.rootContext()->setContextProperty("myAdress",myAdress);      //create a variable myAdress usable in our QML code
//    engine.rootContext()->setContextProperty("dataManager", db.data()); //create a variable dataManager usable in our QML code
//    engine.rootContext()->setContextProperty("weather",weather);        //create a variable weather usable in our QML code

    return app.exec();
}
