#ifndef WAY_HPP
#define WAY_HPP 1

#include "node.h"
#include <vector>
#include <QDebug>                  //using qDebug to print in the Qt console
using namespace std;

class Way
{
  public :
    Way(uint64_t id,vector<uint64_t> nodesId, Node centerNode);
    Way(uint64_t id,vector<uint64_t> nodsId,vector<Node> nods);
    Way(uint64_t id, vector<uint64_t> nodsId, vector<Node> nods, Node ctrNode);

    void displayNode();
    vector<uint64_t> getNodesId() const;
    inline uint64_t getId(){return id;}
    vector<Node> getNodes() const;

    Node getCenterNode() const;

private:
    uint64_t id;
    vector<uint64_t> nodesId;
    vector<Node> nodes;
    Node centerNode;
};


#endif
