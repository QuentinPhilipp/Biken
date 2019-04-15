#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <QDebug>

using namespace std;

class Node
{
public :
  Node(uint64_t id,double lat,double lon); //constructor

  //getter (no setter bc it is read-only)
  uint64_t getId() const;
  double getLatitude() const;
  double getLongitude() const;

private :
  uint64_t id;          //id of the Node
  double latitude;    //latitude of the node
  double longitude;   //longitude of the node
};

#endif // NODE_H
