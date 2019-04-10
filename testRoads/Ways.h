#ifndef WAYS
#define WAYS 1

#include "Nodes.h"
#include <vector>
using namespace std;

class Ways
{
  public :
  Ways(string id,std::vector<Nodes> nodes);

  void displayNode();

  private :
  string id;
  std::vector<Nodes> nodes;
};


#endif
