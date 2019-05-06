#include "requeteapi.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QtMath>


RequeteAPI::RequeteAPI()
{

}

std::tuple<std::vector<Way>, std::vector<Node>> RequeteAPI::requestToDatabase(QString lat,QString lon,QString rad)      //RAD in KM
{
    QSqlQuery query;


    // Get NODE

    //converting
    double minLat = lat.toDouble() - rad.toDouble()/111.11;
    double maxLat = lat.toDouble() + rad.toDouble()/111.11;

    double minLon = lon.toDouble() - rad.toDouble()/(111.11*cos(lat.toDouble()));           //Pour la longitude il faut faire * cos(latitude) car 1° =111.11 a l'equateur mais pas partout
    double maxLon = lon.toDouble() + rad.toDouble()/(111.11*cos(lat.toDouble()));

    //preparing query
    query.prepare("SELECT DISTINCT id_node,latitude,longitude FROM nodes WHERE (:minLat<=lat) AND (lat<=?) AND (?<=lon) AND (lon<=?)");
    query.bindValue(":minLat",minLat);
    query.bindValue(":maxLat",maxLat);
    query.bindValue(":minLon",minLon);
    query.bindValue(":maxLon",maxLon);

    //execute
    if(!query.exec())
      qWarning() << "ERROR Finding nodes: " << query.lastError().text();

    //add all the nodes of the result in a vector
    vector<Node> nodes;
    while (query.next()) {
        unsigned long long id = static_cast<unsigned long long>(query.value(0).toDouble());
        double lat = query.value(1).toDouble();
        double lon = query.value(2).toDouble();
        Node n = Node(id,lat,lon);
        nodes.emplace_back(n);
    }

}

