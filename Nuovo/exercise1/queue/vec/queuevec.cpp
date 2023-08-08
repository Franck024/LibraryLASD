
#include <climits>
#include <iostream>
namespace lasd {

/* ************************************************************************** */

  // Default constructor
  template <typename Data>
  QueueVec<Data>::QueueVec() { 
    size = 5;
    elem = new Data[size]{}; 
    }

  // Specific constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(MappableContainer<Data>& mapCon) : Vector<Data>(mapCon){}

  template <typename Data>
  QueueVec<Data>::QueueVec(MutableMappableContainer<Data>&& mutMap) : Vector<Data>(mutMap){}

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec<Data>& que) {
    front = que.front;
    rear = que.rear;
    size = que.size;
    elem = new Data[size];
    for(ulong i = 0; i < size; i++){
        elem[i] = que.elem[i];
    }
  }

  // Move constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec<Data>&& que) noexcept{
    std::swap(front, que.front);
    std::swap(rear, que.rear);
    std::swap(size, que.size);
    std::swap(elem, que.elem);
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& que){
    Vector<Data>::operator=(que);
    front = que.front;
    rear = que.rear;
    return *this;
  }

  // Move assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& que){
    Vector<Data>::operator=(std::move(que));
    std::swap(front, que.front);
    std::swap(rear, que.rear);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool QueueVec<Data>::operator==(const QueueVec<Data>& que) const noexcept{
    if(Size() != que.Size()) return false;
    // for(ulong i = 0; i < size; i++){
    //     if(elem[i] != que.elem[i]) return false;
    // }
    ulong i = front;
    ulong j = rear;
    ulong k = que.front;
    while(i != j){
      if(elem[i] != que.elem[k]) return false;
      i = (i + 1 ) % size;
      k = (k + 1) % que.size;
    }

    return true;
  }

  template <typename Data>
  bool QueueVec<Data>::operator!=(const QueueVec<Data>& que) const noexcept{
    return !(*this == que);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  template <typename Data>
  Data& QueueVec<Data>::Head() const{
    if(Size() == 0) throw std::length_error("Struttura vuota!");
    return elem[front];
  } 

  template <typename Data>
  Data& QueueVec<Data>::Head(){
    if(Size() == 0) throw std::length_error("Struttura vuota!");
    return elem[front];
  } 

  template <typename Data>
  void QueueVec<Data>::Dequeue(){
    if(Size() == 0) throw std::length_error("Struttura vuota!");
    // for(ulong i = 0; i < size - 1; i++){
    //     elem[i] = elem[i+1];
    // }
    // elem[size--].~Data();
    // size--;
    // ulong tmp = size;
    // if(size <= capacity / 4)
    //     Reduce(capacity / 2);
    // size = tmp;
    front = (front + 1) % size;
    if(Size() == (size / 4) ) Reduce(  );
  } 

  template <typename Data>
  Data QueueVec<Data>::HeadNDequeue(){
    if(Size() == 0) throw std::length_error("Struttura vuota!");
    Data val = Head();
    Dequeue();
    return val;    
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(const Data& dato) {
    // if(size == capacity) Expand(capacity * 2);
    // elem[tmp] = dato;
    // size = ++tmp;
    if( (rear+2 % size) != front)  Expand();
    rear = (rear+1) % size;
    elem[rear] = dato;
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(Data&& dato) noexcept {
    // ulong tmp = size;
    // if(size == capacity) Expand(capacity * 2);
    // elem[tmp] = std::move(dato);
    // size = ++tmp;
    if( (rear+2 % size) != front)  Expand();
    rear = (rear+1) % size;
    elem[rear] = std::move(dato);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  template <typename Data>
  bool QueueVec<Data>::Empty() const noexcept{
    return (Size() == 0);
  }

  template <typename Data>
  ulong QueueVec<Data>::Size() const noexcept{
    return ((rear + size) - front + 1) % size;
  }

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  template <typename Data>
  void QueueVec<Data>::Clear(){
    Vector<Data>::Clear();
  }

  // Auxiliary member functions

    // Espande la capacità del vector sottostante a una nuova capacità
    template <typename Data>
    void QueueVec<Data>::Expand() noexcept{
      SwapVectors(size * 2);
    }

    // Riduce la capacità del vector sottostante al numero di elementi presenti
    template <typename Data>
    void QueueVec<Data>::Reduce() noexcept{
      SwapVectors(size - (size / 4));
    }

    template <typename Data>
    void QueueVec<Data>::SwapVectors(ulong newSize){
      Data *tmp = new Data[newSize] {};
      uint c = 1;

      uint i = front-1;
      uint j = rear;

      while(i!=j){
          i = (i+1) % size;
          tmp[c]=elem[i];
          c++;
      }
      std::swap(elem, tmp);
      front = 1;
      rear = c;
      size = newSize;

      delete[] tmp;
    }

/* ************************************************************************** */

}
