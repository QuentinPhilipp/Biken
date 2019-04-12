#ifndef NODES_HPP
#define NODES_HPP 1

#include <iostream>
#include <string>
#include <QDebug>                       //using qDebug to print in the Qt console
using namespace std;

class Nodes
{
  public :
    Nodes(uint64_t id,double lat,double lon); //constructor


    //getter (no setter bc it is read-only)
    uint64_t getId() const;
    double getLatitude() const;
    double getLongitude() const;

  private :
    uint64_t id;          //id of the Nodes
    double latitude;    //latitude of the node
    double longitude;   //longitude of the node
};






#endif
