#include <climits>
#include <iostream>

namespace lasd {

/* ************************************************************************** */
  // Default constructor
  template <typename Data>
  StackVec<Data>::StackVec() { 
    size = 5;
    elem = new Data[size];
    capacity = 0;
    }

  // Specific constructor
  template <typename Data>
  StackVec<Data>::StackVec(MappableContainer<Data>& map) : Vector<Data>(map) {
    capacity = map.Size();
    Vector<Data>::Resize(map.Size()*2);
  }

  template <typename Data>
  StackVec<Data>::StackVec(MutableMappableContainer<Data>&& map) : Vector<Data>(std::move(map)) {
    capacity = map.Size();
    Vector<Data>::Resize(map.Size()*2);
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  StackVec<Data>::StackVec(const StackVec& stk) : Vector<Data>(stk){
    capacity = stk.capacity;
  }

  // Move constructor
  template <typename Data>
  StackVec<Data>::StackVec(StackVec&& stk) noexcept{
    std::swap(size, stk.size);
    elem = new Data[size];
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
    if(capacity != stk.capacity) return false;
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
    if (Size() == 0) throw std::length_error("Struttura vuota!");
    return elem[capacity -1];
  }

  template <typename Data>
  Data& StackVec<Data>::Top() {
    if (Size() == 0) throw std::length_error("Struttura vuota!");
    return elem[capacity -1];
  }

  template <typename Data>
  void StackVec<Data>::Pop() {
    if (Size() == 0) throw std::length_error("Struttura vuota!");
    elem[capacity - 1].~Data();
    capacity--;
    if(capacity <= size / 4) Reduce(size / 2); // Dimezza la capac dello stack se vuoto al 24%
  }

  template <typename Data>
  Data StackVec<Data>::TopNPop() {
    if (Size() == 0) throw std::length_error("Struttura vuota!");
    Data val = Top();
    Pop();
    return val;
  }

  template <typename Data>
  void StackVec<Data>::Push(const Data& dato) noexcept {
    if(Size() == capacity) Expand(size * 2); // raddoppia la capac dello stack se pieno
    elem[capacity] = dato;
    capacity++;  
  }

  template <typename Data>
  void StackVec<Data>::Push(Data&& dato) noexcept {
    if(Size() == capacity) Expand(size * 2); // raddoppia la capac dello stack se pieno
    elem[capacity] = std::move(dato);
    capacity++;  
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  template <typename Data>
  bool StackVec<Data>::Empty() const noexcept { return (capacity == 0); }

  template <typename Data>
  ulong StackVec<Data>::Size() const noexcept { return capacity;}

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  template <typename Data>
  void StackVec<Data>::Clear() { 
    Vector<Data>::Clear();
    capacity = 0;
  }



  // Auxiliary member functions

    // Espande la capacità del vector sottostante a una nuova capacità
    template <typename Data>
    void StackVec<Data>::Expand(const ulong new_capacity) noexcept{
    if (new_capacity < size) { // verifica se la nuova capacità è maggiore di quella attuale
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
    if (new_capacity > size) { // verifica se la nuova capacità è maggiore di quella attuale
        return;
    }        
    if( new_capacity < size)
        Vector<Data>::Resize(new_capacity);
    }


/* ************************************************************************** */

}
