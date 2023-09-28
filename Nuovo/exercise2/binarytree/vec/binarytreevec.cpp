
namespace lasd {

/* ************************************************************************** */

//----------NodeVec-----------------------
    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(Data& dato, ulong index, Vector<NodeVec*>* vec){
        element = dato;
        indexNode = index;
        vectorPointer = vec;
    }

    template <typename Data>
    struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const{
        if(!HasLeftChild()) throw std::out_of_range("Nessun figlio trovato");
        return *(vectorPointer->operator[](indexNode * 2 + 1));
    }

    template <typename Data>
    struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild(){
        if(!HasLeftChild()) throw std::out_of_range("Nessun figlio trovato");
        return *(vectorPointer->operator[](indexNode * 2 + 1));
    }

    template <typename Data>
    struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const{
        if(!HasRightChild()) throw std::out_of_range("Nessun figlio trovato");
        return *(vectorPointer->operator[](indexNode * 2 + 2));
    } 

    template <typename Data>
    struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild(){
        if(!HasRightChild()) throw std::out_of_range("Nessun figlio trovato");
        return *(vectorPointer->operator[](indexNode * 2 + 2));
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
        if((indexNode * 2 + 1) <= (vectorPointer->Size() - 1)) return true;
        return false; 
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
        if((indexNode * 2 + 2) <= (vectorPointer->Size() - 1)) return true;
        return false; 
    }


//---------------------------------------
//------------BinaryTreeVec--------------

  // Specific constructors
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const MappableContainer<Data>& mp){  
      size = mp.Size();
      treevec = new Vector<NodeVec*>(size); 
      uint i = 0;
      mp.Map([&](const Data& item){  
        NodeVec* newNode = new NodeVec(const_cast<Data&>(item), i, treevec);    
        treevec->operator[](i) = newNode;
        i++;
      });   
    
  } 

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(MutableMappableContainer<Data>&& mp) noexcept{
    size = mp.Size();
    treevec = new Vector<NodeVec*>(size);
    if (size > 0) {
        for (ulong i = 0; i < size; ++i) {
            (*treevec)[i] = new NodeVec(std::move(mp[i]), i, treevec);
        }
    }
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bt){
    size = bt.size;
    treevec = new Vector<NodeVec*>(size);
    for(uint i = 0; i < size; i++){
      NodeVec* node = new NodeVec(bt.treevec->operator[](i)->Element(), i, treevec);
      treevec->operator[](i) = node;
    }
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
    delete treevec;
    treevec = nullptr;
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt){
    size = bt.size;
    treevec = new Vector<NodeVec*>(size);
    for(uint i = 0; i < size; i++){
      NodeVec* node = new NodeVec(bt.treevec->operator[](i)->Element(), i, treevec);
      treevec->operator[](i) = node;
    }
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
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
    if(size==0) throw std::length_error("Albero vuoto");
    return *(treevec->operator[](0));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root(){
    if(size==0) throw std::length_error("Albero vuoto");
    return *(treevec->operator[](0));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::Clear(){
    for( uint i = 0 ; i < size; i++){
      delete (*treevec)[i];
    }
    treevec->Clear();
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
  void BinaryTreeVec<Data>::BreadthMap( MapFunctor fun)const{
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
//-----per non rendere la classe astratta-----------
template <typename Data>
void BinaryTreeVec<Data>::PreOrderFold(const FoldFunctor fun, void* acc) const{
  if (size != 0) PreOrderFold(fun, acc, &(Root()));
}

template <typename Data>
void BinaryTreeVec<Data>::PreOrderFold(const FoldFunctor fun, void* acc, NodeVec* node) const {
    if(node != nullptr){
        fun(node->Element(), acc);

        if(node->HasLeftChild())
            PreOrderFold(fun, acc, &(node->LeftChild()));

        if(node->HasRightChild())
            PreOrderFold(fun, acc, &(node->RightChild()));
    }
}

template <typename Data>
void BinaryTreeVec<Data>::PostOrderFold(const FoldFunctor fun, void* acc) const {
  if (size != 0) PostOrderFold(fun, acc, &(Root()));
}

template <typename Data>
void BinaryTreeVec<Data>::PostOrderFold(const FoldFunctor fun, void* acc, NodeVec* node) const {
    if(node != nullptr){
        if(node->HasLeftChild())
            PostOrderFold(fun, acc, &(node->LeftChild()));

        if(node->HasRightChild())
            PostOrderFold(fun, acc, &(node->RightChild()));

        fun(node->Element(), acc);
    }
}

template <typename Data>
void BinaryTreeVec<Data>::InOrderFold(const FoldFunctor fun, void* acc) const {
  if (size != 0) InOrderFold(fun, acc, &(Root()));
}

template <typename Data>
void BinaryTreeVec<Data>::InOrderFold(const FoldFunctor fun, void* acc, NodeVec* node) const {
    if(node != nullptr){
        if(node->HasLeftChild())
            InOrderFold(fun, acc, &(node->LeftChild()));

        fun(node->Element(), acc);

        if(node->HasRightChild())
            InOrderFold(fun, acc, &(node->RightChild()));
    } 
}

//--------------------------------------------------

/* ************************************************************************** */

}
