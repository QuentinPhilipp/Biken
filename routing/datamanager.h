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

    //Méthode générale
    Node * getNodeFromNodeId(unsigned long long nodeId);

    //Méthodes pour la création des objets Node et Way
    void requestRoads(double lat,double lon,double rad);
    bool extendDatabase(QStringList departement);

    //Méthodes pour la création de l'itinéraire
    Q_INVOKABLE QVariantList createItinerary(QList<double> startCoord, QList<double> finishCoord, QVariant km); //Q_INVOKABLE allows the function to be called from QML
        //Méthodes pour la création du cercle
    Node *findClosestNode(double latitude, double longitude, string option);
    Q_INVOKABLE std::vector<Node *> getCircleNode(Node *startNode,int direction,double radius);
    Node * getCircleCenter(double radius,int direction,Node *startNode);
        //Méthodes pour créer un itinéraire
    Q_INVOKABLE QVariantList findRoute(Node *startNodeId,Node *finishNodeId);
    vector<Node *> getNodesNearby(Node * node);
    uint getPositionInWay(Node *node, Way *way);
    void routeWithAllNodes(Node * nodeA, Node *nodeB, Way *commonWay, QVariantList &nodeList);
    double distanceBetween(Node A, Node B);
    double getItineraryLength(QVariantList routeNodes);

private:

    //parameters
    vector<Node *> allNodes;
    vector<Node *> allNodesAtCrossroads;
    vector<Way *> allWays;
    vector<Way *> allWaysCloseRange;

    bool verifList(QVariantList *nodeList);
    vector<Way *> createWayObject(QSqlQuery query, double minLat, double maxLat, double minLon, double maxLon);
    vector<Node *> createNodeObject(QSqlQuery query, double minLat, double maxLat, double minLon, double maxLon);

};

#endif // DATAMANAGER_H
