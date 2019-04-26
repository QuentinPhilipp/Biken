#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>
#include <vector>

#include "requeteapi.h"
#include "node.h"
#include "way.h"


class DataManager: public QObject                                   //DataManager has to be an object to be used in QML
{
    Q_OBJECT                                                        //This macro is needed
public:
    explicit DataManager(QObject *parent = nullptr);
    Q_INVOKABLE void generateWaysAndNodes(QVariant radius);         //Q_INVOKABLE allows the function to be called from QML
    Node getNodeFromNodeId(uint64_t nodeId, vector<Node> &nodeObjectVector);

    std::vector<Node> requestNodesFromRoad(uint64_t idRoad);
    std::vector<Node> requestNodesFromRoad(QVariant idRoad);        //overload

    std::vector<Way> requestRoadsFromNode(uint64_t idNode);
    std::vector<Way> requestRoadsFromNode(QVariant idNode);         //overload
    std::vector<Way> requestRoadsFromNode(Node node);               //overload

    void requestRoads();

    Q_INVOKABLE QVariantList requestLatLonFromNodes(QVariant idNode);

    std::vector<QVariant> requestNodeFromLatLon(double lat, double lon);

    Q_INVOKABLE QVariantList findRouteFrom(double lat, double lon);
private:
    void addTables();
    void addValuesNodes(std::vector<Node> nodesVetor);
    void addValuesWays(std::vector<Way> wayVector);
    vector<Node> allNodes;
    vector<Way> allWays;
};

#endif // DATAMANAGER_H
