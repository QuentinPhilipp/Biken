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
    // create the dataBase
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER))                                    //checking the availability of the driver
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);                       //Adding the driver
        db.setDatabaseName("../WaysAndNodes.db");                                  //path for the database    |    do not create a WaysAndNodes.db, it's done automatically

        //open the database
        if(!db.open())
        {qDebug() << "ERROR opening the database ";}
        else
        {qDebug() << "DataBase opened properly";}

        addTables();                                                                //create tables
    }
    else {
        qDebug() << "ERROR Driver not Available";
    }
}

void DataManager::addTables()
{   /* This functions create the tables
      Tables are only created the first time. If the
      database already exist, tables will not be created*/

    //Adding the ways table
    QSqlQuery queryways("CREATE TABLE IF NOT EXISTS ways (id_way BIGINT, node BIGINT)");                        //using BIGINT to fit with uint64_t
    if(!queryways.exec())
    {qDebug()<<"Error creating ways table"<<queryways.lastError();}


    //Adding the node table
    QSqlQuery querynodes("CREATE TABLE IF NOT EXISTS nodes (id_node BIGINT, latitude DOUBLE, longitude DOUBLE)");
    if(!querynodes.exec())
    {qDebug()<<"Error creating node table"<<querynodes.lastError();}
}

void DataManager::addValuesNodes(vector<Node> nodesVector)
{
    qDebug() << "\n~~ Adding nodes ~~";
    qDebug() << "In progress...";

    int cutValue = 15000;                                                                   //we split the queryString if there is more than n values to append
    int i = 0;                                                                              //this help the programm to run faster
    while (!nodesVector.empty())
    {
        i = 0;                                                                              //reset the counter
        QSqlQuery query;
        QString queryString = "INSERT INTO nodes(id_node,latitude,longitude) VALUES ";           //preparing the beginning of each query
        while (i<cutValue)
        {
            uint64_t id = nodesVector[0].getId();
            double valueAsDouble = 1.2;
            QString valueAsString = QString::number(valueAsDouble);
            QString add = "("+QString::fromStdString(std::to_string(id))+","+QString::number(nodesVector[0].getLatitude(),'f',8)+","+QString::number(nodesVector[0].getLongitude(),'f',8)+"),";
            /*the string look like : "(1215779765,48.4368521,-4.6501655"
              QString::number(aDoubleValue,'f',8) is used to cast double
            to QString with 8 numbers precision, so we don't lose data*/
            queryString = queryString + add;                                                //adding the string to the query
            nodesVector.erase(nodesVector.begin());                                         //pop the first element of the vector

            if(nodesVector.empty()){
                break;
            }
            i++;                                                                            //increment counter to detect when we have to split the querry

        }
        int pos = queryString.lastIndexOf(QChar(','));                                      //this 2 lines help to remove the last "," in the end of the query
        queryString = queryString.left(pos);

        query.prepare(queryString);                                                         //preparing query

        if(!query.exec())                                                                   //Execute
          qWarning() << "ERROR Adding nodes: " << query.lastError().text();
    }
    qDebug() << "~~ All nodes added ~~";
}

void DataManager::addValuesWays(vector<Way> wayVector)
{
    qDebug() << "\n~~ Adding ways ~~";
    qDebug() << "In progress ...";

    int cutValue = 15000;                                                                   //we split the queryString if there is more than n values to append
    int i = 0;                                                                              //this help the programm to run faster
    while (!wayVector.empty())
    {
        i = 0;                                                                              //reset the counter
        QSqlQuery query;
        QString queryString = "INSERT INTO ways(id_way,node) VALUES ";                          //preparing the beginning of each query
        while (i<cutValue)
        {
            uint64_t id = wayVector[0].getId();
            int counter = 0;                                                                //to be sure to add all the node of a way, we don't split querry in a way. We wait the end
                                                                                            //of this way. So we add a counter to add in "i" the good number
            for (auto &node : wayVector[0].getNodesId()){
                counter +=1;
                QString add = "("+QString::fromStdString(std::to_string(id))+","+QString::fromStdString(std::to_string(node))+"),";
                queryString = queryString + add;
            }
            wayVector.erase(wayVector.begin());                                             //pop the first element of the vector
            if(wayVector.empty()){
                break;
            }
            i+=counter;                                                                     //increment counter to detect when we have to split the querry
        }
        int pos = queryString.lastIndexOf(QChar(','));                                      //this 2 lines help to remove the last "," in the end of the query
        queryString = queryString.left(pos);

        query.prepare(queryString);                                                         //preparing query

        if(!query.exec())                                                                   //Execute
          qWarning() << "ERROR Adding ways: " << query.lastError().text();
    }
    qDebug() << "~~ Ways added ~~";


}

