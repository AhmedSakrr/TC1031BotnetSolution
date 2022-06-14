#include "Graph.h"




Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  table = HashTable<long long int, std::string>(13999); //numero primo proximo al numero de nodos
}

Graph::~Graph() {
  adjList.clear();
  ips.clear();
}

void Graph::loadGraphList(std::string fileName) {
  std::string line, ip1, ip2, peso;
  int i = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while(std::getline(file,line)) {
      if (i == 0) {
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        //std::cout << "numNodes " << numNodes << std::endl;
        //std::cout << "numEdges " << numEdges << std::endl;
        // Reservar memoria para los renglones de la lista de adyacencia (renglon 0 no utilizado) 
        adjList.resize(numNodes+1);
        ips.resize(numNodes+1);
        // Declara una lista vacia para cada renglon y la almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          LinkedList<std::string> tmpList; // en ponderado lista de pares
          adjList[k] = tmpList; 
        }
      }
      else if (i > 0 && i <= numNodes) {
        ipAddress tmpIP(line, "", i);
        ips[i] = tmpIP;
        mapIP.insert({tmpIP.getIpValue(), tmpIP}); // {string ip, int}
        // std::cout << "i: " << i << " IP: " << line << std::endl;
        ///HashNode<int,std::string> tmpNode(0,line);
        table.add(tmpIP.getIpValue(),tmpIP.getIp());
      } 
      else if (i > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found-15);
        std::size_t found2 = line.find(" ", found+1);
        std::size_t found3 = line.find(":", found2+1);
        ip2 = line.substr(found2, found3-found2);
        std::size_t found4 = line.find(" ", found3+1);
        std::size_t found5 = line.find(" ", found4+1);
        peso = line.substr(found4, found5-found4);
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, "", 0);
        ipAddress tmpIP2(ip2, "", 0);
        
        std::map<unsigned int, ipAddress>::iterator it;
        std::pair<int,int>keys;
        keys.first=table.find(tmpIP1.getIpValue());
        keys.second=table.find(tmpIP2.getIpValue());
        
        int ip1Index, ip2Index;
        it = mapIP.find(tmpIP1.getIpValue());     
        if(it != mapIP.end())
          ip1Index = it->second.getIpIndex();
        it = mapIP.find(tmpIP2.getIpValue());     
        if(it != mapIP.end())
          ip2Index = it->second.getIpIndex();
        adjList[ip1Index].addLast(ip2);
        ips[ip1Index].addToDegree();
        //ips[ip2Index].addToDegre out
        table.addDegree(keys.first,keys.second);
      }
      i++;
    }
    file.close();
    //table.print();
    table.totalOverFlowPrint();
  }
}

void Graph::outDegrees(std::string fileName) {
  std::ofstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    for (int i = 1; i <= numNodes; i++) {
      file << "ip: " << ips[i].getIp() << "  grado: "  << ips[i].getDegree() << std::endl;
      maxHeapIPs.push(std::make_pair(ips[i].getDegree(), ips[i].getIp()));
    }
    file.close();
  }
}

void Graph::maxDegrees(std::string fileName) {
  std::ofstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    // get 5 ips
    for (int i = 1; i <= 5; i++) {
      std::pair<int, std::string> p = maxHeapIPs.top();
      maxHeapIPs.pop();
      file << "ip: " << p.second << "  grado: "  << p.first << std::endl;
    }
    file.close();
  }
}

void Graph::bootMaster(){
  std::pair<int, std::string> p = maxHeapIPs.top();
  std::cout << "Bootmaster: " << p.second << " con grado: " << p.first << std::endl;
  for (int i = 1; i <= numNodes; i++){
    if(ips[i].getIp() == p.second){
      bmIndex = ips[i].getIpIndex();
    }else{
      continue;
    }
  }
}

void Graph::menosVulnerable(){
  for (int i = 1; i < 2; i++) {
    std::pair<int, std::string> p = heapDijkstra.top();
    heapDijkstra.pop();
    std::cout << "ip menos vulnerable: " << p.second << " con distancia: "  << p.first << std::endl;
  }
}

void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

/*
void Graph::printGraph(){
	  std::cout << "Adjacency List" << std::endl;
		for (int u = 1; u <= numNodes; u++){
      std::cout << "vertex " << u << ": ";
      for (int j = 0; j < adjList[u].getNumElements(); j++) {
        std::pair<int, int> p = adjList[u].getData(j);
        std::cout << "{" << p.first << ", " << p.second << "} ";
      }
      std::cout << std::endl;
    }
}
*/

// Complejidad O(n)
bool Graph::validate(std::string ip){
  for (int i = 0; i < table.getSize(); i++){
      if (table.getDataAt(i) == ip){
        std::cout << "IP encontrada en bitacora. " << std::endl;
        return true; 
      }
    }
  return false;
}

// Complejidad O(n^2)

void Graph::getIPSummary(){
  std::string input;
  std::cout << "IP a buscar: " << std::endl;
  std::cin >> input;
  bool existe = false;
  if (this->validate(input) == true){
    for (int i = 0; i < table.getSize(); i++){
    if (input == table.getDataAt(i)){
      table.printAt(i);
      existe=true;
    }else{
      continue;
      }
    }
  }else{
    std::cout << "IP no se encuentra en bitacora. " << std::endl;
  }
  if(existe){
  int ipIndex;
  std::map<unsigned int, ipAddress>::iterator it;
  ipAddress tmpIP(input, "", 0);
  it = mapIP.find(tmpIP.getIpValue());
  if(it != mapIP.end())
  ipIndex = it->second.getIpIndex();
  std::priority_queue<std::pair<long long int, std::string>> maxHeapTemp;
  for (int i =0;i<adjList[ipIndex].getNumElements();i++){
    ipAddress tmpIP(adjList[ipIndex].getData(i), "", 0);
maxHeapTemp.push(std::make_pair(tmpIP.getIpValue(),adjList[ipIndex].getData(i)));
  }
      std::cout << "Direcciones accesadas desde IP: " << std::endl;
      for (int i =0;i<adjList[ipIndex].getNumElements();i++) {
      std::pair<long long int, std::string> p = maxHeapTemp.top();
      maxHeapTemp.pop();
      std::cout << i+1 << ". " <<p.second << std::endl;
    }
  }
}