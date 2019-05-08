#include "way.h"
#include <iostream>


//constructor
Way::Way(unsigned long long id,vector<unsigned long long> nodsId, Node ctrNode)
    : id{id}
    ,nodesId{nodsId}
    ,centerNode{ctrNode}
{}

Way::Way(unsigned long long id,vector<unsigned long long> nodsId,vector<Node> nods)
    : id{id}
    ,nodesId{nodsId}
    ,nodes{nods}
{}

Way::Way(unsigned long long id, vector<unsigned long long> nodsId, vector<Node> nods, Node ctrNode)
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

vector<unsigned long long> Way::getNodesId() const
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
