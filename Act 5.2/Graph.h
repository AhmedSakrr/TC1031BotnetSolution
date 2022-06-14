
#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include "LinkedList.h"
#include "ipAddress.h"
#include "HashTable.h"
#define INF 0x3f3f3f3f

class Graph {
  private:
    int numNodes;
    int numEdges;
    int bmIndex;
    // Lista de adyacencia (vector de listas)
    std::vector<LinkedList<std::string>> adjList;
    // mapea IPs a un numero entero de orden
    std::map<unsigned int, ipAddress> mapIP;
    // vector de objetos ipAddress para contar los grados
    std::vector<ipAddress> ips;
    // std::priorityqueue funciona en complejidad de O(nlogN) 
    std::priority_queue<std::pair<int, std::string>> maxHeapIPs;
    std::priority_queue<std::pair<int, std::string>> heapDijkstra;
    // hash table 
    HashTable<long long int, std::string> table;
    
    void split(std::string line, std::vector<int> & res);
  
  public:
    Graph();
    ~Graph();
    // Complejidad O(n)
    void loadGraphList(std::string fileName);
    // Complejidad O(n)
    void printGraph();
    // Complejidad O(n)
    void outDegrees(std::string fileName);
    // Complejidad O(n)
    void maxDegrees(std::string fileName);
    // Complejidad O(n)
    void bootMaster();
    // Complejidad O(ELogV)
    void shortestPath();
    // Complejidad O(1)
    void menosVulnerable();
    //Complejidad O(n)
    bool validate(std::string ip);
    // Complejidad O(n^2)
    void getIPSummary();
};




#endif // __GRAPH_H_