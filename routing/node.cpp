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
double Node::getLatitude() const
{
  return this->latitude;
}
