#include "way.h"
#include <iostream>


//constructor
Way::Way(uint64_t id,vector<uint64_t> nodsId)
    : id{id}
    ,nodesId{nodsId}
{}


void Way::displayNode()
{
    for (auto &e : nodesId)
      {
        qDebug() << e << "\n";
      }
}

vector<uint64_t> Way::getNodes() const
{
    return nodesId;
}
