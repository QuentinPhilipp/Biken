#include "Nodes.h"


//constructor
Nodes::Nodes(string id,double lat,double lon) : id{id},latitude{lat},longitude{lon}
{};



//getter (read-only)
string Nodes::getid() const
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
