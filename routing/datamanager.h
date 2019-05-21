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
    Node * getNodeFromNodeId(unsigned long long nodeId);


    //getter
    //vector<Node *> getAllNodes();

    //vector<Way *> getAllWays();

    //    //methods
    std::vector<Node> requestNodesFromRoad(unsigned long long idRoad);
    std::vector<Node> requestNodesFromRoad(QVariant idRoad);        //overload
    std::vector<Way *> requestRoadsFromNode(Node * node);
    Node *getCircleCenter(double radius,int direction,unsigned long long startNodeId);
    void requestRoads(double lat,double lon,double rad);
    Q_INVOKABLE QVariantList requestLatLonFromNodes(QVariant idNode);
    std::vector<QVariant> requestNodeFromLatLon(double lat, double lon);

    Q_INVOKABLE QVariantList findRouteFrom(double lat, double lon);
    //vector<Node> findRoute();
    Q_INVOKABLE QVariantList findRoute(unsigned long long startNodeId,unsigned long long finishNodeId);
    Q_INVOKABLE QVariantList getCircleNode();
    vector<Node *> getNodesNearby(Node * node);
    double distanceBetween(Node A, Node B);
    double bearingBetween(Node A, Node B);
    bool addNodes(QVariantList &routeNodes, unsigned long long finishNodeId);

    uint getPositionInWay(Node *node, Way *way);

    Node *findClosestNode(double latitude, double longitude);
private:

    //parameters
    vector<Node *> allNodes;
    vector<Node *> allNodesAtCrossroads;
    vector<Way *> allWays;

    //methods
    //    void addTables();
    //    void addValuesNodes(std::vector<Node> nodesVetor);
    //    void addValuesWays(std::vector<Way> wayVector);
    QVariantList verifList(QVariantList nodeList);
    vector<Way *> createWayObject(QSqlQuery query, double minLat, double maxLat, double minLon, double maxLon);
    vector<Node *> createNodeObject(QSqlQuery query, double minLat, double maxLat, double minLon, double maxLon);

};

#endif // DATAMANAGER_H
