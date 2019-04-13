#ifndef ROADSDATA_H
#define ROADSDATA_H

#include <iostream>
#include <QJsonObject>

#include "way.h"
#include "node.h"

using namespace std;

class RoadsData : public QObject
{
    Q_OBJECT
public:
    explicit RoadsData(QObject *parent = 0);
    void generateWaysAndNodes(QJsonObject allRoads);
    Node getNodeFromNodeId(uint64_t nodeId, vector<Node> &nodeObjectVector);
    vector<Way> getWayVector() const;
    Q_INVOKABLE void test();
    Q_INVOKABLE double getFromX(int i);
    Q_INVOKABLE double getFromY();
    Q_INVOKABLE double getToX();
    Q_INVOKABLE double getToY();

private:
    vector<Way> wayVector;

};

#endif // ROADSDATA_H
