#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Graph.h"

class Bitacora {

  private:
    Graph graph;

  public:
    Bitacora();
    Bitacora(std::string fileName);
    ~Bitacora();

};



#endif  // _BITACORA_H_