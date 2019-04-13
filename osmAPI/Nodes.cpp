#include "Nodes.h"


//constructor
Nodes::Nodes(uint64_t id,double lat,double lon) : id{id},latitude{lat},longitude{lon}
{};



//getter (read-only)
uint64_t Nodes::getId() const
{
  return this->id;
}
double Nodes::getLongitude() const
{
  return this->longitude;
}
double Nodes::getLatitude() const
{
  return this->latitude;
}
