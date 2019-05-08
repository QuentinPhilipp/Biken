#include "way.h"
#include <iostream>


//constructor
Way::Way(unsigned long long id, Node ctrNode)
    : id{id}
    ,centerNode{ctrNode}
{}

Way::Way(unsigned long long id,vector<Node> nods)
    : id{id}
    ,nodes{nods}
{}

Way::Way(unsigned long long id, vector<Node> nods, Node centerNode,bool oneway,bool roundabout,int maxspeed,QString type)
    : id{id}
    ,nodes{nods}
    ,centerNode{centerNode}
    ,oneway{oneway}
     ,roundabout{roundabout}
    ,maxspeed{maxspeed}
    ,type{type}
{}




vector<Node> Way::getNodes() const
{
    return nodes;
}

Node Way::getCenterNode() const
{
    return centerNode;
}
