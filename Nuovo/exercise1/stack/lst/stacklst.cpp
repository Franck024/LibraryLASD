
namespace lasd {

/* ************************************************************************** */

  // Specific constructor
  template <typename Data>
  StackLst<Data>::StackLst(const MappableContainer<Data>& mapCont) : List<Data>(mapCont){}

  template <typename Data>
  StackLst<Data>::StackLst(const MutableMappableContainer<Data>& mutMap) : List<Data>(mutMap){}

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  StackLst<Data>::StackLst(const StackLst<Data>& stk) : List<Data>(stk){}

  // Move constructor
  template <typename Data>
  StackLst<Data>::StackLst(StackLst<Data>&& stk) noexcept : List<Data>(std::move(stk)){}

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stk){
    List<Data>::operator=(stk);
    return *this;
  }

  // Move assignment
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stk) noexcept{
    List<Data>::operator=(std::move(stk));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool StackLst<Data>::operator==(const StackLst<Data>& stk) const noexcept{
    return List<Data>::operator==(stk);
  }

  template <typename Data>
  bool StackLst<Data>::operator!=(const StackLst<Data>& stk) const noexcept{
    return !(*this == stk);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)
  template <typename Data>
  Data& StackLst<Data>::Top() const {
    if(size == 0) throw std::length_error("Struttura vuota");
    return this->Front();
  } 
  
  template <typename Data>
  Data& StackLst<Data>::Top() {
    if(size == 0) throw std::length_error("Struttura vuota");
    return this->Front();    
  }

  template <typename Data>
  void StackLst<Data>::Pop() {
    if(size == 0) throw std::length_error("Struttura vuota");   
    this->RemoveFromFront(); 
  }

  template <typename Data>
  Data StackLst<Data>::TopNPop() {
    if(size == 0) throw std::length_error("Struttura vuota");
    Data val = this->FrontNRemove();
    return val;
  }

  template <typename Data>
  void StackLst<Data>::Push(const Data& val) noexcept{
    this->InsertAtFront(val);
  }

  template <typename Data>
  void StackLst<Data>::Push(Data&& val) noexcept {
    this->InsertAtFront(std::move(val));
  }

/* ************************************************************************** */

}
