#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QTime>

#include "node.h"
#include "way.h"
#include "requeteapi.h"
#include "roadsdata.h"
#include "myadress.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //make a request to get all the roads around a coordinate
    RequeteAPI *requeteRoads = new RequeteAPI();
    QString radius = "100000"; //radius in meters. Do not set the radius too high (~200km max), otherwise it will exceed the api's capacity.

    qDebug() << "\n\n TEST CHRONO rayon = 100km\n";
    //chrono time
    qDebug() << "\n TIME Before Request : " << QTime::currentTime().toString() << "\n";
    QJsonObject allRoads = requeteRoads->getAllRoadsAroundThePoint("48.434420","-4.640103",radius);

    qDebug() << "\n TIME After Request : " << QTime::currentTime().toString() << "\n";

    //create the datamanger class
    //DataManager *db = new DataManager();
    QScopedPointer<DataManager> db(new DataManager);

    /*RoadsData roadsData = RoadsData();
    roadsData.generateWaysAndNodes(allRoads);
    vector<Way> wayVector = roadsData.getWayVector();*/

    QScopedPointer<RoadsData> roadsData(new RoadsData);
    roadsData->generateWaysAndNodes(allRoads, *db);

    qDebug() << "\n TIME After Database creation : " << QTime::currentTime().toString() << "\n";
    qDebug() << QCoreApplication::libraryPaths();

    vector<Way> wayVector = roadsData->getWayVector();

    //Verification
    qDebug() << "\nAmount of ways: " << wayVector.size() ;  //shows the amount of Way objects


    //test sur la base de données
    qDebug() << "List of the node of Road id 105576006";
        std::vector<QVariant> nodes = db->requestNodesFromRoad(105576006);
        for (auto elem : nodes)
        {
            qDebug() << elem.toString();
        }
        qDebug() << "Latitude and longitue of the node id 1215777654";
        QVariant lat,lon;
        std::tie(lat,lon) = db->requestLatLonFromNodes(1215777654);
        qDebug() << "Latitude : "<<lat.toString()<<" | Longitude : "<<lon.toString();

    qDebug() << "\n TIME End : " << QTime::currentTime().toString() << "\n";

    //Pour passer du C++ au QML
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    MyAdress* myAdress = new MyAdress();
    engine.rootContext()->setContextProperty("myAdress",myAdress);
    engine.rootContext()->setContextProperty("roadsData", roadsData.data()); //créer une variable roadsData utilisable dans notre QML

    return app.exec();
}
