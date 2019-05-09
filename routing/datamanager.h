#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>
#include <vector>

#include "node.h"
#include "way.h"


class DataManager: public QObject                                   //DataManager has to be an object to be used in QML
{
    Q_OBJECT                                                        //This macro is needed
public:
    explicit DataManager(QObject *parent = nullptr);

    //Q_INVOKABLE allows the function to be called from QML
    Node getNodeFromNodeId(unsigned long long nodeId, vector<Node> &nodeObjectVector);


    //getter
    inline vector<Node> getAllNodes(){return allNodes;}

    //methods
    std::vector<Node> requestNodesFromRoad(unsigned long long idRoad);
    std::vector<Node> requestNodesFromRoad(QVariant idRoad);        //overload
    std::vector<Way> requestRoadsFromNode(Node node);
    void requestRoads(double lat,double lon,double rad);
    Q_INVOKABLE QVariantList requestLatLonFromNodes(QVariant idNode);
    std::vector<QVariant> requestNodeFromLatLon(double lat, double lon);
    Q_INVOKABLE QVariantList findRouteFrom(double lat, double lon);

    vector<Node> findRoute();
    vector<Node> getNodesNearby(Node node);

private:

    //parameters
    vector<Node> allNodes;
    vector<Way> allWays;

    //methods
    void addTables();
    void addValuesNodes(std::vector<Node> nodesVetor);
    void addValuesWays(std::vector<Way> wayVector);
    vector<Way> createWayObject(QSqlQuery query, double minLat, double maxLat, double minLon, double maxLon, std::vector<Node> nodeVect);
    vector<Node> createNodeObject(QSqlQuery query, double minLat, double maxLat, double minLon, double maxLon);
};

#endif // DATAMANAGER_H
