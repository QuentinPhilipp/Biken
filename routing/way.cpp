#include "way.h"
#include <iostream>


//constructor
Way::Way(uint64_t id,vector<uint64_t> nodsId, vector<Node> n)
    : id{id}
    ,nodesId{nodsId}
    ,nodes{n}
{}


void Way::displayNode()
{
    for (auto &e : nodes)
      {
        qDebug() << e.getId()<< "\n";
      }
}

void Way::displayGPSData()         //display way id and the position
{                                   //using qDebug to print in the Qt console
  qDebug() << "\n~~~~~~~ Way n° : "<< id << " ~~~~~~~";
  for (auto &e : nodes)
  {
    qDebug() << "Node id : "<< e.getId();
    qDebug() << " -Latitude : "<<e.getLatitude();
    qDebug() << " -longitude : " << e.getLongitude();
  }
}

void Way::displayWay()         //display way id and the position
{                                   //using qDebug to print in the Qt console
  qDebug() << "\n~~~~~~~ Way n° : "<< id << " ~~~~~~~";
  for (auto &e : nodesId)
  {
    qDebug() << "Node id : "<< e;
  }
}

vector<Node> Way::getNodes() const
{
    return nodes;
}
