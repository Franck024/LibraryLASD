
namespace lasd {

/* ************************************************************************** */
template <typename Data>
BST<Data>::BST(const MutableContainer<Data>& mp){}

xxx
BST<Data>::BST(MappableMutableContainer<Data> mp) noexcept {}

xxx
BST<Data>::BST(const BST<Data>& copy) : BinaryTreeLnk<Data>(copy){}

xxx
BST<Data>::BST(BST<Data>&& ab) : BinaryTreeLnk<Data>(std::move(ab)){}

xxx
BST<Data>::operator=(const BST<Data>& ab) : BinaryTreeLnk<Data>::operator=(ab){ return *this;}

xxx
BST<Data>::operator=(BST<Data>&& ab) noexcept : BinaryTreeLnk<Data>::operator=(std::move(ab)) { return *this;}

xxx
BST<Data>::operator==(const BST<Data>& ab) const noexcept {
  return BinaryTreeLnk<Data>::operator==(ab);  
}

xxx
BST<Data>::operator!=(const BST<Data>& ab)const noexcept{
    return !(*this == ab);
}

//--------------------- Funzioni specifiche -------------------------
//-------------------------------------------------------------------
xxx
Data BST<Data>::Min() const{
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    NodeLnkLnk<Data>* curr = root;
    while( curr->leftChild != nullptr){
        curr = curr->leftChild;
    }
    return curr->element;
}

template <typename Data>
Data BST<Data>::MinNRemove() {
    if(root == nullptr)
        throw std::length_error("Vuoto");
  Data minValue = Min();
  DataNRemove(root, minValue);
  return minValue;
}

template <typename Data>
Data BST<Data>::Max() const {
  if (root == nullptr)
    throw std::length_error("BST is empty");

  NodeLnk<Data>* current = root;
  while (current->rightChild != nullptr) {
    current = current->rightChild;
  }

  return current->element;
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
    if(root == nullptr)
        throw std::length_error("Vuoto");
  Data maxValue = Max();
  DataNRemove(root, maxValue);
  return maxValue;
}

template <typename Data>
Data BST<Data>::Predecessor(const Data& value) const {
  NodeLnk<Data>* current = root;
  NodeLnk<Data>* predecessor = nullptr;

  // Search for the node with the given value
  while (current != nullptr && current->element != value) {
    if (value < current->element) {
      current = current->leftChild;
    } else {
      predecessor = current;
      current = current->rightChild;
    }
  }

  if (current == nullptr) {
    throw std::length_error("NodeLnk not found");
  }

  if (current->leftChild != nullptr) {
    // If the current node has a leftChild child, find the maximum value in its leftChild subtree
    current = current->leftChild;
    while (current->rightChild != nullptr) {
      current = current->rightChild;
    }
    return current->element;
  } else if (predecessor != nullptr) {
    // If the current node doesn't have a leftChild child, return its predecessor
    return predecessor->element;
  } else {
    // There is no predecessor for the root node
    throw std::length_error("Predecessor not found");
  }
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& value) {
  Data predecessorValue = Predecessor(value);
  Remove(predecessorValue);
  return predecessorValue;
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& value) {
  Data predecessorValue = Predecessor(value);
  Remove(predecessorValue);
}

template <typename Data>
Data BST<Data>::Successor(const Data& value) const {
  NodeLnk<Data>* current = root;
  NodeLnk<Data>* successor = nullptr;

  // Search for the node with the given value
  while (current != nullptr && current->element != value) {
    if (value < current->element) {
      successor = current;
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }

  if (current == nullptr) {
    throw std::length_error("NodeLnk not found");
  }

  if (current->rightChild != nullptr) {
    // If the current node has a rightChild child, find the minimum value in its rightChild subtree
    current = current->rightChild;
    while (current->leftChild != nullptr) {
      current = current->leftChild;
    }
    return current->element;
  } else if (successor != nullptr) {
    // If the current node doesn't have a rightChild child, return its successor
    return successor->element;
  } else {
    // There is no successor for the root node
    throw std::length_error("Successor not found");
  }
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& value) {
  Data successorValue = Successor(value);
  Remove(successorValue);
  return successorValue;
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& value) {
  Data successorValue = Successor(value);
  Remove(successorValue);
}

//****************** Funzioni di DictionaryContainer *********************
//************************************************************************

template <typename Data>
bool BST<Data>::Insert(const Data& value) {
  if (root == nullptr) {
    root = new NodeLnk<Data>(value);
    size++;
    return true;
  }

  NodeLnk<Data>* current = root;
  NodeLnk<Data>* parent = nullptr;

  // Trova la posizione del nuovo nodo
  while (current != nullptr) {
    parent = current;
    if (value == current->element) {
      // Value already exists in the tree, cannot insert duplicate
      return false;
    } else if (value < current->element) {
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }

  // Create a new node and link it to the parent
  if (value < parent->element) {
    parent->leftChild = new NodeLnk<Data>(value);
  } else {
    parent->rightChild = new NodeLnk<Data>(value);
  }

  size++;
  return true;
}

template <typename Data>
bool BST<Data>::Insert(Data&& value) noexcept {
  if (root == nullptr) {
    root = new NodeLnk<Data>(std::move(value));
    size++;
    return true;
  }

  NodeLnk<Data>* current = root;
  NodeLnk<Data>* parent = nullptr;

  // Trova la posizione del nuovo nodo
  while (current != nullptr) {
    parent = current;
    if (value == current->element) {
      // Value already exists in the tree, cannot insert duplicate
      return false;
    } else if (value < current->element) {
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }

  // Create a new node and link it to the parent
  if (value < parent->element) {
    parent->leftChild = new NodeLnk<Data>(std::move(value));
  } else {
    parent->rightChild = new NodeLnk<Data>(std::move(value));
  }

  size++;
  return true;
}


template <typename Data>
bool BST<Data>::Remove(const Data& value) {
  if (root == nullptr) {
    // Tree is empty
    return false;
  }

  NodeLnk<Data>* current = root;
  NodeLnk<Data>* parent = nullptr;

  // Find the node to be removed
  while (current != nullptr && current->element != value) {
    parent = current;
    if (value < current->element) {
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }

  if (current == nullptr) {
    // NodeLnk not found
    return false;
  }

  // Case 1: NodeLnk has no children
  if (current->leftChild == nullptr && current->rightChild == nullptr) {
    if (current == root) {
      // Removing the root node
      delete root;
      root = nullptr;
    } else if (parent->leftChild == current) {
      // Removing a leftChild child
      delete parent->leftChild;
      parent->leftChild = nullptr;
    } else {
      // Removing a rightChild child
      delete parent->rightChild;
      parent->rightChild = nullptr;
    }
  }
  // Case 2: NodeLnk has one child
  else if (current->leftChild == nullptr) {
    // NodeLnk has a rightChild child
    if (current == root) {
      // Removing the root node
      root = current->rightChild;
    } else if (parent->leftChild == current) {
      // Removing a leftChild child
      parent->leftChild = current->rightChild;
    } else {
      // Removing a rightChild child
      parent->rightChild = current->rightChild;
    }
    delete current;
  } else if (current->rightChild == nullptr) {
    // NodeLnk has a leftChild child
    if (current == root) {
      // Removing the root node
      root = current->leftChild;
    } else if (parent->leftChild == current) {
      // Removing a leftChild child
      parent->leftChild = current->leftChild;
    } else {
      // Removing a rightChild child
      parent->rightChild = current->leftChild;
    }
    delete current;
  }
  // Case 3: NodeLnk has two children
  else {
    NodeLnk<Data>* successor = Successor(current);
    Data successorValue = successor->element;
    Remove(successorValue);
    current->element = successorValue;
  }

  size--;
  return true;
}

//****************** Funzioni di TestableContainer *********************
//************************************************************************

template <typename Data>
bool BST<Data>::Exists(const Data& value) const {
  NodeLnk<Data>* current = root;

  // Search for the node with the given value
  while (current != nullptr) {
    if (value == current->element) {
      // Value found
      return true;
    } else if (value < current->element) {
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }

  // Value not found
  return false;
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
Data BST<Data>::DataNRemove(NodeLnkLnk<Data>*& node) {
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
    NodeLnkLnk<Data>* temp = node;
    node = node->rightChild;
    delete temp;
  } else if (node->rightChild == nullptr) {
    NodeLnkLnk<Data>* temp = node;
    node = node->leftChild;
    delete temp;
  }
  // Case 3: NodeLnk has two children
  else {
    NodeLnkLnk<Data>* successor = Successor(node);
    node->element = successor->element;
    DataNRemove(successor);
  }

  size--;
  return deletedData;
}

template <typename Data>
typename BST<Data>::NodeLnkLnk* BST<Data>::Detach(typename BST<Data>::NodeLnkLnk*& node) noexcept {  // per staccare il nodo
  if (node == nullptr) {
    return nullptr;
  }

  NodeLnkLnk* detachedNodeLnk = node;
  node = nullptr;
  return detachedNodeLnk;
}

template <typename Data>
typename BST<Data>::NodeLnkLnk* BST<Data>::DetachMin(typename BST<Data>::NodeLnkLnk*& node) noexcept {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->leftChild != nullptr) {
    return DetachMin(node->leftChild);
  } else {
    NodeLnkLnk* detachedNodeLnk = node;
    node = node->rightChild;
    detachedNodeLnk->rightChild = nullptr;
    return detachedNodeLnk;
  }
}

template <typename Data>
typename BST<Data>::NodeLnkLnk* BST<Data>::DetachMax(typename BST<Data>::NodeLnkLnk*& node) noexcept {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->rightChild != nullptr) {
    return DetachMax(node->rightChild);
  } else {
    NodeLnkLnk* detachedNodeLnk = node;
    node = node->leftChild;
    detachedNodeLnk->leftChild = nullptr;
    return detachedNodeLnk;
  }
}

template <typename Data>
typename BST<Data>::NodeLnkLnk* BST<Data>::Skip2Left(typename BST<Data>::NodeLnkLnk*& node) noexcept {
  if (node == nullptr || node->leftChild == nullptr) {
    return nullptr;
  }

  return node->leftChild->leftChild;
}

template <typename Data>
typename BST<Data>::NodeLnkLnk* BST<Data>::Skip2Right(typename BST<Data>::NodeLnkLnk*& node) noexcept {
  if (node == nullptr || node->rightChild == nullptr) {
    return nullptr;
  }

  return node->rightChild->rightChild;
}

template <typename Data>
typename BST<Data>::NodeLnkLnk*& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnkLnk*& node) noexcept {
  if (node == nullptr || node->leftChild == nullptr) {
    return node;
  }

  return FindPointerToMin(node->leftChild);
}

template <typename Data>
typename BST<Data>::NodeLnkLnk* BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnkLnk* const& node) const noexcept {
  if (node == nullptr || node->leftChild == nullptr) {
    return const_cast<typename BST<Data>::NodeLnkLnk*>(node);
  }

  return FindPointerToMin(node->leftChild);
}

template <typename Data>
typename BST<Data>::NodeLnkLnk*& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnkLnk*& node) noexcept {
  if (node == nullptr || node->rightChild == nullptr) {
    return node;
  }

  return FindPointerToMax(node->rightChild);
}

template <typename Data>
typename BST<Data>::NodeLnkLnk* BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnkLnk* const& node) const noexcept {
  if (node == nullptr || node->rightChild == nullptr) {
    return const_cast<typename BST<Data>::NodeLnkLnk*>(node);
  }

  return FindPointerToMax(node->rightChild);
}

