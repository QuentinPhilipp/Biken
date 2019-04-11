#ifndef NODES_HPP
#define NODES_HPP 1

#include <iostream>
#include <string>
#include <QDebug>                       //using qDebug to print in the Qt console
using namespace std;

class Nodes
{
  public :
    Nodes(string id,double lat,double lon); //constructor


    //getter (no setter bc it is read-only)
    string getId() const;
    double getLatitude() const;
    double getLongitude() const;

  private :
    string id;          //id of the Nodes
    double latitude;    //latitude of the node
    double longitude;   //longitude of the node
};






#endif