vector<Node>
DataManager::requestNodesFromRoad(uint64_t idRoad)
{
     //converting
     QVariant idRoadVar;
     idRoadVar.setValue(idRoad);
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT id_node,latitude,longitude FROM nodes, ways WHERE (id_node=node) and (id_way = ? )");
     query.addBindValue(idRoadVar);


     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding nodes: " << query.lastError().text();

     //add all the nodes of the result in a vector
     vector<Node> nodes;
     while (query.next()) {
         uint64_t id = static_cast<uint64_t>(query.value(0).toDouble());
         double lat = query.value(1).toDouble();
         double lon = query.value(2).toDouble();
         Node n = Node(id,lat,lon);
         nodes.emplace_back(n);
     }
     return nodes;
}

vector<Node>    //overload
DataManager::requestNodesFromRoad(QVariant idRoad)
{
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT id_node,latitude,longitude FROM nodes, ways WHERE (id_node=node) and (id_way = ? )");
     query.addBindValue(idRoad);


     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding nodes: " << query.lastError().text();

     //add all the nodes of the result in a vector
     vector<Node> nodes;
     while (query.next()) {
         uint64_t id = static_cast<uint64_t>(query.value(0).toDouble());
         double lat = query.value(1).toDouble();
         double lon = query.value(2).toDouble();
         Node n = Node(id,lat,lon);
         nodes.emplace_back(n);
     }
     return nodes;
}

vector<Way>
DataManager::requestRoadsFromNode(uint64_t idNode)
{
     //converting
     QVariant idNodeVar;
     idNodeVar.setValue(idNode);
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT id_way, id_node,latitude,longitude FROM nodes,ways WHERE id_way IN (SELECT id_way FROM nodes, ways WHERE (id_node = node) and (id_node=?)) and (id_node=node) ORDER BY id_way");
     query.addBindValue(idNodeVar);

     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding roads: " << query.lastError().text();

     query.first();
     //add all the nodes of the result in a vector
     vector<Way> roads;
     uint64_t lastId = static_cast<uint64_t>(query.value(0).toDouble());
     vector<Node> nodeVect;
     vector<uint64_t> nodeIdVect;

     while (query.next()) {
         uint64_t idWay = static_cast<uint64_t>(query.value(0).toDouble());
         qDebug() << "idWay"<<idWay;
         qDebug()<< "oldIdWay"<<lastId;
         if (idWay != lastId)
         {
             Way w = Way(idWay,nodeIdVect,nodeVect);
             roads.emplace_back(w);
             lastId = static_cast<uint64_t>(query.value(0).toDouble());
             nodeIdVect={};
             nodeVect={};
         }
         uint64_t idNode = static_cast<uint64_t>(query.value(1).toDouble());
         double lat = query.value(2).toDouble();
         double lon = query.value(3).toDouble();
         Node n = Node(idNode,lat,lon);
         nodeVect.emplace_back(n);
         nodeIdVect.emplace_back(idNode);
     }
     return roads;
}

vector<Way>
DataManager::requestRoadsFromNode(QVariant idNode)
{
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT id FROM ways WHERE node = ?");
     query.addBindValue(idNode);

     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding roads: " << query.lastError().text();

//     //add all the nodes of the result in a vector
//     vector<Way> roads;
//     while (query.next()) {
//         QVariant val = query.value(0);
//         roads.emplace_back(val);
//     }
//     return roads;
}

tuple<QVariant,QVariant>
DataManager::requestLatLonFromNodes(uint64_t idNode)
{
     //converting
     QVariant idNodeVar;
     idNodeVar.setValue(idNode);
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT latitude,longitude FROM nodes WHERE id=?");
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
     return make_tuple(-1,-1);
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
//    QVariantList routeNodes;
//    vector<Node> nodes = requestNodesFromRoad(136110431);
//    qDebug() << nodes;
//    QVariant startNode = nodes[0];
//    qDebug() << "findRouteFrom(): example of QVariant node: " << startNode;
//    routeNodes.append(startNode);
//    for(auto &node: nodes){
//        vector<QVariant> roads = requestRoadsFromNode(node);
//        if(roads.size()>1){
//            routeNodes.append(node);
//            nodes = requestNodesFromRoad(roads[0]); //TO DO: checker si cette liste (nodes) est différente de celle d'avant
//            break;
//        }
//    }
//    bool b=0;
//    for(auto &node: nodes){
//        vector<QVariant> roads = requestRoadsFromNode(node);
//        if(roads.size()>1 && b==1){
//            routeNodes.append(node);
//            break;
//        }
//        b=1;
//    }
//    return routeNodes;
}


