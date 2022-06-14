#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include "HashNode.h"
#include "LinkedList.h"

template<class K, class T>
class HashTable {
  private:
    std::vector<HashNode<K,T>> table;
    int size;
    int maxSize; // preferible un numero primo 13999
    int totalOverFlow;

  public:
    HashTable();
    HashTable(int selectedMaxSize);
    int getHashIndex(K keyVal);
    int getSize();
    // Complejidad O(n)
    void print();
    // Complejidad O(1)
    void add(K keyVal, T value);
    // Complejidad O(n)
    int find(K keyVal);
    // Complejidad O(1)
    T getDataAt(int index);
    K getKeyAt(int index);
    int getStatusAt(int index);
    void remove(K keyVal);
    // Complejidad O(1)
    void addDegree(int KeyValIn,int KeyValOut); 
    // Complejidad O(1)
    void totalOverFlowPrint();
    // Complejidad O(1)
    void printAt(int index);

};

template<class K, class T>
HashTable<K, T>::HashTable() {
  maxSize = 0;
  size = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
  totalOverFlow=0;
}

template<class K, class T>
HashTable<K, T>::HashTable(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  size = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}

template<class K, class T>
int HashTable<K, T>::getHashIndex(K keyVal) {
  return keyVal % maxSize;
}

template<class K, class T>
int HashTable<K, T>::getSize() {
  return size;
}

// Complejidad O(n)

template<class K, class T>
void HashTable<K,T>::print() {
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    // status:  0 empty, 1 used, 2 deleted
    if (table[i].getStatus() == 1) // Cell is used
      std::cout << "Cell: " << i << " Key: " << table[i].getKey() << ", Value: " << table[i].getData() << ", Overflow.size: " << table[i].getOverflowSize() << ", Grado de entrada: "<< table[i].getIpIn() <<", Grado de salida: "<< table[i].getIpOut()<< std::endl;
  }
}

template<class K, class T>
void HashTable<K,T>::add(K keyVal, T value) {
  if (size == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  // Compute the index of the table using a key and a hash function
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() != 1) { // Cell is free
    node.setKey(keyVal);
    node.setData(value);
    table[hashVal] = node;
  }
  else { // Cell is already taken
    // Find next free space using quadratic probing
    // https://www.geeksforgeeks.org/quadratic-probing-in-hashing/
    int i = 1;
    int currentHashVal = getHashIndex(hashVal + i * i);
    HashNode<K, T> currentNode = table[currentHashVal];
    while (currentNode.getStatus() == 1) { // Cell is used
      i++;
      currentHashVal = getHashIndex(hashVal + i * i);
      currentNode = table[currentHashVal];
      totalOverFlow++;
    }
    // A free cell was found
    currentNode.setKey(keyVal);
    currentNode.setData(value);
    node.addToOverflow(currentHashVal);
    table[currentHashVal] = currentNode;
    table[hashVal] = node;
  }
  size++;
}  

// Complejidad O(n)

template<class K, class T>
int HashTable<K,T>::find(K keyVal) {
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() == 1) { // Cell is used
    if (node.getKey() == keyVal) {
      return hashVal;
    }
    for (int i = 0; i < node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table[overflowIndex].getKey() == keyVal) {
        return overflowIndex;
      }
    }
    return -1;
  }
  return -1;
}


// Complejidad O(1)
template<class K, class T>
T HashTable<K,T>::getDataAt(int index) {
  return table[index].getData();
}

template<class K, class T>
K HashTable<K,T>::getKeyAt(int index) {
  return table[index].getKey();
}

template<class K, class T>
int HashTable<K,T>::getStatusAt(int index) {
  return table[index].getStatus();
}

template<class K, class T>
void HashTable<K,T>::remove(K keyVal) {
  int pos, hashVal;
  pos = find(keyVal);
  if (pos == -1) {
    throw std::invalid_argument("Element does not exist in hash table");
  }
  hashVal = getHashIndex(keyVal);
  if (pos != hashVal) {
    HashNode<K, T> node = table[hashVal];
    node.removeFromOverflow(pos);
    table[hashVal] = node;
  }
  table[pos].clearData(); 
}

// Complejidad O(2)

template<class K, class T>
void HashTable<K,T>::addDegree(int KeyValIn,int KeyValOut) {
  table[KeyValIn].addIpIn();
  table[KeyValOut].addIpOut();
}

// Complejidad O(1)

template<class K, class T>
void HashTable<K,T>::totalOverFlowPrint() {
  std::cout<<"El total de coliciones generadas en esta hash table fueron: "<<totalOverFlow<<std::endl;
}

// Complejidad O(1)
template<class K, class T>
void HashTable<K, T>::printAt(int index){
    if (table[index].getStatus() == 1) // Cell is used
      std::cout << "Cell: " << index << " Key: " << table[index].getKey() << ", Value: " << table[index].getData() << ", Overflow.size: " << table[index].getOverflowSize() << ", Grado de entrada: "<< table[index].getIpIn() <<", Grado de salida: "<< table[index].getIpOut()<< std::endl;
}



#endif // __HASH_TABLE_H_