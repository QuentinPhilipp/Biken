#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "node.h"
#include "way.h"
#include "requeteapi.h"
#include "roadsdata.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //make a request to get all the roads around a coordinate
    RequeteAPI *requeteRoads = new RequeteAPI();
    QString radius = "1000"; //radius in meters. Do not set the radius too high (~200km max), otherwise it will exceed the api's capacity.
    QJsonObject allRoads = requeteRoads->getAllRoadsAroundThePoint("48.434420","-4.640103",radius);

    /*RoadsData roadsData = RoadsData();
    roadsData.generateWaysAndNodes(allRoads);
    vector<Way> wayVector = roadsData.getWayVector();*/

    QScopedPointer<RoadsData> roadsData(new RoadsData);
    roadsData->generateWaysAndNodes(allRoads);
    vector<Way> wayVector = roadsData->getWayVector();

    //Verification
    qDebug() << "\nAmount of ways: " << wayVector.size() ;  //shows the amount of Way objects
    wayVector[wayVector.size()-1].displayGPSData();         //shows the very last Way object

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.rootContext()->setContextProperty("roadsData", roadsData.data());

    return app.exec();
}
