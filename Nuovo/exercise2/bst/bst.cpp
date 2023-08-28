
namespace lasd {

/* ************************************************************************** */

  // Specific constructors
  template <typename Data>
  BST<Data>::BST(const LinearContainer<Data>& mp) {
    for(ulong i = 0; i < mp.Size(); i++){
        Insert(mp[i]);
    }
  } 

  template <typename Data>
  BST<Data>::BST(MutableMappableContainer<Data>&& mp)  {
    mp.Map([&](Data&& item) {
        Insert(std::move(item));
    });
  } 

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BST<Data>::BST(const BST<Data>& bst) :  BinaryTreeLnk<Data>(bst){} 

  // Move constructor
  template <typename Data>
  BST<Data>::BST(BST<Data>&& bt) noexcept : BinaryTreeLnk<Data>(std::move(bt)) {} 

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(const BST<Data>& bt)  {
    BinaryTreeLnk<Data>::operator=(bt);
    return *this;
  } 

  // Move assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(BST<Data>&& bt) noexcept {
    BinaryTreeLnk<Data>::operator=(std::move(bt));
    return *this;
  } 

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BST<Data>::operator==(const BST<Data>& bt) const noexcept {
    if(size==bt.size){
        BTInOrderIterator<Data> iterThis(*this);
        BTInOrderIterator<Data> iterOther(bt);
        while (!iterThis.Terminated() && !iterOther.Terminated()){
            if(*iterThis != *iterOther)
                return false;
            ++iterThis;
            ++iterOther;
        }
        if(iterThis.Terminated() && iterOther.Terminated()) return true;
    }
    return false;
  } 

  template <typename Data>
  bool BST<Data>::operator!=(const BST<Data>& bt) const noexcept {
    return !(*this == bt);
  } 

  /* ************************************************************************ */

  // Specific member functions
  template <typename Data>
  Data& BST<Data>::Min()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    return (FindPointerToMin(root))->it;
  } 

  template <typename Data>
  Data BST<Data>::MinNRemove()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
  struct BST<Data>::NodeLnk* minNode = DetachMin(root);
  Data minValue = minNode->it;
  delete minNode;
  return minValue;
  } 
  
  template <typename Data>
  void BST<Data>::RemoveMin()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    struct BST<Data>::NodeLnk* minNode = DetachMin(root);
    delete minNode;
  }  

  template <typename Data>
  Data& BST<Data>::Max()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    return (FindPointerToMax(root))->it;
  } 

  template <typename Data>
  Data BST<Data>::MaxNRemove()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    struct BST<Data>::NodeLnk* maxNode = DetachMax(root);
    Data maxValue = maxNode->it;
    delete maxNode;
    return maxValue;
  } 

  template <typename Data>
  void BST<Data>::RemoveMax()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    delete DetachMax(root);
  } 

  template <typename Data>
  Data& BST<Data>::Predecessor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    struct BST<Data>::NodeLnk* preNode = FindPointerToPredecessor(value, root);
    if(preNode == nullptr) throw std::out_of_range("Nessun predecessore trovato");
    return preNode->it;
  }  

  template <typename Data>
  Data BST<Data>::PredecessorNRemove(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    struct BST<Data>::NodeLnk* preNode = FindPointerToPredecessor(value, root);
    if(preNode == nullptr) throw std::out_of_range("Nessun predecessore trovato");
    Data preValue = preNode->it;
    Detach(preNode);
    return preValue;
  }  

  template <typename Data>
  void BST<Data>::RemovePredecessor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    struct BST<Data>::NodeLnk* preNode = FindPointerToPredecessor(value, root);
    if(preNode == nullptr) return;
    Detach(preNode);
  }  

  template <typename Data>
  Data& BST<Data>::Successor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    struct BST<Data>::NodeLnk* succNode = FindPointerToSuccessor(value, root);
    if(succNode == nullptr) throw std::out_of_range("Nessun predecessore trovato");
    return succNode->it;
  }  

  template <typename Data>
  Data BST<Data>::SuccessorNRemove(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    struct BST<Data>::NodeLnk* succNode = FindPointerToSuccessor(value, root);
    if(succNode == nullptr) throw std::out_of_range("Nessun successore trovato");
    Data succValue = succNode->it;
    Detach(succNode);
    return succValue;
  } 

  template <typename Data>
  void BST<Data>::RemoveSuccessor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    struct BST<Data>::NodeLnk* succNode = FindPointerToSuccessor(value, root);
    if(succNode == nullptr) return;
    Detach(succNode);
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  template <typename Data>
  bool BST<Data>::Insert(const Data& dato)  {
    // struct BST<Data>::NodeLnk*& pointer = FindPointerTo(dato, root);
    // if(pointer==nullptr){
    //     pointer = new struct BST<Data>::NodeLnk(dato);
    //     size++;
    //     return true;
    // }
    // return false;
    //-----------------------------------
    struct BST<Data>::NodeLnk* node = new struct BST<Data>::NodeLnk(dato);
    if(root == nullptr){
      root = node;
      size++;
      return true;
    }
    struct BST<Data>::NodeLnk* curr = root;
    struct BST<Data>::NodeLnk* parent = nullptr;
    while(curr != nullptr){
      parent = curr;
      if(dato < curr->it) curr = curr->lc;
      else if(dato > curr->it) curr = curr->rc;
        else{
          delete node;
          return false;
        }
    }
    if(dato < parent->it) parent->lc = node;
    else parent->rc = node;
    size++; 
    return true;
  }  

  template <typename Data>
  bool BST<Data>::Insert(Data&& dato) noexcept  {
    struct BST<Data>::NodeLnk* node = new struct BST<Data>::NodeLnk(dato);
    if(root == nullptr){
      root = node;
      size++;
      return true;
    }
    struct BST<Data>::NodeLnk* curr = root;
    struct BST<Data>::NodeLnk* parent = nullptr;
    while(curr != nullptr){
      parent = curr;
      if(dato < curr->it) curr = curr->lc;
      else if(dato > curr->it) curr = curr->rc;
        else{
          delete node;
          return false;
        }
    }
    if(dato < parent->it) parent->lc = node;
    else parent->rc = node;
    size++; 
    return true;
  } 

  template <typename Data>
  bool BST<Data>::Remove(const Data& dato)  {
    if(root == nullptr) std::length_error("Albero vuoto");
    struct BST<Data>::NodeLnk* parent = nullptr;
    struct BST<Data>::NodeLnk* delNode = FindPointerTo(dato, root);
    if(delNode == nullptr) return false;
    if(delNode->lc == nullptr){
      if(parent == nullptr) root = delNode->rc;
      else if(parent->lc == delNode) parent->lc = delNode->rc;
        else parent->rc = delNode->rc;
      delete delNode;
    }else if(delNode->rc == nullptr){
      if(parent == nullptr) root = delNode->lc;
      else if(parent->lc == delNode) parent->lc = delNode->lc;
        else parent->rc = delNode->lc;
      delete delNode;
    }else{
      struct BST<Data>::NodeLnk* succ = delNode->rc;
      struct BST<Data>::NodeLnk* succParent = delNode;
      while(succ->lc != nullptr){
        succParent = succ;
        succ = succ->lc;
      }
      delNode->it = succ->it;
      if(succParent->lc == succ) succParent->lc = succ->rc;
      else succParent->rc = succ->rc;
      delete succ;
    }
    return true;
  }  

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  template <typename Data>
  bool BST<Data>::Exists(const Data& dato) const noexcept  {
    return (FindPointerTo(dato, root)!=nullptr);
  } 

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  template <typename Data>
  void BST<Data>::Clear()  {
    ClearNodes(root);
    size = 0; 
    root = nullptr; 
  } 

  template <typename Data>
  void BST<Data>::ClearNodes(struct BST<Data>::NodeLnk*& node) {
    if (node != nullptr) {
        ClearNodes(node->lc);
        ClearNodes(node->rc); 
        delete node;
    }
}


  // Auxiliary member functions
  template <typename Data>
  Data BST<Data>::DataNDelete(struct BST<Data>::NodeLnk* node)  {
    if(node == nullptr) throw std::invalid_argument("Nodo non trovato");
    Data val = node->it;
    Remove(node->it);
    return val;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Detach(struct BST<Data>::NodeLnk*& node) noexcept {
    if(node == nullptr) return nullptr;
    struct BST<Data>::NodeLnk* detNode = nullptr;
    if(node->lc == nullptr) detNode =  Skip2Right(node);
    else if(node->rc == nullptr) detNode = Skip2Left(node);
    else{
        detNode = DetachMax(node->lc);
        detNode->lc = node->lc;
        detNode->rc = node->rc;
    }
    delete node;
    node = detNode;
    size--;
    return detNode;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::DetachMin(struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* minNode = FindPointerToMin(node);
    if(minNode->lc == nullptr) node = minNode->rc;
    else minNode->lc = Skip2Right(minNode->lc);
    size--;
    return minNode;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::DetachMax(struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* maxNode = FindPointerToMax(node);
    if(maxNode->rc == nullptr) node = maxNode->lc;
    else maxNode->rc = Skip2Left(maxNode->rc);
    size--;
    return maxNode;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Skip2Left(struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* skipLeft = nullptr;
    if(node != nullptr){
        skipLeft = node->lc;
        delete node;
    }
    return skipLeft;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Skip2Right(struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* skipRight = nullptr;
    if(node != nullptr){
        skipRight = node->rc;
        delete node;
    }
    return skipRight;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(struct BST<Data>::NodeLnk* const& node) const noexcept {
    struct BST<Data>::NodeLnk* const* ptr = &node;
    while((*ptr)->lc != nullptr){
        ptr = &((*ptr) -> lc);
    }
    return *ptr;
  }  

  template <typename Data>
  struct BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(struct BST<Data>::NodeLnk*& node)  noexcept {
    struct BST<Data>::NodeLnk** ptr = &node;
    while((*ptr)->lc != nullptr){
        ptr = &((*ptr) -> lc);
    }
    return *ptr;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(struct BST<Data>::NodeLnk* const& node) const noexcept {
    struct BST<Data>::NodeLnk* const* ptr = &node;
    while((*ptr)->rc != nullptr){
        ptr = &((*ptr) -> rc);
    }
    return *ptr;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(struct BST<Data>::NodeLnk*& node)  noexcept {
    struct BST<Data>::NodeLnk* * ptr = &node;
    while((*ptr)->rc != nullptr){
        ptr = &((*ptr) -> rc);
    }
    return *ptr;
  }  

  template <typename Data>
  struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(const Data& dato, struct BST<Data>::NodeLnk* const& node) const noexcept {
    // std::cout << std::endl << "------HERE   F-------------" << std::endl;
    // struct BST<Data>::NodeLnk* const* ptr = &node;
    // std::cout << std::endl << "------HERE  F 1 -------------" << std::endl;
    // if(*ptr != nullptr){
    // std::cout << std::endl << "------HERE   F 2-------------" << std::endl;
    //     if(node->it == dato){
    // std::cout << std::endl << "------HERE  Fc3  -------------" << std::endl;
    //       return *ptr;
    //     } 
    //     else if(node->it > dato){
    // std::cout << std::endl << "------HERE   F 4-------------" << std::endl;
    //       ptr = &((*this).FindPointerTo(dato, node->lc));
    //     } 
    //     else {
    // std::cout << std::endl << "------HERE  F5 -------------" << std::endl;
    //       ptr = &((*this).FindPointerTo(dato, node->rc));
    // }}
    // std::cout << std::endl << "------HERE  F EXT -------------" << std::endl;
    // return *ptr;
    //-----------------------------------------------------------------------
    // std::cout << std::endl << "------HERE   4-------------" << std::endl;
    //     struct BST<Data>::NodeLnk* const* pointer = &node;
    // struct BST<Data>::NodeLnk* current = node;

    // if(current!=nullptr) {
    // std::cout << std::endl << "------HERE   5-------------" << std::endl;
    //     while (current!=nullptr && current->it!=dato) {
    // std::cout << std::endl << "------HERE   while-------------" << std::endl;
    //         if(dato < current->it  ) {
    // std::cout << std::endl << "------curr->lc=    "<< current->lc << std::endl;
    //             pointer = &current->lc;
    // std::cout << std::endl << "------HERE   xxx-------------" << std::endl;
    //             current = current->lc;
    // std::cout << std::endl << "------HERE  ssss -------------" << std::endl;
    //         }else if(dato > current->it  ){
    // std::cout << std::endl << "------HERE  w elseif -------------" << std::endl;
    //             pointer = &current->rc;
    //             current = current->rc;
    //         }
    //     }
    // }
    // std::cout << std::endl << "------FINE   -------------" << std::endl;
    // return *pointer;  
    //-----------------------------------------------------------------------
      if(node == nullptr || node->it == dato) return node;
      if(node->it > dato) return FindPointerTo(dato, node->lc);
      if(node->it < dato) return FindPointerTo(dato, node->rc);
      return node;
  }  

  template <typename Data>
  struct BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(const Data& dato, struct BST<Data>::NodeLnk*& node) noexcept {
          if(node == nullptr || node->it == dato) return node;
      if(node->it > dato) return FindPointerTo(dato, node->lc);
      if(node->it < dato) return FindPointerTo(dato, node->rc);
      return node;

  }  
 
  template <typename Data>
  struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(const Data& dato, struct BST<Data>::NodeLnk* const& node) const noexcept {
    // struct BST<Data>::NodeLnk* const* current = &node;
    // struct BST<Data>::NodeLnk* const* estimate = nullptr;
    // while(*current != nullptr && (*current)->it != dato){
    //     if((*current)->it < dato) current = &((*current)->rc);
    //     else{
    //         estimate = current;
    //         current = &((*current)-> rc);
    //     }
    // }
    // if(*current != nullptr && (*current)->HasLeftChild()) estimate = &(FindPointerToMax((*current)->lc));
    // return *estimate;

    struct BST<Data>::NodeLnk* pre = nullptr;
    while(node != nullptr){
        if(node->it <dato){
          pre = node;
          node = node->rc;
        }else node = node->lc;
      }
    return pre;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::FindPointerToPredecessor(const Data& dato, struct BST<Data>::NodeLnk*& node) noexcept {
    // struct BST<Data>::NodeLnk* * current = &node;
    // struct BST<Data>::NodeLnk* * estimate = nullptr;
    // while(*current != nullptr && (*current)->it != dato){
    //     if((*current)->it < dato) current = &((*current)->rc);
    //     else{
    //         estimate = current;
    //         current = &((*current)-> rc);
    //     }
    // }
    // if(*current != nullptr && (*current)->HasLeftChild()) estimate = &(FindPointerToMax((*current)->lc));
    // return *estimate;
    
    struct BST<Data>::NodeLnk* pre = nullptr;
    while(node != nullptr){
        if(node->it < dato){
          pre = node;
          node = node->rc;
        }else node = node->lc;
      }
    return pre;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(const Data& dato, struct BST<Data>::NodeLnk* const& node) const noexcept {
    struct BST<Data>::NodeLnk* succ = nullptr;
    while(node != nullptr){
        if(node->it > dato){
          succ = node;
          node = node->lc;
        }else node = node->rc;
      }
    return succ;
  }  

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::FindPointerToSuccessor(const Data& dato, struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* succ = nullptr;
    while(node != nullptr){
        if(node->it > dato){
          succ = node;
          node = node->lc;
        }else node = node->rc;
      }
    return succ;
  }  

/* ************************************************************************** */

}
