#ifndef _STACKLINKEDLIST_H_
#define _STACKLINKEDLIST_H_

  #include<iostream>
  #include <stdexcept>
  #include "StackNode.h"

  template <class T>
  class StackLinkedList {
      private:
        StackNode<T> *top;
        int numElements;

      public:
        StackLinkedList();
        ~StackLinkedList();
        int getNumElements();
        void print();
        void push(T value);
        void pop();
        T getTop();
        bool isEmpty();
  };

  template<class T>
  StackLinkedList<T>::StackLinkedList() {
      std::cout << "--->Creando un stack vacio" << std::endl;
      top = nullptr;
      numElements = 0;
  }

  template<class T>
  StackLinkedList<T>::~StackLinkedList() {
      std::cout << "--->Liberando memoria del stack" << std::endl;
    StackNode<T> *p, *q;
    p = top;
    while (p != nullptr) {
      q = p->next;
      delete p;
      p = q;
    }
    top = nullptr;
    numElements = 0;
  }

  template<class T>
  int StackLinkedList<T>::getNumElements() {
    return numElements;
  }

  template<class T>
  void StackLinkedList<T>::print() {
    StackNode<T> *ptr = top;
    while (ptr != nullptr) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
  }

  template<class T>
  void StackLinkedList<T>::push(T value) {
    StackNode<T> *newStackNode = new StackNode<T>(value);
    newStackNode->next = top;
    top = newStackNode;
    numElements++;    
  }

  template<class T>
  void StackLinkedList<T>::pop() {
    if (top != nullptr) {
      StackNode<T> *p = top;
      top = p->next;
      delete p;
      numElements--;
    }
  }

  template<class T>
  T StackLinkedList<T>::getTop() {
    T value= {};
    if (top != nullptr) {
      value = top->data;
    }
    return value; 
  }

  template<class T>
  bool StackLinkedList<T>::isEmpty() {
    return (top==nullptr);
  }
    
  

#endif // _STACKLINKEDLIST_H_