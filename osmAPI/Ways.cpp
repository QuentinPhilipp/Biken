#include "Ways.h"
#include <iostream>


//constructor
Ways::Ways(string id,std::vector<Nodes> nds) : id{id},nodes{nds}
{}


void Ways::displayNode()
{
    for (auto &e : nodes)
      {
        qDebug() << atoi(e.getId().c_str())<< "\n";
      }
}

void Ways::displayGPSData()         //display way id and the position
{
  qDebug() << "~~~~~~~ Ways n° : "<< atoi(id.c_str()) << " ~~~~~~~\n\n";
  for (auto &e : nodes)
  {
    qDebug() << "Node id : "<<atoi(e.getId().c_str()) << '\n';
    qDebug() << "Latitude : "<<e.getLatitude() << '\n';
    qDebug() << "longitude : " << e.getLongitude()<<"\n\n";
  }
}


