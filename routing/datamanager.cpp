#include "datamanager.h"
#include "roadsdata.h"
#include <string>
#include <QDebug>
#include <QObject>
#include <QJsonObject>
#include <vector>
#include <algorithm>
#include <QJsonArray>
#include <tuple>


using namespace std;

DataManager::DataManager()
{
    // open the dataBase

    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase dbase = QSqlDatabase::addDatabase(DRIVER);
        db = dbase;                                            //store in the class
        db.setDatabaseName("../WaysAndNodes.db");          //path for the database    |    do not create a WaysAndNodes.db, it's done automatically
        if(!db.open())
            qDebug() << "ERROR: ";
        else
        {
            qDebug() << "DataBase opened properly";
            qDebug() <<"Has Feature : " <<db.driver()->hasFeature(QSqlDriver::BatchOperations);
        }
        addTables();    //create tables
    }
    else {
        qDebug() << "ERROR isDriverAvailable";
    }
}

void DataManager::addTables()
{
    //Creating tables ways and nodes
    QSqlQuery queryways("CREATE TABLE ways (id BIGINT, node INTEGER)");
    QSqlQuery querynodes("CREATE TABLE nodes (id BIGINT, latitude DOUBLE, longitude DOUBLE)");
    //qDebug() << "Tables created";
}

void DataManager::addValuesNodes(vector<Node> nodesVector)
{

    QVariantList idList;
    QVariantList latList;
    QVariantList lonList;
    for (auto &node : nodesVector){
        QVariant id,lat,lon;
        id.setValue(node.getId());
        lat.setValue(node.getLatitude());
        lon.setValue(node.getLongitude());
        idList << id;
        latList << lat;
        lonList << lon;
    }
    qDebug() << "size of node : " << idList.size();
    QSqlQuery query;
    QString queryString = "INSERT INTO nodes(id,latitude,longitude) VALUES ";
    for (int i=0;i<idList.size()-1;i++) {
        QString add = "("+idList[i].toString()+","+latList[i].toString()+","+lonList[i].toString()+"),";
        queryString = queryString + add;
    }
    QString add = "("+idList.last().toString()+","+latList.last().toString()+","+lonList.last().toString()+")";
    queryString = queryString + add;
    query.prepare(queryString);
    query.exec();
}




void DataManager::addValuesWays(vector<Way> wayVector)
{
    QVariantList nodeList;
    qDebug() << "Adding ways ";

    int cutValue = 15000;
    int i = 0;
    while (!wayVector.empty())
    {
        i = 0;
        QSqlQuery query;
        QString queryString = "INSERT INTO ways(id,node) VALUES ";
        while (i<cutValue)
        {
            uint64_t id = wayVector[0].getId();
            int counter = 0;
            for (auto &node : wayVector[0].getNodes()){
                counter +=1;
                QString add = "("+QString::fromStdString(std::to_string(id))+","+QString::fromStdString(std::to_string(node))+"),";
                queryString = queryString + add;
            }
            wayVector.erase(wayVector.begin());
            i+=counter;
        }
        query.prepare(queryString);
        query.exec();
    }


}

vector<QVariant>
DataManager::requestNodesFromRoad(uint64_t idRoad)
{
     //converting
     QVariant idRoadVar;
     idRoadVar.setValue(idRoad);
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT node FROM ways WHERE id = ?");
     query.addBindValue(idRoadVar);


     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding nodes: " << query.lastError().text();

     //add all the nodes of the result in a vector
     vector<QVariant> nodes;
     while (query.next()) {
         QVariant val = query.value(0);
         nodes.emplace_back(val);
     }
     return nodes;
}

vector<QVariant>
DataManager::requestNodesFromRoad(QVariant idRoad)
{
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT node FROM ways WHERE id = ?");
     query.addBindValue(idRoad);


     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding nodes: " << query.lastError().text();

     //add all the nodes of the result in a vector
     vector<QVariant> nodes;
     while (query.next()) {
         QVariant val = query.value(0);
         nodes.emplace_back(val);
     }
     return nodes;
}

vector<QVariant>
DataManager::requestRoadsFromNode(uint64_t idNode)
{
     //converting
     QVariant idNodeVar;
     idNodeVar.setValue(idNode);
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT id FROM ways WHERE node = ?");
     query.addBindValue(idNodeVar);

     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding roads: " << query.lastError().text();

     //add all the nodes of the result in a vector
     vector<QVariant> roads;
     while (query.next()) {
         QVariant val = query.value(0);
         roads.emplace_back(val);
     }
     return roads;
}

