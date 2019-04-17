#include "node.h"

Node::Node(uint64_t id,double lat,double lon)
    : id{id}
    ,latitude{lat}
    ,longitude{lon}
{

}

Node::Node()
{

}

//getter (read-only)
uint64_t Node::getId() const
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
