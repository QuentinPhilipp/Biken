#ifndef ROADSDATA_H
#define ROADSDATA_H

#include <iostream>
#include <QJsonObject>

#include "way.h"
#include "node.h"
#include "datamanager.h"

using namespace std;

class RoadsData : public QObject
{
    Q_OBJECT
public:
    explicit RoadsData(QObject *parent = nullptr);
    void generateWaysAndNodes(QJsonObject allRoads, DataManager db);
    Node getNodeFromNodeId(uint64_t nodeId, vector<Node> &nodeObjectVector);
    vector<Way> getWayVector() const;

    //tests pour envoyer des données au qml
    Q_INVOKABLE QVariantList findRouteFrom(double lat, double lon);
    Q_INVOKABLE QVariantList requestLatLonFromNodes(QVariant idNode);

private:
    vector<Way> wayVector;
    DataManager myDb;

};

#endif // ROADSDATA_H
