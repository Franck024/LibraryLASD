
namespace lasd {

/* ************************************************************************** */

  // Specific constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(MappableContainer<Data>& mapCon) : List<Data>(mapCon) {}

  template <typename Data>
  QueueLst<Data>::QueueLst(MutableMappableContainer<Data>&& mutMap) : List<Data>(mutMap){}

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(const QueueLst<Data>& que) : List<Data>(que){}

  // Move constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(QueueLst<Data>&& que) noexcept : List<Data>(std::move(que)){}

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& que){
    List<Data>::operator=(que);
    return *this;
  }

  // Move assignment
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& que) noexcept{
    List<Data>::operator=(std::move(que));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool QueueLst<Data>::operator==(const QueueLst<Data>& que) const noexcept{
    return List<Data>::operator==(que);
  }

  template <typename Data>
  bool QueueLst<Data>::operator!=(const QueueLst<Data>& que) const noexcept{
    return !(*this == que);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)
  template <typename Data>
  Data& QueueLst<Data>::Head() const {
    if (List<Data>::Empty()) 
        throw std::length_error("Coda vuota");
    return List<Data>::Front();    
  }
 
  template <typename Data>
  Data& QueueLst<Data>::Head()  {
    if (List<Data>::Empty()) 
        throw std::length_error("Coda vuota");
    return List<Data>::Front();    
  }

  template <typename Data>
  void QueueLst<Data>::Dequeue() {
    if (List<Data>::Empty()) 
        throw std::length_error("Coda vuota");
        List<Data>::RemoveFromFront();
  }

  template <typename Data>
  Data QueueLst<Data>::HeadNDequeue() {
    if (List<Data>::Empty()) 
        throw std::length_error("Coda vuota");
        Data val = Head();
        List<Data>::RemoveFromFront();  
        return val;  
  }

  template <typename Data>
  void QueueLst<Data>::Enqueue(const Data& dato) {
    List<Data>::InsertAtBack(dato);
  }

  template <typename Data>
  void QueueLst<Data>::Enqueue(Data&& dato) noexcept{
    List<Data>::InsertAtBack(std::move(dato));
  }

/* ************************************************************************** */

}
