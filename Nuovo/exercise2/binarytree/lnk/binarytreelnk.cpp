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
  else if(value < node ->Element()) funzioneCostruzione(value, node->lc);
  else funzioneCostruzione(value, node->rc);
}

template <typename Data>
void BinaryTreeLnk<Data>::funzioneCostruzione( Data&& value, NodeLnk*& node) {
  if(node == nullptr) node = new NodeLnk(std::move(value));
  else if(std::move(value) < node ->Element()) funzioneCostruzione(std::move(value), node->lc);
  else funzioneCostruzione(std::move(value), node->rc);
}

template <typename Data>
void BinaryTreeLnk<Data>::CopyNodes(NodeLnk*& destNode, const NodeLnk* sourceNode) {
    if (sourceNode->HasLeftChild()) {
        destNode->lc = new NodeLnk(sourceNode->LeftChild().Element());
        CopyNodes(destNode->lc, &sourceNode->LeftChild());
    }
    if (sourceNode->HasRightChild()) {
        destNode->rc = new NodeLnk(sourceNode->RightChild().Element());
        CopyNodes(destNode->rc, &sourceNode->RightChild());
    }
}

  // Specific constructors
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const MappableContainer<Data>& map){
    size = map.Size();
    root = nullptr;
    map.Map([&](const Data& item){
      funzioneCostruzione(item, root);
    });
  }


  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(MutableMappableContainer<Data>&& map){
    size = map.Size();
    root = nullptr;
    map.Map([&](const Data& item){
      funzioneCostruzione(std::move(item), root);
    });
  }


  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt){
    if (bt.root == nullptr) {
        root = nullptr;
    } else {
        // Recursively copy nodes starting from the root
        root = new NodeLnk(bt.root->Element());
        CopyNodes(root, bt.root);
    }
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
    if (bt.root == nullptr) {
        root = nullptr;
    } else {
        // Recursively copy nodes starting from the root
        root = new NodeLnk(bt.root->Element());
        CopyNodes(root, bt.root);
    }
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
        fun(node->Element(), acc);     
            PreOrderFold(fun, acc, node->lc); 
            PreOrderFold(fun, acc, node->rc);
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

          std::cout<< "--------------HERE     -------------" << std::endl;
    NodeLnk* levelStart = node;

    while (levelStart != nullptr) {
          std::cout<< "--------------HERE     2-------------" << std::endl;
        NodeLnk* current = levelStart;

        while (current != nullptr) {
          std::cout<< "--------------HERE     3-------------" << std::endl;
            fun(current->it, acc); // Applica la funzione di piegatura al nodo corrente

            if (current->HasLeftChild()) {
          std::cout<< "--------------HERE     4-------------" << std::endl;
                current = current->lc;
          std::cout<< "--------------HERE     4 E -------------" << std::endl;
            } else {
          std::cout<< "--------------HERE     5-------------" << std::endl;
                current = current->rc;
            }
        }

          std::cout<< "--------------HERE     6-------------" << std::endl;
        if (levelStart->HasLeftChild()) {
          std::cout<< "--------------HERE     7------------" << std::endl;
            levelStart = levelStart->lc;
          std::cout<< "--------------HERE     7E-------------" << std::endl;
        } else {
          std::cout<< "--------------HERE     8-------------" << std::endl;
            levelStart = levelStart->rc;
        }
    }
          std::cout<< "--------------FINE------------" << std::endl;
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
