
namespace lasd {

/* ************************************************************************** */

  // Specific constructors
  template <typename Data>
  BST<Data>::BST(const LinearContainer<Data>& mp) {
    size = 0;
    for(ulong i = 0; i < mp.Size(); i++){
        Insert(mp[i]);
    }
  } 

  template <typename Data>
  BST<Data>::BST(MutableMappableContainer<Data>&& mp)  {
    size = 0;
    root = mp.Root();
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
        throw std::length_error("Albero vuoto ccc");
    return (FindPointerToMin(root))->it;
  } 

  template <typename Data>
  Data BST<Data>::MinNRemove()  {
    if(root == nullptr) throw std::length_error("Albero vuoto bb");
  Data val = Min();
  RemoveMin();
  return val;
  } 
  
  template <typename Data>
  void BST<Data>::RemoveMin()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto aaaaaaaa");
    
    DetachMin(root);
  //  delete minNode;
  }  

  template <typename Data>
  Data& BST<Data>::Max()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    return (FindPointerToMax(root))->it;
  } 

  template <typename Data>
  Data BST<Data>::MaxNRemove()  {
    if(root == nullptr) throw std::length_error("Albero vuoto");
    Data maxValue = Max();
    RemoveMax();
    return maxValue;
    // return DataNDelete(DetachMax(root));
  } 

  template <typename Data>
  void BST<Data>::RemoveMax()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    DetachMax(root);
  } 

  template <typename Data>
  Data& BST<Data>::Predecessor(const Data& value)  {
    if(root == nullptr) throw std::length_error("Vuoto");
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
    if(root == nullptr) throw std::length_error("Vuoto");
    struct BST<Data>::NodeLnk* succNode = FindPointerToSuccessor(value, root);
    if(succNode == nullptr) throw std::out_of_range("Nessun successore trovato");
    if(succNode->it <= value) throw std::out_of_range("Nessun successore trovato");
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
    // if(root == nullptr) throw std::length_error("Vuoto");
    // struct BST<Data>::NodeLnk* succNode = FindPointerToSuccessor(value, root);
    // if(succNode == nullptr) return;
    // Detach(succNode);
    //---------------------------------
    if(root == nullptr) throw std::length_error("Vuoto");
    struct BST<Data>::NodeLnk* node = FindPointerTo(value, root);
    if (node == nullptr) throw std::invalid_argument("Nodo non trovato");
    struct BST<Data>::NodeLnk* succNode = FindPointerToSuccessor(value, root);
    if(succNode == nullptr) throw std::out_of_range("Successore non trovato");
    if(succNode->rc != nullptr){
      struct BST<Data>::NodeLnk* succR = succNode->rc;
      succNode->it = succR->it;
      succNode->lc = succR->lc;
      succNode->rc = succR->rc;
      delete succR;
    }else{
      if(succNode == node->lc) node->lc = nullptr;
      else node->rc = nullptr;
      delete succNode;
    }
    size--;
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  template <typename Data>
  bool BST<Data>::Insert(const Data& dato)  {
    struct BST<Data>::NodeLnk*& node = FindPointerTo(dato, root);
    if(node == nullptr){
      node = new struct BST<Data>::NodeLnk(dato);
      size++;
      return true;
    }
    return false;
  }  

  template <typename Data>
  bool BST<Data>::Insert(Data&& dato) noexcept  {
    struct BST<Data>::NodeLnk*& node = FindPointerTo(dato, root);
    if(node == nullptr){
      node = new struct BST<Data>::NodeLnk(dato);
      size++;
      return true;
    }
    return false;
  } 

  template <typename Data>
  bool BST<Data>::Remove(const Data& dato)  {
    if(root == nullptr) throw std::length_error("Albero vuoto");
    struct BST<Data>::NodeLnk*& delNodePtr = FindPointerTo(dato, root);
    if(delNodePtr == nullptr) return false;
    Detach(delNodePtr);
    //delete delNode;
    return true;
  }  

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  template <typename Data>
  bool BST<Data>::Exists(const Data& dato) const noexcept  {
    return FindPointerTo(dato, root)!=nullptr;
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
        node = nullptr;
    }
}


  // Auxiliary member functions
  template <typename Data>
  Data BST<Data>::DataNDelete(struct BST<Data>::NodeLnk* node)  {
    if(node == nullptr) throw std::invalid_argument("Nodo non trovato");
    Data val = node->it;
    Detach(node);
    return val;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Detach(struct BST<Data>::NodeLnk*& node) noexcept {
    if(node == nullptr) return nullptr;

    if(node->lc == nullptr) return Skip2Right(node);
    else if(node->rc == nullptr) return Skip2Left(node);
      else{
        struct BST<Data>::NodeLnk* detach = DetachMax(node->lc);
        node->it = detach->it;
        return detach;
      }return nullptr;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::DetachMin(struct BST<Data>::NodeLnk*& node) noexcept {
    if(node == nullptr) return nullptr;
    if(node->lc == nullptr){
      struct BST<Data>::NodeLnk* minNode = node;
      node = node->rc;
      size--;
      return minNode;
    }
    return DetachMin(node->lc);
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::DetachMax(struct BST<Data>::NodeLnk*& node) noexcept {
    if(node == nullptr) return nullptr;
    // struct BST<Data>::NodeLnk* maxNode = FindPointerToMax(node);
    // if(maxNode->rc == nullptr) root = maxNode->lc;
    // else maxNode->rc = Skip2Left(maxNode->rc);
    // size--;
    // return maxNode;
    if(node->rc == nullptr){
      struct BST<Data>::NodeLnk* maxNode = node;
      node = node->lc;
      size--;
      return maxNode;
    }
    return DetachMax(node->rc);
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Skip2Left(struct BST<Data>::NodeLnk*& node) noexcept {
    if(node == nullptr) return nullptr;
    struct BST<Data>::NodeLnk* skipLeft = node->lc;
    delete node;   
    node = nullptr; 
    return skipLeft;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Skip2Right(struct BST<Data>::NodeLnk*& node) noexcept {  
    if(node == nullptr) return nullptr;
    struct BST<Data>::NodeLnk* skipRight = node->rc;
    delete node;
    node = nullptr;
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