vector<QVariant>
DataManager::requestRoadsFromNode(QVariant idNode)
{
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT id FROM ways WHERE node = ?");
     query.addBindValue(idNode);

     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding roads: " << query.lastError().text();

     //add all the nodes of the result in a vector
     vector<QVariant> roads;
     while (query.next()) {
         QVariant val = query.value(0);
         roads.emplace_back(val);
     }
     return roads;
}

tuple<QVariant,QVariant>
DataManager::requestLatLonFromNodes(uint64_t idNode)
{
     //converting
     QVariant idNodeVar;
     idNodeVar.setValue(idNode);
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT latitude,longitude FROM nodes WHERE id = ?");
     query.addBindValue(idNodeVar);

     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding nodes: " << query.lastError().text();

     //returning a tuple with latitude and longitude. If it doesn't work, you don't have c++17 so look to the tie() function to get the data fro this function
     vector<QVariant> nodes;
     if (query.first()) {
         QVariant lat = query.value(0);
         QVariant lon = query.value(1);
         return make_tuple(lat,lon);
     }
}

QVariantList DataManager::requestLatLonFromNodes(QVariant idNode)
{
    QSqlQuery query;
    //preparing query
    query.prepare("SELECT latitude,longitude FROM nodes WHERE id = ?");
    query.addBindValue(idNode);

    //execute
    if(!query.exec())
      qWarning() << "ERROR Finding nodes: " << query.lastError().text();

    //returning a tuple with latitude and longitude. If it doesn't work, you don't have c++17 so look to the tie() function to get the data fro this function
    QVariantList nodes;
    if (query.first()) {
        QVariant lat = query.value(0);
        QVariant lon = query.value(1);
        nodes.append(lat);
        nodes.append(lon);
    }
    return nodes;
}

//not working yet
vector<QVariant> DataManager::requestNodeFromLatLon(double lat, double lon)
{
    /*
     *TO DO:
     * - try to find a node with the exact same latitude and longitude as the coordinate(lat,lon) --- ex:(48.483652,-4.235684)
     * - if it doesn't exist : remove one (or more) decimal from lat and lon and try to           --- ex: between(48.4836,-4.2356)
     *   find a node in this range                                                                ---     and    (48.4837,-4.2357)
     * - remove a decimal until there is a node in the range
     *
     * to do that, use this method: lat=floor(lat*10000)/10000 (adjusting "10000" depending on how
     * many decimal you want to remove. You have to include <math.h>
     *
     */

    //converting
    QVariant latitude, longitude;
    latitude.setValue(lat);
    longitude.setValue(lon);
    QSqlQuery query;

    //preparing query
    query.prepare("SELECT id FROM nodes WHERE latitude = ? AND longitude = ?");
    query.addBindValue(latitude);
    query.addBindValue(longitude);

    //execute
    if(!query.exec())
      qWarning() << "ERROR Finding nodes: " << query.lastError().text();
}


//Fonction pour trouver un itinéraire: à améliorer
QVariantList DataManager::findRouteFrom(double lat, double lon)
{
    /*
     * TO DO:
     * - appeler la fonction requestNodeFromLatLon(lat,lon) qui retourne le node le plus proche des coordonnées (lat,lon)
     * - trouver un way qui contient ce node
     * - partir de ce node et passer au node suivant (dans le même Way) jusqu'à ce qu'on croise un autre Way (=jusqu'à ce qu'un node soit
     *   contenu dans plus de 1 Way)
     * - à partir de ce node "de croisement", rester dans le même way ou changer de way (en fonction des possibilités)
     */
    QVariantList routeNodes;
    vector<QVariant> nodes = requestNodesFromRoad(136110431);
    qDebug() << nodes;
    QVariant startNode = nodes[0];
    qDebug() << "findRouteFrom(): example of QVariant node: " << startNode;
    routeNodes.append(startNode);
    for(auto &node: nodes){
        vector<QVariant> roads = requestRoadsFromNode(node);
        if(roads.size()>1){
            routeNodes.append(node);
            nodes = requestNodesFromRoad(roads[0]); //TO DO: checker si cette liste (nodes) est différente de celle d'avant
            break;
        }
    }
    bool b=0;
    for(auto &node: nodes){
        vector<QVariant> roads = requestRoadsFromNode(node);
        if(roads.size()>1 && b==1){
            routeNodes.append(node);
            break;
        }
        b=1;
    }
    return routeNodes;
}


