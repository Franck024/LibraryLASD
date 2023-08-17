
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

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& InsertAtRoot(const Data& data) {
    if (root == nullptr) {
        root = new NodeLnk(data);
        return *root;
    } else {
        NodeLnk* newNode = new NodeLnk(data);
        newNode->lc = root;
        root = newNode;
        return *newNode;
    }
}

template <typename Data>
void CopyNodes(NodeLnk*& destNode, const NodeLnk* sourceNode) {
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
    for(const Data& element : map){
        InsertAtRoot(element);
    }
  }
  
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(MutableMappableContainer<Data>&& map){
    for(const Data& element : map){
        InsertAtRoot(std::move(element));
    }
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt){
    if (other.root == nullptr) {
        root = nullptr;
    } else {
        // Recursively copy nodes starting from the root
        root = new NodeLnk(other.root->Element());
        CopyNodes(root, other.root);
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
    if (other.root == nullptr) {
        root = nullptr;
    } else {
        // Recursively copy nodes starting from the root
        root = new NodeLnk(other.root->Element());
        CopyNodes(root, other.root);
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

/* ************************************************************************** */

}
