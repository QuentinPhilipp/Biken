#ifndef WAYS_HPP
#define WAYS_HPP 1

#include "Nodes.h"
#include <vector>
#include <QDebug>
using namespace std;

class Ways
{
  public :
    Ways(string id,std::vector<Nodes> nodes);

    void displayNode();
    void displayGPSData();

  private:
    string id;
    std::vector<Nodes> nodes;
};


#endif
