#ifndef WAYS_HPP
#define WAYS_HPP 1

#include "Nodes.h"
#include <vector>
#include <QDebug>                  //using qDebug to print in the Qt console
using namespace std;

class Ways
{
  public :
    Ways(uint64_t id,vector<uint64_t> nodesId,vector<Nodes> n);

    void displayNode();
    void displayGPSData();
    void displayWay();

  private:
    uint64_t id;
    vector<uint64_t> nodesId;
    vector<Nodes> nodes;
};


#endif
