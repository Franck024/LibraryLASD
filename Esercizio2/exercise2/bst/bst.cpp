
namespace lasd {

/* ************************************************************************** */
template <typename Data>
BST<Data>::BST(const MutableContainer<Data>& mp){}

template <typename Data>
BST<Data>::BST(MappableMutableContainer<Data> mp) noexcept {}

template <typename Data>
BST<Data>::BST(const BST<Data>& copy) : BinaryTreeLnk<Data>(copy){}

template <typename Data>
BST<Data>::BST(BST<Data>&& ab) : BinaryTreeLnk<Data>(std::move(ab)){}

template <typename Data>
BST<Data>::operator=(const BST<Data>& ab) : BinaryTreeLnk<Data>::operator=(ab){ return *this;}

template <typename Data>
BST<Data>::operator=(BST<Data>&& ab) noexcept : BinaryTreeLnk<Data>::operator=(std::move(ab)) { return *this;}

template <typename Data>
BST<Data>::operator==(const BST<Data>& ab) const noexcept {
  return BinaryTreeLnk<Data>::operator==(ab);  
}

template <typename Data>
BST<Data>::operator!=(const BST<Data>& ab)const noexcept{
    return !(*this == ab);
}

//--------------------- Funzioni specifiche -------------------------
//-------------------------------------------------------------------
template <typename Data>
Data BST<Data>::Min() const{
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    return (FindPointerToMin(root))->element;
}

template <typename Data>
Data BST<Data>::MinNRemove() {
  Data minValue = Min();
  Remove(minValue);
  return minValue;
}

template <typename Data>
void BST<Data>::RemoveMin(){
    if(root == nullptr)
        throw std::length_error("Vuoto");
    DetachMin();
}

template <typename Data>
Data BST<Data>::Max() const {
  if (root == nullptr)
    throw std::length_error("BST vuoto");
  return (FindPointerMax(root))->element;
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
  Data maxValue = Max();
  Remove(maxValue);
  return maxValue;
}

template <typename Data>
void BST<Data>::RemoveMax(){
    if(root == nullptr)
        throw std::length_error("Vuoto");
    DetachMax();
}

template <typename Data>
Data BST<Data>::Predecessor(const Data& value) const {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    return (FindPointerToPredecessor(root, value))->element;
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& value) {
  Data predecessorValue = Predecessor(value);
  Remove(predecessorValue);
  return predecessorValue;
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& value) {
  Remove(Predecessor(value));
}

template <typename Data>
Data BST<Data>::Successor(const Data& value) const {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    return (FindPointerToSuccessor(root, value))->element;
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& value) {
  Data successorValue = Successor(value);
  Remove(successorValue);
  return successorValue;
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& value) {
  Remove(Successor(value));
}

//****************** Funzioni di DictionaryContainer *********************
//************************************************************************

template <typename Data>
bool BST<Data>::Insert(const Data& value) {
  NodeLnk*& pointer = FindPointerTo(root, value);
  
  if (pointer != nullptr) 
    return false;
  
  pointer = new NodeLnk(value);
  size++;
  return true;
}


template <typename Data>
bool BST<Data>::Insert(Data&& value) noexcept {
  NodeLnk*& pointer = FindPointerTo(root, value);
  
  if (pointer != nullptr) 
    return false;
  
  pointer = new NodeLnk(std::move(value));
  size++;
  return true;
}



template <typename Data>
bool BST<Data>::Remove(const Data& value) {
  NodeLnk*& pointer = FindPointerTo(root, value);

  if (pointer == nullptr)
    return false;

  Detach(pointer);
  delete pointer;
  pointer = nullptr;
  size--;
  return true;
}


//****************** Funzioni di TestableContainer *********************
//************************************************************************

template <typename Data>
bool BST<Data>::Exist(const Data& value) const {
  NodeLnk* pointer = FindPointerTo(root, value);
  if (pointer == nullptr)
    return false;
  return true;
}


//****************** Funzioni di ClearableContainer *********************
//************************************************************************

template <typename Data>
void BST<Data>::Clear() {
  clear(root);
  root = nullptr;
  size = 0;
}

// Recursive helper function to clear the tree
template <typename Data>
void BST<Data>::clear(NodeLnk<Data>* node) {
  if (node == nullptr) {
    return;
  }

  clear(node->leftChild);
  clear(node->rightChild);
  delete node;
}

//****************** Funzioni ausiliari *********************
//***********************************************************
template <typename Data>
Data BST<Data>::DataNRemove(NodeLnk<Data>*& node) {
  if (node == nullptr) {
    throw std::length_error("NodeLnk not found");
  }

  Data deletedData = node->element;

  // Case 1: NodeLnk has no children
  if (node->leftChild == nullptr && node->rightChild == nullptr) {
    delete node;
    node = nullptr;
  }
  // Case 2: NodeLnk has one child
  else if (node->leftChild == nullptr) {
    NodeLnk<Data>* temp = node;
    node = node->rightChild;
    delete temp;
  } else if (node->rightChild == nullptr) {
    NodeLnk<Data>* temp = node;
    node = node->leftChild;
    delete temp;
  }
  // Case 3: NodeLnk has two children
  else {
    NodeLnk<Data>* successor = Successor(node);
    node->element = successor->element;
    DataNRemove(successor);
  }

  size--;
  return deletedData;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(typename BST<Data>::NodeLnk*& node) noexcept {  // per staccare il nodo
  if (node == nullptr) {
    return nullptr;
  }

  NodeLnk* detachedNodeLnk = node;
  node = nullptr;
  return detachedNodeLnk;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(typename BST<Data>::NodeLnk*& node) noexcept {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->leftChild != nullptr) {
    return DetachMin(node->leftChild);
  } else {
    NodeLnk* detachedNodeLnk = node;
    node = node->rightChild;
    detachedNodeLnk->rightChild = nullptr;
    return detachedNodeLnk;
  }
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(typename BST<Data>::NodeLnk*& node) noexcept {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->rightChild != nullptr) {
    return DetachMax(node->rightChild);
  } else {
    NodeLnk* detachedNodeLnk = node;
    node = node->leftChild;
    detachedNodeLnk->leftChild = nullptr;
    return detachedNodeLnk;
  }
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(typename BST<Data>::NodeLnk*& node) noexcept {
  if (node == nullptr || node->leftChild == nullptr) {
    return nullptr;
  }

  return node->leftChild->leftChild;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(typename BST<Data>::NodeLnk*& node) noexcept {
  if (node == nullptr || node->rightChild == nullptr) {
    return nullptr;
  }

  return node->rightChild->rightChild;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk*& node) noexcept {
  if (node == nullptr || node->leftChild == nullptr) {
    return node;
  }

  return FindPointerToMin(node->leftChild);
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk* const& node) const noexcept {
  if (node == nullptr || node->leftChild == nullptr) {
    return const_cast<typename BST<Data>::NodeLnk*>(node);
  }

  return FindPointerToMin(node->leftChild);
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk*& node) noexcept {
  if (node == nullptr || node->rightChild == nullptr) {
    return node;
  }

  return FindPointerToMax(node->rightChild);
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk* const& node) const noexcept {
  if (node == nullptr || node->rightChild == nullptr) {
    return const_cast<typename BST<Data>::NodeLnk*>(node);
  }

  return FindPointerToMax(node->rightChild);
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk*& node, const Data& value) noexcept {
  if (node == nullptr || node->element == value) {
    return node;
  }

  if (value < node->element) {
    return FindPointerTo(node->leftChild, value);
  } else {
    return FindPointerTo(node->rightChild, value);
  }
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk* const& node, const Data& value) const noexcept {
  if (node == nullptr || node->element == value) {
    return const_cast<typename BST<Data>::NodeLnk*>(node);
  }

  if (value < node->element) {
    return FindPointerTo(node->leftChild, value);
  } else {
    return FindPointerTo(node->rightChild, value);
  }
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk*& node, const Data& value) noexcept {
  if (node == nullptr || node->element == value) {
    return node;
  }

  if (value < node->element) {
    return FindPointerToPredecessor(node->leftChild, value);
  } else {
    return FindPointerToPredecessor(node->rightChild, value);
  }
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk* const& node, const Data& value) const noexcept {
  if (node == nullptr || node->element == value) {
    return const_cast<typename BST<Data>::NodeLnk*>(node);
  }

  if (value < node->element) {
    return FindPointerToPredecessor(node->leftChild, value);
  } else {
    return FindPointerToPredecessor(node->rightChild, value);
  }
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk*& node, const Data& value) noexcept {
  if (node == nullptr || node->element == value) {
    return node;
  }

  if (value < node->element) {
    return FindPointerToSuccessor(node->leftChild, value);
  } else {
    return FindPointerToSuccessor(node->rightChild, value);
  }
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk* const& node, const Data& value) const noexcept {
  if (node == nullptr || node->element == value) {
    return const_cast<typename BST<Data>::NodeLnk*>(node);
  }

  if (value < node->element) {
    return FindPointerToSuccessor(node->leftChild, value);
  } else {
    return FindPointerToSuccessor(node->rightChild, value);
  }
}


/* ************************************************************************** */

}
