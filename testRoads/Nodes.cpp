#include "Nodes.h"


Nodes::Nodes(string id,double lat,double lon) : id{id},latitude{lat},longitude{lon}
{};


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
