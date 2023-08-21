
namespace lasd {

/* ************************************************************************** */

  // Specific constructors
  template <typename Data>
  BST<Data>::BST(const LinearContainer<Data>& mp) {
    // for(ulong i = 0; i < mp.Size(); i++){
    //     Insert(mp[i]);
    //}
  } 

  template <typename Data>
  BST<Data>::BST(MutableMappableContainer<Data>&& mp)  {
    // for(ulong i = 0; i < mp.Size(); i++){
    //     Insert(std::move(mp[i]));
    //}
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
    return DataNDelete(DetachMin(root));
  } 
  
  template <typename Data>
  void BST<Data>::RemoveMin()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    DetachMin(root);
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
    return DataNDelete(DetachMax(root));
  } 

  template <typename Data>
  void BST<Data>::RemoveMax()  {
    if(root == nullptr)
        throw std::length_error("Albero vuoto");
    DetachMax(root);
  } 

  template <typename Data>
  Data& BST<Data>::Predecessor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    return (FindPointerToPredecessor(value, root))->it;
  }  

  template <typename Data>
  Data BST<Data>::PredecessorNRemove(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    return DataNDelete(Detach(FindPointerToPredecessor(value, root)));
  }  

  template <typename Data>
  void BST<Data>::RemovePredecessor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    Detach(FindPointerToPredecessor(value, root));
  }  

  template <typename Data>
  Data& BST<Data>::Successor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    return FindPointerToSuccessor(value, root)->it;
  }  

  template <typename Data>
  Data BST<Data>::SuccessorNRemove(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    return DataNDelete(Detach(FindPointerToSuccessor(value, root)));
  } 

  template <typename Data>
  void BST<Data>::RemoveSuccessor(const Data& value)  {
    if(root == nullptr)
        throw std::length_error("Vuoto");
    Detach(FindPointerToSuccessor(value, root)->it);
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  template <typename Data>
  bool BST<Data>::Insert(const Data& dato)  {
    struct BST<Data>::NodeLnk*& pointer = FindPointerTo(dato, root);
    if(pointer==nullptr){
        pointer = new struct BST<Data>::NodeLnk(dato);
        size++;
        return true;
    }
    return false;
  }  

  template <typename Data>
  bool BST<Data>::Insert(Data&& dato) noexcept  {
    struct BST<Data>::NodeLnk*& pointer = FindPointerTo(dato, root);
    if(pointer==nullptr){
        pointer = new struct BST<Data>::NodeLnk(dato);
        size++;
        return true;
    }
    return false;
  } 

  template <typename Data>
  bool BST<Data>::Remove(const Data& dato)  {
    return Detach(FindPointerTo(dato, root));
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
        node = nullptr; 
    }
}


  // Auxiliary member functions
  template <typename Data>
  Data BST<Data>::DataNDelete(struct BST<Data>::NodeLnk* node)  {
    Data val;
    val = node->it;
    delete node;
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
        delete detach;
    }
    return nullptr;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::DetachMin(struct BST<Data>::NodeLnk*& node) noexcept {
    return Skip2Right(FindPointerToMin(node));
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::DetachMax(struct BST<Data>::NodeLnk*& node) noexcept {
    return Skip2Left(FindPointerToMax(node));
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Skip2Left(struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* skipLeft = nullptr;
    if(node != nullptr){
        skipLeft = node->lc;
        delete node;
        node = skipLeft;
        size--;
    }
    return skipLeft;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* BST<Data>::Skip2Right(struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* skipRight = nullptr;
    if(node != nullptr){
        skipRight = node->rc;
        delete node;
        node = skipRight;
        size--;
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
    struct BST<Data>::NodeLnk** ptr = &node;
    while((*ptr)->rc != nullptr){
        ptr = &((*ptr) -> rc);
    }
    return *ptr;
  }  

  template <typename Data>
  struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(const Data& dato, struct BST<Data>::NodeLnk* const& node) const noexcept {
    struct BST<Data>::NodeLnk* const* ptr = &node;
    if(*ptr != nullptr){
        if(node->it == dato) return *ptr;
        else if(node->it > dato) ptr = &(FindPointerTo(dato, node->lc));
        else ptr = &(FindPointerTo(dato, node->rc));
    }
    return *ptr;
  }  

  template <typename Data>
  struct BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(const Data& dato, struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk** ptr = &node;
    if(*ptr != nullptr){
        if(node->it == dato) return *ptr;
        else if(node->it > dato) ptr = &(FindPointerTo(dato, node->lc));
        else ptr = &(FindPointerTo(dato, node->rc));
    }
    return *ptr;
  }  
 
  template <typename Data>
  struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(const Data& dato, struct BST<Data>::NodeLnk* const& node) const noexcept {
    struct BST<Data>::NodeLnk* const* current = &node;
    struct BST<Data>::NodeLnk* const* estimate = nullptr;
    while(*current != nullptr && (*current)->it != dato){
        if((*current)->it < dato) current = &((*current)->rc);
        else{
            estimate = current;
            current = &((*current)-> rc);
        }
    }
    if(*current != nullptr && (*current)->HasLeftChild()) estimate = &(FindPointerToMax((*current)->lc));
    return *estimate;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(const Data& dato, struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* * current = &node;
    struct BST<Data>::NodeLnk* * estimate = nullptr;
    while(*current != nullptr && (*current)->it != dato){
        if((*current)->it < dato) current = &((*current)->rc);
        else{
            estimate = current;
            current = &((*current)-> rc);
        }
    }
    if(*current != nullptr && (*current)->HasLeftChild()) estimate = &(FindPointerToMax((*current)->lc));
    return *estimate;
  } 

  template <typename Data>
  struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(const Data& dato, struct BST<Data>::NodeLnk* const& node) const noexcept {
    struct BST<Data>::NodeLnk* const* current = &node;
    struct BST<Data>::NodeLnk* const* estimate = nullptr;
    while(*current != nullptr && (*current)->it != dato){
        if((*current)->it < dato) current = &((*current)->lc);
        else{
            estimate = current;
            current = &((*current)-> lc);
        }
    }
    if(*current != nullptr && (*current)->HasRightChild()) estimate = &(FindPointerToMin((*current)->rc));
    return *estimate;
  }  

  template <typename Data>
  struct BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(const Data& dato, struct BST<Data>::NodeLnk*& node) noexcept {
    struct BST<Data>::NodeLnk* * current = &node;
    struct BST<Data>::NodeLnk* * estimate = nullptr;
    while(*current != nullptr && (*current)->it != dato){
        if((*current)->it < dato) current = &((*current)->lc);
        else{
            estimate = current;
            current = &((*current)-> lc);
        }
    }
    if(*current != nullptr && (*current)->HasRightChild()) estimate = &(FindPointerToMin((*current)->rc));
    return *estimate;
  }  

/* ************************************************************************** */

}
