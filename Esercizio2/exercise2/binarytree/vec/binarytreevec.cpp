
namespace lasd {

/* ************************************************************************** */

//************* MutableNode *******************************
/**********************************************************/
// Constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Vector<NodeVec*> *vec, Data &dato, ulong indice ) {
    vectorNode = vec;
    element = dato;
    iNode = indice;
    
}

// Specific member functions

template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return element;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (iNode*2+1) <= (vectorNode->Size() - 1);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
   return (iNode*2+2) <= (vectorNode->Size() - 1);
}

template <typename Data>
struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(!HasLeftChild())
        throw std::out_of_range("Access to an empty child.");

    return *(vectorNode->operator[](iNode*2+1));
}

template <typename Data>
struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(!HasRightChild())
        throw std::out_of_range("Access to an empty child.");

    return *(vectorNode->operator[](iNode*2+2));

}

//*************************BinaryTreeVec **************************************
//*****************************************************************************
//Classiche

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const MappableContainer<Data>& mp){
    // size = mp.Size();
    // treevec = new Data[capacity]{};
    // ulong index = 0;
    // mp.Map([&index, this](const auto& element){
    //     Elements[index++] = element;
    // });
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MutableMappableContainer<Data>&& mp){
    // size = mp.Size();
    // treevec = new Data[size];
    // ulong index = 0;
    // mp.Map([&index, this](Data& item) {
    //     Elements[index++] = std::move(item);
    // });
}

// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &bt) {
    size = bt.size;
    treevec = new Vector<NodeVec*>(size);
    for(uint i = 0; i < size; i++){
        NodeVec* node = new NodeVec(treevec, bt.treevec->operator[](i)->Element(),i);
        treevec->operator[](i) = node;
    }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&bt) noexcept {
    treevec = new Vector<NodeVec*>();
    std::swap(size,bt.size);
    std::swap(treevec,bt.treevec);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
    Clear();

    delete treevec;
    treevec = nullptr;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> &bt) {
    BinaryTreeVec<Data>* tmpbt = new BinaryTreeVec<Data>(bt);
	std::swap(*this,*tmpbt);
	delete tmpbt;
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> &&bt) noexcept {
    std::swap(size,bt.size);
    std::swap(treevec,bt.treevec);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> &bt) const noexcept {
   return BinaryTree<Data>::operator==(bt);
}

template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> &bt) const noexcept{
    return !(*this == bt);
}
//******************* Funzioni specifiche
 // Specific member functions (inherited from BinaryTree)
template <typename Data>
  Node& BinaryTreeVec<Data>::Root() const{
    if(size == 0)
        throw std::length_error("Albero vuoto");
    return *(treevec->operator[](0));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
template <typename Data>
  MutableNode& BinaryTreeVec<Data>::Root() const {
    if(size == 0)
        throw std::length_error("Albero vuoto");
    return *(treevec->operator[](0));
  } // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
template <typename Data>
  void BinaryTreeVec<Data>::Clear(){
    if(size > 0){
        treevec->Clear();
        size = 0;
    }
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)
template <typename Data>
  void BinaryTreeVec<Data>::BreadthFold(const FoldFunctor fun, void* par) const{
    for(ulong i = 0; i < size; i++){
        fun(treevec->operator[](i)->Element(), par);
    }
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)
template <typename Data>
  void BinaryTreeVec<Data>::BreadthMap(const MapFunctor fun) {
    for(ulong i = 0; i < size; i++){
        fun(treevec->operator[](i)->Element());
    }
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableBreadthMappableContainer)
template <typename Data>
  void BinaryTreeVec<Data>::BreadthMap(MutableMapFunctor fun){
    for(ulong i = 0; i < size; i++){
        fun(treevec->operator[](i)->Element());
    }    
  }

/* ************************************************************************** */

}
