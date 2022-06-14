#ifndef _NODE_H_
#define _NODE_H_

  template <class T>
  class StackNode { 
  public: 
      T data; 
      StackNode<T> *next;
      StackNode();
      StackNode(T val);        
  }; 

  template<class T>
  StackNode<T>::StackNode() : data{}, next{nullptr} {}
  
  template<class T>
  StackNode<T>::StackNode(T val){
      data = val;
      next = nullptr;
  }

#endif // _NODE_H_