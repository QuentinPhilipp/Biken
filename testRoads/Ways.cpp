#include "Ways.h"
#include <iostream>


//constructor
Ways::Ways(string id,std::vector<Nodes> nds) : nodes{nds},id{id}
{}


void Ways::displayNode()
{
    for (auto &e : nodes)
      {
        std::cout << e.getid()<< "\n";
      }
}

void Ways::displayGPSData()         //display way id and the position
{
  std::cout << "~~~~~~~ Ways n° : "<< id << " ~~~~~~~\n\n";
  for (auto &e : nodes)
  {
    std::cout << "Node id : "<<e.getid() << '\n';
    std::cout << "Latitude : "<<e.getLatitude() << '\n';
    std::cout << "longitude : " << e.getLongitude()<<"\n\n";
  }
}
