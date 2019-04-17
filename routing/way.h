#ifndef WAY_HPP
#define WAY_HPP 1

#include "node.h"
#include <vector>
#include <QDebug>                  //using qDebug to print in the Qt console
using namespace std;

class Way
{
  public :
    Way(uint64_t id,vector<uint64_t> nodesId);
    Way(uint64_t id,vector<uint64_t> nodsId,vector<Node> nods);

    void displayNode();
    vector<uint64_t> getNodesId() const;
    inline uint64_t getId(){return id;}
    vector<Node> getNodes() const;

private:
    uint64_t id;
    vector<uint64_t> nodesId;
    vector<Node> nodes;
};


#endif
