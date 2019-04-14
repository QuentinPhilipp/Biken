#ifndef WAY_HPP
#define WAY_HPP 1

#include "node.h"
#include <vector>
#include <QDebug>                  //using qDebug to print in the Qt console
using namespace std;

class Way
{
  public :
    Way(uint64_t id,vector<uint64_t> nodesId,vector<Node> n);

    void displayNode();
    void displayGPSData();
    void displayWay();

    vector<Node> getNodes() const;

private:
    uint64_t id;
    vector<uint64_t> nodesId;
    vector<Node> nodes;
};


#endif
