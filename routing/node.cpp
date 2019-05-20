#include "node.h"

Node::Node(unsigned long long id,double lat,double lon)
    : id{id}
    ,latitude{lat}
    ,longitude{lon}
{

}

Node::Node()
{

}

//getter (read-only)
unsigned long long Node::getId() const
{
  return this->id;
}
double Node::getLongitude() const
{
  return this->longitude;
}

double Node::getDistance() const
{
    return distance;
}

void Node::setDistance(double value)
{
    distance = value;
}

unsigned long long Node::getPrecedingNodeId() const
{
    return precedingNodeId;
}

void Node::setPrecedingNodeId(unsigned long long value)
{
    precedingNodeId = value;
}

bool Node::getMarque() const
{
    return marque;
}

void Node::setMarque(bool value)
{
    marque = value;
}

int Node::getNumberOfWays() const
{
    return numberOfWays;
}

void Node::setNumberOfWays(int value)
{
    numberOfWays = value;
}
double Node::getLatitude() const
{
    return this->latitude;
}
