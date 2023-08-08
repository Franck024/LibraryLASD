
#include <climits>
#include <iostream>
namespace lasd {

/* ************************************************************************** */

  // Default constructor
  template <typename Data>
  QueueVec<Data>::QueueVec() :  capacity(5){ 
    size = 0;
    elem = new Data[capacity]{}; 
    }

  // Specific constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const MappableContainer<Data>& mapCon) : List<Data>(mapCon){}

  template <typename Data>
  QueueVec<Data>::QueueVec(const MutableMappableContainer<Data>& mutMap) : List<Data>(mutMap){}

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec<Data>& que) {
    capacity = que.capacity;
    size = que.size;
    elem = new Data[capacity]{};
    for(ulong i = 0; i < size; i++){
        elem[i] = que.elem[i];
    }
  }

  // Move constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec<Data>&& que) noexcept{
    std::swap(capacity, que.capacity);
    std::swap(size, que.size);
    std::swap(elem, que.elem);
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& que){
    Vector<Data>::operator=(que);
    return *this;
  }

  // Move assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& que){
    Vector<Data>::operator=(std::move(que));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool QueueVec<Data>::operator==(const QueueVec<Data>& que) const noexcept{
    if(size != que.size) return false;
    for(ulong i = 0; i < size; i++){
        if(elem[i] != que.elem[i]) return false;
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
    if(size == 0) throw std::length_error("Struttura vuota!");
    return elem[0];
  } 

  template <typename Data>
  Data& QueueVec<Data>::Head(){
    if(size == 0) throw std::length_error("Struttura vuota!");
    return elem[0];
  } 

  template <typename Data>
  void QueueVec<Data>::Dequeue(){
    if(size == 0) throw std::length_error("Struttura vuota!");
    for(ulong i = 0; i < size - 1; i++){
        elem[i] = elem[i+1];
    }
    elem[size--].~Data();
    size--;
    ulong tmp = size;
    if(size <= capacity / 4)
        Reduce(capacity / 2);
    size = tmp;
  } 

  template <typename Data>
  Data QueueVec<Data>::HeadNDequeue(){
    if(size == 0) throw std::length_error("Struttura vuota!");
    Data val = elem[0];
    Dequeue();
    return val;    
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(const Data& dato) {
    ulong tmp = size;
    if(size == capacity) Expand(capacity * 2);
    elem[tmp] = dato;
    size = ++tmp;
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(Data&& dato) noexcept {
    ulong tmp = size;
    if(size == capacity) Expand(capacity * 2);
    elem[tmp] = std::move(dato);
    size = ++tmp;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  template <typename Data>
  bool QueueVec<Data>::Empty() const noexcept{
    return (size == 0);
  }

  template <typename Data>
  ulong QueueVec<Data>::Size() const noexcept{
    return size;
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
    void QueueVec<Data>::Expand(const ulong new_capacity){
        if (new_capacity < capacity) { // verifica se la nuova capacità è maggiore di quella attuale
            return;
        }
        if(new_capacity > ULONG_MAX - sizeof(Data)) {
            Vector<Data>::Resize(ULONG_MAX - sizeof(Data));
        }
        else
            Vector<Data>::Resize(new_capacity);
    }

    // Riduce la capacità del vector sottostante al numero di elementi presenti
    template <typename Data>
    void QueueVec<Data>::Reduce(const ulong new_capacity){
        if( new_capacity < size)
            Vector<Data>::Resize(size);
        if (new_capacity > capacity) { // verifica se la nuova capacità è maggiore di quella attuale
            throw std::length_error("Nuova capacità maggiore alla capacità attuale");
        }    
        Vector<Data>::Resize(capacity - new_capacity);
    }

  template <typename Data>
  void QueueVec<Data>::SwapVectors(QueueVec<Data>& que){
    std::swap(size, que.size);
    std::swap(capacity, que.capacity);
    std::swap(elem, que.elem);
  }

/* ************************************************************************** */

}
