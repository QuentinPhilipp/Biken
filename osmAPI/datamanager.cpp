#include "datamanager.h"

#include <string>
#include <QDebug>
#include <QObject>
#include <QJsonObject>
#include <vector>
#include <algorithm>
#include <QJsonArray>
#include <tuple>

dataManager::dataManager()
{
    // open the dataBase
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName("../WaysAndNodes.db");          //path for the database    |    do not create a WaysAndNodes.db, it's done automatically
        if(!db.open())
            qDebug() << "ERROR: ";
        else
        {
            qDebug() << "DataBase opened properly";
        }
        addTables();    //create tables
    }
}

void dataManager::addTables()
{
    //Creating tables ways and nodes
    QSqlQuery queryways("CREATE TABLE ways (id BIGINT, node INTEGER)");
    QSqlQuery querynodes("CREATE TABLE nodes (id BIGINT, latitude DOUBLE, longitude DOUBLE)");
    qDebug() << "Tables created";
}

void dataManager::addValuesNodes(uint64_t id,double latitude,double longitude)
{
    QSqlQuery query,queryTest;

    //converting to Qvariant object
    QVariant latVar = QVariant(latitude);
    QVariant lonVar = QVariant(longitude);
    QVariant idVar;
    idVar.setValue(id);

    //check if the node already exist in the database
    QVariant lat,lon;
    std::tie(lat,lon) = requestLatLonFromNodes(id);
    if ((lat==latVar) && (lon==lonVar)){
        qDebug() << "Node already in the Database";                                                     //already in
    } else {
        qDebug() << "New Node.. Adding it in the database";                                             //Not in
        query.prepare("INSERT INTO nodes(id,latitude,longitude) VALUES(:id,:lat,:lon)");                //preparing the query

        query.bindValue(":id",idVar);                                                                   //setting the parameters
        query.bindValue(":lat",latitude);
        query.bindValue(":lon",longitude);
        if (!query.exec())                                                                              //execute
        {qWarning() << "ERROR Inserting nodes : " << query.lastError().text();}
    }
}

void dataManager::addValuesWays(uint64_t id,uint64_t node)                                               // add prevention to don't have the same data twice
{
    QSqlQuery query,queryTest;

    //converting to Qvariant object
    QVariant idVar;
    QVariant nodeVar;
    idVar.setValue(id);
    nodeVar.setValue(node);

    // Check if the way is already in the DataBase
    std::vector<QVariant> nodesVector = requestNodesFromRoad(id);
    if(std::find(nodesVector.begin(), nodesVector.end(), nodeVar) != nodesVector.end()) {               //std::find search a position of an object in a vector.
        // nodesVector contains nodeVar
        qDebug() << "Way already in the database";
    } else {
        // Not in the database
        qDebug() << "New way.. Adding it in the database";
        query.prepare("INSERT INTO ways(id,node) VALUES(?,?)");                                         //insert values into the ways table

        query.addBindValue(idVar);
        query.addBindValue(nodeVar);
        if (!query.exec())                                                                              //execute
        {qWarning() << "ERROR Inserting ways: " << query.lastError().text();}
    }



}

std::vector<QVariant>
dataManager::requestNodesFromRoad(uint64_t idRoad)
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
     std::vector<QVariant> nodes;
     while (query.next()) {
         QVariant val = query.value(0);
         nodes.emplace_back(val);
     }
     return nodes;

}

std::tuple<QVariant,QVariant>
dataManager::requestLatLonFromNodes(uint64_t idNode)
{
     //converting
     QVariant idRoadVar;
     idRoadVar.setValue(idNode);
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT latitude,longitude FROM nodes WHERE id = ?");
     query.addBindValue(idRoadVar);

     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding nodes: " << query.lastError().text();

     //returning a tuple with latitude and longitude. If it doesn't work, you don't have c++17 so look to the tie() function to get the data fro this function
     std::vector<QVariant> nodes;
     if (query.first()) {
         QVariant lat = query.value(0);
         QVariant lon = query.value(1);
         return std::make_tuple(lat,lon);
     }


}
