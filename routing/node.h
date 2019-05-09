#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <QDebug>

using namespace std;

class Node
{
public :
  Node(unsigned long long id,double lat,double lon); //constructor
  Node();

  //getter (no setter bc it is read-only)
  unsigned long long getId() const;

  double getLatitude() const;
  double getLongitude() const;

  int getDistance() const;
  void setDistance(int value);

private :
  unsigned long long id;          //id of the Node
  double latitude;    //latitude of the node
  double longitude;   //longitude of the node
  int distance=999999999;
};

#endif // NODE_H
