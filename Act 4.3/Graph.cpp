#include "Graph.h"



Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
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
          LinkedList<std::pair<int,int>> tmpList; // en ponderado lista de pares
          adjList[k] = tmpList; 
        }
      }
      else if (i > 0 && i <= numNodes) {
        ipAddress tmpIP(line, "", i);
        ips[i] = tmpIP;
        mapIP.insert({tmpIP.getIpValue(), tmpIP}); // {string ip, int}
        // std::cout << "i: " << i << " IP: " << line << std::endl;
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
        int ip1Index, ip2Index;
        it = mapIP.find(tmpIP1.getIpValue());     
        if(it != mapIP.end())
          ip1Index = it->second.getIpIndex();
        it = mapIP.find(tmpIP2.getIpValue());     
        if(it != mapIP.end())
          ip2Index = it->second.getIpIndex();
        adjList[ip1Index].addLast({ip2Index, stoi(peso)});
        ips[ip1Index].addToDegree();
      }
      i++;
    }
    file.close();
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


// Codigo recuperado y adaptado de: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
void Graph::shortestPath(){
    int src = bmIndex;
    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    std::priority_queue< std::pair<int, int>, std::vector <std::pair<int, int>> , std::greater<std::pair<int, int>> > pq;
 
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    std::vector<int> dist(numNodes+1, INF);
 
    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(std::make_pair(0, src));
    dist[src] = 0;
 
    /* Looping till priority queue becomes empty (or all
      distances are not finalized) */
    while (!pq.empty()) {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();
        // Nodos adyacentes
        for (int j = 0; j < (int)adjList[u].getNumElements(); j ++) {
          std::pair<int,int> p = adjList[u].getData(j);
          int v = p.first; // Vertice adyacente
          int weight = p.second; // Ponderacion
          if (dist[v] > dist[u] + weight) {
            // Actualizando V
            dist[v] = dist[u] + weight;
            pq.push(std::make_pair(dist[v], v));
          }
        }
      }
      // Creacion de archivo
      std::ofstream file("distancia_bootmaster.txt");
      if (!file.good()) {
        file.close();
        throw std::invalid_argument("File not found");
      }else{
      // Almacenar ip y distancia en archivo
      file << "IP   Distancia de Source " << std::endl;
      for (int i = 1; i < numNodes+1; ++i){
        if(dist[i] == INF){
          file << ips[i].getIp() << "\t\t" << "INF" << std::endl;
          heapDijkstra.push(std::make_pair(dist[i], ips[i].getIp()));
        }
        else{
          file << ips[i].getIp() << "\t\t" << dist[i] << std::endl;
          heapDijkstra.push(std::make_pair(dist[i], ips[i].getIp()));
        }
      }
    file.close();
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
