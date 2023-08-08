#include <climits>
#include <iostream>

namespace lasd {

/* ************************************************************************** */
  // Default constructor
  template <typename Data>
  StackVec<Data>::StackVec() :  capacity(5){ 
    size = 0;
    elem = new Data[capacity]{};
    }

  // Specific constructor
  template <typename Data>
  StackVec<Data>::StackVec(MappableContainer<Data>& map) {
    size = map.Size();
    capacity = map.Size();
    map.Map([&](const Data& item){
        Push(item);
    });
  }

  template <typename Data>
  StackVec<Data>::StackVec(MutableMappableContainer<Data>&& map)  {
    size = map.Size();
    capacity = map.Size();
    map.Map([&]( Data& item){
        Push(item);
    });
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  StackVec<Data>::StackVec(const StackVec& stk){
    size = stk.size;
    capacity = stk.capacity;
    elem = new Data[capacity];
    for(ulong i = 0; i < size; i++){
        elem[i] = stk.elem[i];
    }
  }

  // Move constructor
  template <typename Data>
  StackVec<Data>::StackVec(StackVec&& stk) noexcept{
    std::swap(size, stk.size);
    std::swap(capacity, stk.capacity);
    std::swap(elem, stk.elem);
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  StackVec<Data>& StackVec<Data>::operator=(const StackVec& stk){
    Vector<Data>::operator=(stk);
    capacity = stk.capacity;
    return *this;
  }

  // Move assignment
  template <typename Data>
  StackVec<Data>& StackVec<Data>::operator=(StackVec&& stk) noexcept{
    Vector<Data>::operator=(std::move(stk));
    capacity = stk.capacity;
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool StackVec<Data>::operator==(const StackVec& stk) const noexcept{
    if(size != stk.size) return false;
    for(ulong i = 0; i < size; i++){
        if(elem[i] != stk.elem[i]) return false;
    }
    return true;
  }

  template <typename Data>
  bool StackVec<Data>::operator!=(const StackVec& stk) const noexcept{
    return !(*this == stk);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  template <typename Data>
  Data& StackVec<Data>::Top() const {
    if (size == 0) throw std::length_error("Struttura vuota!");
    return elem[size -1];
  }

  template <typename Data>
  Data& StackVec<Data>::Top() {
    if (size == 0) throw std::length_error("Struttura vuota!");
    return elem[size -1];
  }

  template <typename Data>
  void StackVec<Data>::Pop() {
    if (size == 0) throw std::length_error("Struttura vuota!");
    ulong tmp = size;
    elem[size -1].~Data();
    if(size <= capacity / 4) Reduce(capacity / 2); // Dimezza la capac dello stack se vuoto al 24%
    size = tmp--;
  }

  template <typename Data>
  Data StackVec<Data>::TopNPop() {
    if (size == 0) throw std::length_error("Struttura vuota!");
    Data val = Top();
    Pop();
    return val;
  }

  template <typename Data>
  void StackVec<Data>::Push(const Data& dato) noexcept {
    ulong tmp = size;
    if(size == capacity) Expand(capacity * 2); // raddoppia la capac dello stack se pieno
    elem[size] = dato;
    size = tmp++;  
  }

  template <typename Data>
  void StackVec<Data>::Push(Data&& dato) noexcept {
    ulong tmp = size;
    if(size == capacity) Expand(capacity * 2); // raddoppia la capac dello stack se pieno
    elem[size] = dato;
    size = tmp++;  
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  template <typename Data>
  bool StackVec<Data>::Empty() const noexcept { return (size == 0); }

  template <typename Data>
  ulong StackVec<Data>::Size() const noexcept { return size;}

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  template <typename Data>
  void StackVec<Data>::Clear() { Vector<Data>::Clear();}



  // Auxiliary member functions

    // Espande la capacità del vector sottostante a una nuova capacità
    template <typename Data>
    void StackVec<Data>::Expand(const ulong new_capacity) noexcept{
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
    void StackVec<Data>::Reduce(const ulong new_capacity) noexcept{
    if (new_capacity > capacity) { // verifica se la nuova capacità è maggiore di quella attuale
        return;
    }        
    if( new_capacity < size)
        Vector<Data>::Resize(size);
    Vector<Data>::Resize(capacity - new_capacity);
    }


/* ************************************************************************** */

}
