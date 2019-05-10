#include "way.h"
#include <iostream>


//constructor
<<<<<<< routing/way.cpp
Way::Way(unsigned long long id,vector<unsigned long long> nodsId, Node ctrNode)
=======
Way::Way(unsigned long long id, Node ctrNode)
>>>>>>> routing/way.cpp
    : id{id}
    ,centerNode{ctrNode}
{}

<<<<<<< routing/way.cpp
Way::Way(unsigned long long id,vector<unsigned long long> nodsId,vector<Node> nods)
=======
Way::Way(unsigned long long id,vector<Node> nods)
>>>>>>> routing/way.cpp
    : id{id}
    ,nodes{nods}
{}

<<<<<<< routing/way.cpp
Way::Way(unsigned long long id, vector<unsigned long long> nodsId, vector<Node> nods, Node ctrNode)
=======
Way::Way(unsigned long long id, vector<Node> nods, Node centerNode,bool oneway,bool roundabout,int maxspeed,QString type)
>>>>>>> routing/way.cpp
    : id{id}
    ,nodes{nods}
    ,centerNode{centerNode}
    ,oneway{oneway}
     ,roundabout{roundabout}
    ,maxspeed{maxspeed}
    ,type{type}
{}

<<<<<<< routing/way.cpp

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

=======
>>>>>>> routing/way.cpp
vector<Node> Way::getNodes() const
{
    return nodes;
}

Node Way::getCenterNode() const
{
    return centerNode;
}
