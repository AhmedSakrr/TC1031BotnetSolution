#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

  #include <vector>
  #include <iostream>
  #include <stdexcept>

  template<class T>
  class MaxHeap {
    private:
      // contiene los elementos del heap
      std::vector<T> data; 
      // capacidad maxima del heap
      int maxSize;
      // tamaño actual del heap   
      int size;   
      int parent(int i);
      int left(int i);
      int right(int i);

    public:
      MaxHeap();
      MaxHeap(int capacity);
      ~MaxHeap();
      bool isEmpty();
      int getCapacity();
      void setCapacity(int n);
      void printMaxHeap();
      void push(T key);
      void heapify(int size, int i);
      void heapSort(int n);
      T top();
      void pop();
      int getSize();


  };


  template <class T> 
  MaxHeap<T>::MaxHeap() {
    size = 0;
    maxSize = 0;
  }

//Complejidad O(1)
  template <class T> 
  MaxHeap<T>::MaxHeap(int capacity) {
      std::cout << "--->Creando un MaxHeap: " <<  this << std::endl;
      size = 0;
      maxSize = capacity;
      data.resize(maxSize);
  }
//Complejidad O(1)
  template <class T> 
  MaxHeap<T>::~MaxHeap() {
      std::cout << "--->Liberando memoria del MaxHeap: " <<  this << std::endl;
      data.clear();
  }

  //Complejidad O(1)
  template <class T> 
  void MaxHeap<T>::setCapacity(int cap) {
    maxSize = cap;
    data.resize(maxSize);
  }

  //Complejidad O(1)
  template <class T> 
  bool MaxHeap<T>::isEmpty() {
    return (size <= 0);
  }

//Complejidad O(1)
  template <class T> 
  int MaxHeap<T>::getCapacity() {
    return maxSize;
  }
//Complejidad O(1)
  template <class T> 
  void MaxHeap<T>::printMaxHeap() {
    for (int i=0; i < size; i++)
      std::cout << data[i] << " ";
    std::cout << std::endl;
  }
//Complejidad O(1)
  template <class T> 
  int MaxHeap<T>::parent(int i) {
    return (i-1)/2; 
  }
  //Complejidad O(1)
  template <class T> 
  int MaxHeap<T>::left(int i) {
    return (2*i + 1); 
  }
//Complejidad O(1)
  template <class T> 
  int MaxHeap<T>::right(int i) {
    return (2*i + 2);
  }

  // Codigo conseguido y adaptado de: https://www.geeksforgeeks.org/building-heap-from-array/ pendiente

//Complejidad O(n log n)
  template<class T>
  void MaxHeap<T>::heapify(int size, int i)
{
    int largest = i; // Inicializar el más grande como root

    int l = this->left(i);
    int r = this->left(i);
 
    // If left child is larger than root
    if (l < size && data[l] > data[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < size && data[r] > data[largest])
        largest = r;
 
    // Si la más grande no es root

    if (largest != i) {
        std::swap(data[i], data[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(size, largest);
    }
}

  template<class T>
  void MaxHeap<T>::heapSort(int n)
  {
      // Build heap (rearrange array)
      for (int i = n / 2 - 1; i >= 0; i--)
          heapify(n, i);
   
      // One by one extract an element from heap
      for (int i = n - 1; i > 0; i--) {
          // Move current root to end
          std::swap(data[0], data[i]);
   
          // call max heapify on the reduced heap
          heapify(i, 0);
      }
  }
 
//Complejidad O(n)
  template <class T> 
  void MaxHeap<T>::push(T key) {
    std::cout << size << std::endl;
    std::cout << maxSize << std::endl;
    if (size == maxSize) {
      throw std::out_of_range("Overflow: no se puede insertar la llave: ");
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)] < data[i]) {
       std::swap(data[i], data[parent(i)]);
       i = parent(i);
    }
  }


//Complejidad O(1)
template <class T> 
T MaxHeap<T>::top() {
  T error;
  if (isEmpty()) {
      std::cout << "Tu heap esta vacio." << std::endl;
      return error;
  }else
  return data[0];
}

//Complejidad O(n)
  template <class T> 
  void MaxHeap<T>::pop() {
    std::swap(data[0], data[size - 1]);
    heapify(size - 1, 0);
    size --;
  }

//Complejidad O(1)
  template <class T> 
  int MaxHeap<T>::getSize() {
    return size;
  }

#endif // __MAXHEAP_H_