#include "Ways.h"
#include <iostream>

Ways::Ways(string id,std::vector<Nodes> nds) : nodes{nds},id{id}
{}


void Ways::displayNode()
{
    for (auto &e : nodes)
      {
        std::cout << e.getid()<< "\n";
      }
}