template <typename Data>
typename BST<Data>::NodeLnkLnk*& BST<Data>::FindPointerTo(typename BST<Data>::NodeLnkLnk*& node, const Data& value) noexcept {
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
typename BST<Data>::NodeLnkLnk* BST<Data>::FindPointerTo(typename BST<Data>::NodeLnkLnk* const& node, const Data& value) const noexcept {
  if (node == nullptr || node->element == value) {
    return const_cast<typename BST<Data>::NodeLnkLnk*>(node);
  }

  if (value < node->element) {
    return FindPointerTo(node->leftChild, value);
  } else {
    return FindPointerTo(node->rightChild, value);
  }
}

template <typename Data>
typename BST<Data>::NodeLnkLnk*& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnkLnk*& node, const Data& value) noexcept {
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
typename BST<Data>::NodeLnkLnk* BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnkLnk* const& node, const Data& value) const noexcept {
  if (node == nullptr || node->element == value) {
    return const_cast<typename BST<Data>::NodeLnkLnk*>(node);
  }

  if (value < node->element) {
    return FindPointerToPredecessor(node->leftChild, value);
  } else {
    return FindPointerToPredecessor(node->rightChild, value);
  }
}

template <typename Data>
typename BST<Data>::NodeLnkLnk*& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnkLnk*& node, const Data& value) noexcept {
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
typename BST<Data>::NodeLnkLnk* BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnkLnk* const& node, const Data& value) const noexcept {
  if (node == nullptr || node->element == value) {
    return const_cast<typename BST<Data>::NodeLnkLnk*>(node);
  }

  if (value < node->element) {
    return FindPointerToSuccessor(node->leftChild, value);
  } else {
    return FindPointerToSuccessor(node->rightChild, value);
  }
}


/* ************************************************************************** */

}
