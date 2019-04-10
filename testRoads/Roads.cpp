#include "Nodes.h"
#include "Ways.h"
#include <iostream>



int main()
{
  Nodes nds1 = Nodes("33438625",48.3767558,-4.5505677);
  Nodes nds2 = Nodes("33438629",48.3768234,-4.5485148);
  Nodes nds3 = Nodes("33438632",48.3770156,-4.5474697);
  std::vector<Nodes> nds{nds1,nds2,nds3};
  string id = "372871887";
  Ways w = Ways(id,nds);

  w.displayNode();
  return 0;
};
