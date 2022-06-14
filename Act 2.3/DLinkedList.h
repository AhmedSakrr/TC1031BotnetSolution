#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_
  
  #include <iostream>
  #include <stdexcept>
  #include "Registro.h"
  #include "StackedLinkedList.h"
  #include "DLLNode.h"


  template <class T>
  class DLinkedList {
      private:
        DLLNode<T> *head;
        DLLNode<T> *tail;
        int numElements;

      public:
        DLinkedList();
        ~DLinkedList();
        int getNumElements();
        void printList();
        void printLastNode();
        void addFirst(T value);
        void addLast(T value);
        bool deleteData(T value);
        bool deleteAt(int position);
        T getData(int position);
        bool clear();
        void quickSort();
        void _quickSort(DLLNode<T> *l, DLLNode<T> *h);
        DLLNode<T>* partition(DLLNode<T> *l, DLLNode<T> *h);
        void swap(T *a, T *b);
        void duplicate();
        void removeDuplicate();
        void getReversedSublist(int inicio, int fin);
        T operator[](const int position);
        void operator=(DLinkedList&other);
  };

  template<class T>
  DLinkedList<T>::DLinkedList() {
      std::cout << "--->Creando una lista vacia" << std::endl;
      head = nullptr;
      tail = nullptr;
      numElements = 0;
  }

  template<class T>
  DLinkedList<T>::~DLinkedList() {
      std::cout << "--->Liberando memoria de la lista ligada" << std::endl;
    DLLNode<T> *p, *q;
    p = head;
    while (p != nullptr) {
      q = p->next;
      delete p;
      p = q;
    }
    head = nullptr;
    tail = nullptr;
    numElements = 0;
  }

  template<class T>
  int DLinkedList<T>::getNumElements() {
    return numElements;
  }

  template<class T>
  void DLinkedList<T>::printList() {
    DLLNode<T> *ptr = head;
    while (ptr != nullptr) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
  }

  template<class T>
  void DLinkedList<T>::printLastNode() {
    std::cout << tail->data << std::endl;
  }

  template<class T>
  void DLinkedList<T>::addFirst(T value) {
    DLLNode<T> *newDLLNode = new DLLNode<T>(value);
    // Si la lista está vacia
    if (head == nullptr && tail == nullptr) {
      head = newDLLNode;
      tail = newDLLNode;
    }
    else {
      newDLLNode->next = head;
      head->prev = newDLLNode;
      head = newDLLNode;
    }
    numElements++;
  }

  template<class T>
  void DLinkedList<T>::addLast(T value) {
    if (head == nullptr && tail == nullptr) {
      addFirst(value);
    }
    else {
      DLLNode<T> *newDLLNode = new DLLNode<T>(value);
      tail->next = newDLLNode;
      newDLLNode->prev = tail; 
      tail = newDLLNode;
      numElements++;
    }
  }

  template<class T>
  bool DLinkedList<T>::deleteData(T value) {
    // Si la lista esta vacia 
    if (head == nullptr && tail == nullptr) {
      return false;
    }
    else {
      DLLNode<T> *p, *q;
      p = head;
      q = nullptr;
      // buscar value en la lista
      while (p != nullptr && p->data != value) {
        q = p;
        p = p->next;
      }
      // Si no existe value en la lista
      if (p == nullptr)
        return false;
      // Si debe borrarse el primer elemento
      if (p->prev == nullptr) {
        head = p->next;
        if (head != nullptr)
          head->prev = nullptr;
      }
      else if (p->next == nullptr) { 
        // Si debe borrarse el último elemento
        q->next = nullptr;
        tail = q;
      }
      else {
        // Cualquier otro elemento entre la lista 
        q->next = p->next;
        p->next->prev = q;
      }
      delete p;
      numElements--;
      return true;
    }
  }

  template<class T>
  bool DLinkedList<T>::deleteAt(int position) {
    if (position < 0 || position >= numElements) {
      throw std::out_of_range("Indice fuera de rango");
    }
    else if (position == 0) { // Si debe borrarse el primer elemento
      DLLNode<T> *p = head;
      // Si la lista contiene solo un nodo
      if (head != nullptr && head->next == nullptr) {
        head = tail = nullptr;  
      }
      else {
        head = p->next;
        head->prev = nullptr;
      }
      delete p;
      numElements--;
      return true; 
    }
    else { // Si la lista contiene mas de un nodo
      DLLNode<T> *p = head, *q = nullptr;
      int index = 0;
      // Se busca el indice del elemento a borrar
      while (index != position) {
        q = p;
        p = p->next;
        index++;
      }
      // Si debe borrarse el último elemento
      if (p->next == nullptr) {
        q->next = nullptr;
        tail = q;
      }
      else { // Cualquier otro elemento en medio de la lista 
        q->next = p->next;
        p->next->prev = q;
      }
      delete p;
      numElements--;
      return true;
    }
  }

  template<class T>
  T DLinkedList<T>::getData(int position) {
    if (position < 0 || position >= numElements) {
      throw std::out_of_range("Indice fuera de rango");
    }
    else {
      if (position == 0)
        return head->data;
      DLLNode<T> *p = head;
      int index = 0;
      while (p != nullptr) {
        if (index == position)
          return p->data;
        index++;
        p = p->next;
      }
      return -1;
    }
  }


  // Metodos de actividad 2.2 y 2.3

  // Funcion clear complejidad temporal: O(n)

  template<class T>
  bool DLinkedList<T>::clear(){
    DLLNode<T> *p = head;
    DLLNode<T> *q = tail;
    while(numElements != 1){
      if (head != nullptr && head->next == nullptr) {
        head = tail = nullptr;
        numElements = numElements - 1;
        return true;
      }else
        head = p->next;
        head->prev = nullptr;
        p = p->next;
        numElements = numElements - 1;
      }
  }


  // Funcion sort (quicksort) complejidad: O(n log n)


  template <class T>
  void DLinkedList<T>::swap (T * a, T * b ){ 
    T t = *a; *a = *b; *b = t; 
  }

  template <class T>
  DLLNode<T>* DLinkedList<T>::partition(DLLNode<T> *l, DLLNode<T> *h){
    // set pivot as h element
    T x = h->data;
 
    // similar to i = l-1 for array implementation
    DLLNode<T> *i = l->prev;
 
    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (DLLNode<T> *j = l; j != h; j = j->next)
    {
        if (j->data.getDate() <= x.getDate()){
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;
 
            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    swap(&(i->data), &(h->data));
    return i;
}

  template <class T>
  void DLinkedList<T>::_quickSort(DLLNode<T>* l, DLLNode<T> *h){
    if (h != NULL && l != h && l != h->next)
    {
      DLLNode<T> *p = partition(l, h);
      _quickSort(l, p->prev);
      _quickSort(p->next, h);
    }
}

  template<class T>
  void DLinkedList<T>::quickSort(){
    DLLNode<T> *p = head;
    DLLNode<T> *q = tail;
    _quickSort(p, q);
  }



  // Funcion duplicate complejidad: O(n)

  template<class T>
  void DLinkedList<T>::duplicate(){
  DLLNode<T> *p = head;
    int ctr = 0;
    int elementos = this->getNumElements();
    while (ctr < elementos){
      this->addLast(p->data);
      p = p->next;
      ctr++;
    }
  }

  // Funcion removeDuplicate complejidad: O(n)

  template<class T>
  void DLinkedList<T>::removeDuplicate(){
  DLLNode<T> *p = head;
  DLLNode<T> *q = nullptr;
  int index = 0;
  int elements = getNumElements();
  while(p != nullptr){
    if(this->getData(index) == this->getData(index + 1)){
      this->deleteAt(index);
      index++;
      p = p->next;
    }
  }
}

  // Funcion getReversedSubl complejidad: O(n)

  template<class T>
  void DLinkedList<T>::getReversedSublist(int inicio, int fin){
    DLinkedList<int> sentence;
    for (int i = inicio; i <= fin;  i++){
      sentence.addFirst(this->getData(i));
    }
    sentence.printList();
  }


 // Sobrecarga, complejidad: O(n)

template <class T>
T DLinkedList<T>::operator[](const int position){
  T valor;
  try{
    if(position < 0 || position >= numElements){
      throw std::out_of_range("Out_of_Range");
    }
    if (position == 0){
      return head->data;
      }
    DLLNode<T> *p = head;
    int index = 0;
    while (p != NULL) {
      if (index == position)
        return p->data;
      index++;
      p = p->next;
    }
    return valor;
  }catch(const std::out_of_range &oor){
      std::cerr << "Error: " << oor.what() << std::endl;
      return valor;
  }
}

  // Sobrecarga =, complejidad: O(1)

template<class T>
void DLinkedList<T>::operator=(DLinkedList<T> &other) {
  this -> clear();
  DLLNode<T> *p = other.getHead();
  while(p != NULL){//Complejidad O(n)
    this -> addLast(p->data);
    p = p->next; 
  }
}


#endif // _DLINKEDLIST_H_