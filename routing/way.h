#ifndef WAY_HPP
#define WAY_HPP 1

#include "node.h"
#include <vector>
#include <QDebug>                  //using qDebug to print in the Qt console
using namespace std;

class Way
{
  public :
    Way(unsigned long long id, Node centerNode);
    Way(unsigned long long id,vector<Node> nods);
    Way(unsigned long long id, vector<Node> nods, Node centerNode,bool oneway,bool roundabout,int maxspeed,QString type);

    void displayNode();
    vector<unsigned long long> getNodesId() const;
    inline unsigned long long getId(){return id;}
    vector<Node> getNodes() const;

    Node getCenterNode() const;

private:
    unsigned long long id;
    vector<Node> nodes;
    Node centerNode;
    bool oneway;
    bool roundabout;
    int maxspeed;
    QString type;
};


#endif
