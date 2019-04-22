#include "way.h"
#include <iostream>


//constructor
Way::Way(uint64_t id,vector<uint64_t> nodsId, Node ctrNode)
    : id{id}
    ,nodesId{nodsId}
    ,centerNode{ctrNode}
{}

Way::Way(uint64_t id,vector<uint64_t> nodsId,vector<Node> nods)
    : id{id}
    ,nodesId{nodsId}
    ,nodes{nods}
{}

Way::Way(uint64_t id, vector<uint64_t> nodsId, vector<Node> nods, Node ctrNode)
    : id{id}
    ,nodesId{nodsId}
    ,nodes{nods}
    ,centerNode{ctrNode}
{}


void Way::displayNode()
{
    for (auto &e : nodesId)
      {
        qDebug() << e << "\n";
      }
}

vector<uint64_t> Way::getNodesId() const
{
    return nodesId;
}

vector<Node> Way::getNodes() const
{
    return nodes;
}

Node Way::getCenterNode() const
{
    return centerNode;
}
