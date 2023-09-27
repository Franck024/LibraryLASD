
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

  template <typename Data>
  BST<Data>::~BST() {
    Clear();
  }

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
    if(size != bt.size) return false;
    if(size == 0) return true;

    // BTInOrderIterator<Data> iterThis(*this);
    // BTInOrderIterator<Data> iterOther(bt);
    // while (!iterThis.Terminated() && !iterOther.Terminated()){
    //     if(*iterThis != *iterOther)
    //         return false;
    //     ++iterThis;
    //     ++iterOther;
    // }
    // return true;

    BTInOrderIterator<Data> iterThis(*this);
    while(!iterThis.Terminated()){
      if(bt.Exists(*iterThis) == false) return false;
      ++iterThis;
    }
    return true;
    
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
        throw std::length_error("Albero vuoto ");
    
    Remove(Min());
    
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
    Remove(Max());
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
    Data preValue = Predecessor(value);
    RemovePredecessor(value);
    return preValue;
  }  

  template <typename Data>
  void BST<Data>::RemovePredecessor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    Remove(Predecessor(value));
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
    Data succValue = Successor(value);
    RemoveSuccessor(value);
    return succValue;
  } 

  template <typename Data>
  void BST<Data>::RemoveSuccessor(const Data& value)  {
    if(root == nullptr) throw std::length_error("Vuoto");
    Remove(Successor(value));
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
    struct BST<Data>::NodeLnk* delNode = Detach(delNodePtr);
    delete delNode;
    size--;
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
        struct BST<Data>::NodeLnk* detNode = DetachMax(node->lc);
            std::swap(node->it, detNode->it);
        return detNode;
      }
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
    struct BST<Data>::NodeLnk* skipLeft = nullptr;
    if(node!=nullptr){
        std::swap(skipLeft,node->lc);
        std::swap(skipLeft,node);
    }
    return skipLeft;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Skip2Right(struct BST<Data>::NodeLnk*& node) noexcept {  
    struct BST<Data>::NodeLnk* skipRight = nullptr;
    if(node!=nullptr){
        std::swap(skipRight,node->rc);
        std::swap(skipRight,node);
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
    struct BST<Data>::NodeLnk* curr = node;
    while(curr != nullptr){
      if(curr->it == dato){
        if(curr->lc != nullptr){
          pre = curr->lc;
          while(pre->rc != nullptr){
            pre = pre->rc;
          }
        }
        break;
      }
      else if(curr->it > dato) curr = curr->lc;
        else{
          pre = curr;
          curr = curr->rc;
        }
    }
    return pre;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::FindPointerToPredecessor(const Data& dato, struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* pre = nullptr;
    struct BST<Data>::NodeLnk* curr = node;
    while(curr != nullptr){
      if(curr->it == dato){
        if(curr->lc != nullptr){
          pre = curr->lc;
          while(pre->rc != nullptr){
            pre = pre->rc;
          }
        }
        break;
      }
      else if(curr->it > dato) curr = curr->lc;
        else{
          pre = curr;
          curr = curr->rc;
        }
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
    struct BST<Data>::NodeLnk* curr = node;

    while (curr != nullptr) {
        if (curr->it == dato) {
            if (curr->rc != nullptr) {
                succ = curr->rc;
                while (succ->lc != nullptr) {
                    succ = succ->lc;
                }
            }
            break;  
        } else if (dato < curr->it) {
            succ = curr;
            curr = curr->lc;
        } else curr = curr->rc;
    }
    return succ;
  }  

/* ************************************************************************** */

  template <typename Data>
  bool BST<Data>::InsertAll(const MappableContainer<Data>& map){
    map.Map([&](const Data& item) {
        Insert(item);
    });
    return true;
  }

  template <typename Data>
  bool BST<Data>::InsertAll(MutableMappableContainer<Data>&& map) noexcept{
    map.Map([&](Data& item) {
        Insert(std::move(item));
    });
    return true;
  }


  template <typename Data>
  bool BST<Data>::RemoveAll(const MappableContainer<Data>& map) {
    map.Map([&](const Data& item) {
        Remove(item);
    });
    return true;
  }


  template <typename Data>
  bool BST<Data>::InsertSome(const MappableContainer<Data>& map, ulong numElem) {
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong insertCount = 0;
    map.Map([&](const Data& item) {
        if(insertCount < numElem){
          Insert(item);
          insertCount++;
        }
    });
    return true;
  }


  template <typename Data>
  bool BST<Data>::InsertSome(MutableMappableContainer<Data>&& map, ulong numElem) noexcept {
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong insertCount = 0;
    map.Map([&](Data& item) {
        if(insertCount < numElem){
          Insert(std::move(item));
          insertCount++;
        }
    });
    return true;
  }


  template <typename Data>
  bool BST<Data>::RemoveSome(const MappableContainer<Data>& map, ulong numElem) {
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong removeCount = 0;
    map.Map([&](const Data& item) {
        if(removeCount < numElem){
          Remove(item);
          removeCount++;
        }
    });
    return true;
  }


}
