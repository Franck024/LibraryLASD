#include <queue>
namespace lasd {

/* ************************************************************************** */

// ------------------------------
//-------------NodeLnk-----------
    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
        if(lc == nullptr) throw std::out_of_range("figlio inesistente");
        return *lc;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild(){
        if(lc == nullptr) throw std::out_of_range("figlio inesistente");
        return *lc;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
        if(rc == nullptr) throw std::out_of_range("figlio inesistente");
        return *rc;
    }

    template <typename Data>  
    BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild(){
        if(rc == nullptr) throw std::out_of_range("figlio inesistente");
        return *rc;
    }

//--------------------------------
//-------------BinaryTreeLnk------

//Funzioni accessorie
template <typename Data>
void BinaryTreeLnk<Data>::funzioneCostruzione(const Data& value, NodeLnk*& node) {
  if(node == nullptr) node = new NodeLnk(value);
  else if(!(node->HasLeftChild())) funzioneCostruzione(value, node->lc);
  else if(!(node->HasRightChild())) funzioneCostruzione(value, node->rc);
  else funzioneCostruzione(value, node->lc);
}

template <typename Data>
void BinaryTreeLnk<Data>::funzioneCostruzione( Data&& value, NodeLnk*& node) {
  if(node == nullptr) node = new NodeLnk(std::move(value));
  else if(!(node->HasLeftChild())) funzioneCostruzione(std::move(value), node->lc);
  else if(!(node->HasRightChild())) funzioneCostruzione(std::move(value), node->rc);
  else funzioneCostruzione(std::move(value), node->lc);
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::CopyNodes(NodeLnk* sourceNode) {
    NodeLnk* node = nullptr;
    if(sourceNode != nullptr){
      node = new NodeLnk(sourceNode->Element());
      if(sourceNode->HasLeftChild()) node->lc = CopyNodes(sourceNode->lc);
      if(sourceNode->HasRightChild()) node->rc = CopyNodes(sourceNode->rc);
    }
    return node;
}

  // Specific constructors
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const MappableContainer<Data>& map){
    size = map.Size();
    root = nullptr;
    bool firstItem = true;

    map.Map([&](const Data& item){
      if(firstItem){
        root = new NodeLnk(item);
        firstItem = false;
      }else funzioneCostruzione(item, root);
    });
  }


  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(MutableMappableContainer<Data>&& map){
    size = map.Size();
    root = nullptr;
    bool firstItem = true;

    map.Map([&](const Data& item){
      if(firstItem){
        root = new NodeLnk(std::move(item));
        firstItem = false;
      }else funzioneCostruzione(std::move(item), root);
    });
  }


  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt){
    size = bt.size;
    if (bt.root == nullptr) root = nullptr; 
    else root = CopyNodes(bt.root);
  }

  // Move constructor
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& bt) noexcept{
    std::swap(size, bt.size);
    std::swap(root, bt.root);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt){
    size = bt.size;
    if (bt.root == nullptr) root = nullptr; 
    else root = CopyNodes(bt.root);
    return *this;
  }

  // Move assignment
  template <typename Data>
  BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept{
    std::swap(size, bt.size);
    std::swap(root, bt.root);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& bt) const noexcept{
    return BinaryTree<Data>::operator==(bt);
  }
  
  template <typename Data>
  bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  template <typename Data>
  typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const{
    if(root == nullptr) throw std::length_error("Albero vuoto");
    return *root;
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  template <typename Data>
  typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root(){
    if(root == nullptr) throw std::length_error("Albero vuoto");
    return *root;
  }

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  template <typename Data>
  void BinaryTreeLnk<Data>::Clear(){
    size = 0;
    delete root;
    root = nullptr;
  }

//--------------------------------
//-----per non rendere la classe astratta-----------
template <typename Data>
void BinaryTreeLnk<Data>::PreOrderFold(const FoldFunctor fun, void* acc) const{
  if (size != 0) PreOrderFold(fun, acc, &(Root()));
}

template <typename Data>
void BinaryTreeLnk<Data>::PreOrderFold(const FoldFunctor fun, void* acc, NodeLnk* node) const {
    if(node != nullptr){
        // fun(node->Element(), acc);     
        //     PreOrderFold(fun, acc, node->lc); 
        //     PreOrderFold(fun, acc, node->rc);
        fun(node->Element(), acc);
        if(node->HasLeftChild())  PreOrderFold(fun, acc, &(node->LeftChild()));
        if(node->HasRightChild())  PreOrderFold(fun, acc, &(node->RightChild()));
    }
}

template <typename Data>
void BinaryTreeLnk<Data>::PostOrderFold(const FoldFunctor fun, void* acc) const {
  if (size != 0) PostOrderFold(fun, acc, &(Root()));
}

template <typename Data>
void BinaryTreeLnk<Data>::PostOrderFold(const FoldFunctor fun, void* acc, NodeLnk* node) const {
    if(node != nullptr){
      PostOrderFold(fun, acc, node->lc);
      PostOrderFold(fun, acc, node->rc);
      fun(node->Element(), acc);
    }
}

template <typename Data>
void BinaryTreeLnk<Data>::InOrderFold(const FoldFunctor fun, void* acc) const {
  if (size != 0) InOrderFold(fun, acc, &(Root()));
}

template <typename Data>
void BinaryTreeLnk<Data>::InOrderFold(const FoldFunctor fun, void* acc, NodeLnk* node) const {
    if(node != nullptr){
        InOrderFold(fun, acc, node->lc);
        fun(node->Element(), acc);
        InOrderFold(fun, acc, node->rc);
    } 
}

template <typename Data>
void BinaryTreeLnk<Data>::BreadthFold(const FoldFunctor fun, void* acc) const {
  if (size != 0) BreadthFold(fun, acc, &(Root()));
}

template <typename Data>
void BinaryTreeLnk<Data>::BreadthFold(const FoldFunctor fun, void* acc, NodeLnk* node) const {
    if (node == nullptr) {
        return;
    }
    QueueLst<NodeLnk*> que;
    que.Enqueue(node);
    while(!(que.Empty())){
      struct BinaryTreeLnk<Data>::NodeLnk* tmp = que.Head();
      que.Dequeue();
      fun(tmp->Element(), acc);
      if(tmp->HasLeftChild()) que.Enqueue(&(tmp->LeftChild()));
      if(tmp->HasRightChild()) que.Enqueue(&(tmp->RightChild()));
    }
}

//----------------------------------------
//---------Aggunto per valori inattesi----
template <typename Data>
void BinaryTreeLnk<Data>::Fold(const FoldFunctor fun , void* acc) const{
  PreOrderFold(fun, acc);
}

template <typename Data>
void BinaryTreeLnk<Data>::Map(MapFunctor fun) const{
  PreOrderMap(fun);
}

template <typename Data>
void BinaryTreeLnk<Data>::PreOrderMap(MapFunctor fun) const{
  PreOrderMap(fun, &(Root()));
}

template <typename Data>
void BinaryTreeLnk<Data>::PreOrderMap(MapFunctor fun, NodeLnk* node) const{
  if(node != nullptr){
    fun(node->Element());
    PreOrderMap(fun, node->lc);
    PreOrderMap(fun, node->rc);
  }
}
/* ************************************************************************** */

}
