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
    QString radius = "1000"; //radius in meters. Do not set the radius too high (~200km max), otherwise it will exceed the api's capacity.

    qDebug() << "\n\n TEST CHRONO rayon = 100km\n";


    //chrono time
    QDateTime beforeRequestTime = QDateTime::currentDateTime();
    qDebug() << "\n TIME Before Request : " << beforeRequestTime.toString() << "\n";

    //Request
    QJsonObject allRoads = requeteRoads->getAllRoadsAroundThePoint("48.434420","-4.640103",radius);


    //CHRONO
    QDateTime afterRequestTime = QDateTime::currentDateTime();
    qDebug() << "\n TIME After Request : " << afterRequestTime.toString() << "\n";


    //create the datamanger class
    //DataManager *db = new DataManager();
    QScopedPointer<DataManager> db(new DataManager);



    QScopedPointer<RoadsData> roadsData(new RoadsData);
    roadsData->generateWaysAndNodes(allRoads, *db);


    //CHRONO
    QDateTime afterDatabaseTime = QDateTime::currentDateTime();
    qDebug() << "\n TIME After Database creation : " << afterDatabaseTime.toString() << "\n";


    //Verification
    //test sur la base de données
    qDebug() << "\nVérification\n";

    // Test requestNodesFromRoad()
    //qDebug() << "Test requestNodesFromRoads";
//    std::vector<Node> nodes = db->requestNodesFromRoad(105576006);
//    for (auto &elem : nodes)
//    {
//        qDebug() << "Node n°"<< elem.getId()<<"| Latitude :" <<QString::number(elem.getLatitude(),'f',8)<<"| Longitude :" <<QString::number(elem.getLongitude(),'f',8);
//    }

    // Test requestRoadsFromNode()
    qDebug() << "Test requestRoadsFromNode";
    std::vector<Way> ways = db->requestRoadsFromNode(1215777654);
    qDebug() << "Size of ways" << ways.size();
    for(auto &way : ways)
    {
        qDebug()<< "Way id "<< way.getId();
        for (auto &node : way.getNodes())
        {
            qDebug() << node.getId() << " | " << QString::number(node.getLatitude(),'f',8) << " | " <<QString::number(node.getLongitude(),'f',8);
        }
    }

    // Test requestLatLonFromNodes()
    qDebug() << "Test requestLatLonFromNodes()";
    QVariant lat,lon;
    std::tie(lat,lon) = db->requestLatLonFromNodes(38578584);
    qDebug() << "Node n°38578584 | Latitude : "<<lat.toString()<<" | Longitude : "<<lon.toString();

    qint64 requestTime = beforeRequestTime.secsTo(afterRequestTime);           //measuring in milli-seconds
    qint64 databaseTime = afterRequestTime.secsTo(afterDatabaseTime);           //measuring in seconds

    qDebug() << "\nTemps écoulé pendant la requête : "<<requestTime<<"secondes";
    qDebug() << "\nTemps écoulé pendant la création de la base de donnée : "<<databaseTime<<"secondes\n";

    //Pour passer du C++ au QML
    QQmlApplicationEngine engine;

    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    MyAdress* myAdress = new MyAdress();
    engine.rootContext()->setContextProperty("myAdress",myAdress);
    engine.rootContext()->setContextProperty("roadsData", roadsData.data()); //créer une variable roadsData utilisable dans notre QML




    return app.exec();
}
