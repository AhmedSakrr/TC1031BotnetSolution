#include "Bitacora.h"


Bitacora::Bitacora() {

}

Bitacora::Bitacora(std::string fileName) {
  graph.loadGraphList(fileName);
  graph.getIPSummary();
  // graph.printGraph();
  //graph.outDegrees("grados_ips.txt");
  //graph.bootMaster();
  //graph.maxDegrees("mayores_grados_ips.txt");
  //graph.shortestPath();
  //graph.menosVulnerable();
  //graph.mapToHash();
}

Bitacora::~Bitacora() {

}

