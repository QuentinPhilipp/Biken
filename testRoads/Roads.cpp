#include "Nodes.h"
#include "Ways.h"
#include <iostream>



int main()
{
  Nodes nds1 = Nodes("33438625",48.3767558,-4.5505677);
  Nodes nds2 = Nodes("33438629",48.3768234,-4.5485148);
  Nodes nds3 = Nodes("33438632",48.3770156,-4.5474697);     //creating false node
  std::vector<Nodes> nds{nds1,nds2,nds3};                   //vect of node
  string id = "372871887";                                  //create an id
  Ways w = Ways(id,nds);                                    //generating way

  w.displayNode();        //just display the node Id
  w.displayGPSData();     //display all the node and the GPS data
  return 0;
};
