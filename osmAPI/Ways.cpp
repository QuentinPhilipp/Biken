#include "Ways.h"
#include <iostream>


//constructor
Ways::Ways(uint64_t id,vector<uint64_t> nodsId, vector<Nodes> n)
    : id{id}
    ,nodesId{nodsId}
    ,nodes{n}
{}


void Ways::displayNode()
{
    for (auto &e : nodes)
      {
        qDebug() << e.getId()<< "\n";
      }
}

void Ways::displayGPSData()         //display way id and the position
{                                   //using qDebug to print in the Qt console
  qDebug() << "\n~~~~~~~ Ways n° : "<< id << " ~~~~~~~";
  for (auto &e : nodes)
  {
    qDebug() << "Node id : "<< e.getId();
    qDebug() << " -Latitude : "<<e.getLatitude();
    qDebug() << " -longitude : " << e.getLongitude();
  }
}

void Ways::displayWay()         //display way id and the position
{                                   //using qDebug to print in the Qt console
  qDebug() << "\n~~~~~~~ Ways n° : "<< id << " ~~~~~~~";
  for (auto &e : nodesId)
  {
    qDebug() << "Node id : "<< e;
  }
}
