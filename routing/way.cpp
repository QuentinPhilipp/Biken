#include "way.h"
#include <iostream>


//constructor
Way::Way(uint64_t id,vector<uint64_t> nodsId)
    : id{id}
    ,nodesId{nodsId}
{}

Way::Way(uint64_t id,vector<uint64_t> nodsId,vector<Node> nods)
    : id{id}
    ,nodesId{nodsId}
    ,nodes{nods}
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
