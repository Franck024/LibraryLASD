
namespace lasd {

/* ************************************************************************** */

//----------NodeVec-----------------------
    template <typename Data>
    BinaryTreeVec<Data>::NodeVec<Data>::NodeVec(Data& dato, ulong index, Vector<NodeVec>* vec){
        element = dato;
        indexNode = index;
        vectorPointer = vec;
    }

    template <typename Data>
    struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec<Data>::LeftChild() const{
        if(!HasLeftChild()) throw std::out_of_range("Nessun figlio trovato");
        return *(vectorPointer->operator[](indexNode * 2 + 1));
    }

    template <typename Data>
    struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec<Data>::LeftChild(){
        if(!HasLeftChild()) throw std::out_of_range("Nessun figlio trovato");
        return *(vectorPointer->operator[](indexNode * 2 + 1));
    }

    template <typename Data>
    struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec<Data>::RightChild() const{
        if(!HasRightChild()) throw std::out_of_range("Nessun figlio trovato");
        return *(vectorPointer->operator[](indexNode * 2 + 2));
    } 

    template <typename Data>
    struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec<Data>::RightChild(){
        if(!HasRightChild()) throw std::out_of_range("Nessun figlio trovato");
        return *(vectorPointer->operator[](indexNode * 2 + 2));
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec<Data>::HasLeftChild() const noexcept{
        if((indexNode * 2 + 1) <= (vectorPointer->Size() - 1)) return true;
        return false; 
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec<Data>::HasRightChild() const noexcept{
        if((indexNode * 2 + 2) <= (vectorPointer->Size() - 1)) return true;
        return false; 
    }

//---------------------------------------
//------------BinaryTreeVec--------------

  // Specific constructors
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const MappableContainer<Data>& mp){
    treevec = new Vector<NodeVec*>;
    size = mp.size();

    if (size > 0) {
        for (ulong i = 0; i < size; ++i) {
            (*treevec)[i] = new NodeVec(container[i], i, treevec);
        }
    }
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(MutableMappableContainer<Data>&& mp) noexcept{
    treevec = new Vector<NodeVec*>;
    size = mp.size();

    if (size > 0) {
        for (ulong i = 0; i < size; ++i) {
            (*treevec)[i] = new NodeVec(std::move(container[i]), i, treevec);
        }
    }
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bt){
    BinaryTreeVec<Data>* tmp = new BinaryTreeVec<Data>(bt);
    std::swap(*tmp, *this);
    delete tmp;
  }

  // Move constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& bt) noexcept{
    std::swap(size, bt.size);
    std::swap(treevec, bt.treevec);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BinaryTreeVec<Data>::~BinaryTreeVec(){
    Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt){
    BinaryTreeVec<Data>* tmp = new BinaryTreeVec<Data>(bt);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& bt) noexcept{
    std::swap(size, bt.size);
    std::swap(treevec, bt.treevec);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& bt) const noexcept{
    return BinaryTree<Data>::operator==(bt);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  template <typename Data>
  NodeVec& BinaryTreeVec<Data>::Root() const{
    if(size==0) throw std::length_error("Albero vuoto");
    return *(treevec->operator[](0));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  template <typename Data>
  NodeVec& BinaryTreeVec<Data>::Root(){
    if(size==0) throw std::length_error("Albero vuoto");
    return *(treevec->operator[](0));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::Clear(){
    treevec.Clear();
    treevec = nullptr;
    size = 0;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::BreadthFold(const FoldFunctor fun, void* acc) const{
    for(uint i = 0; i < size; i++) 
        fun(treevec->operator[](i)->Element(), acc);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::BreadthMap(const MapFunctor fun){
    for(uint i = 0; i < size; i++) 
        fun(treevec->operator[](i)->Element());
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableBreadthMappableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::BreadthMap(MutableMapFunctor fun){
    for(uint i = 0; i < size; i++) 
        fun(treevec->operator[](i)->Element());
  }

//----------------------------------------

/* ************************************************************************** */

}
