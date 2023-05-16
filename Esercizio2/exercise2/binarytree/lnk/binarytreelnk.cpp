
namespace lasd {

/* ************************************************************************** */

//************** NodeLnk ***************************
//**************************************************
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& val) : element(val), leftChild(nullptr), rightChild(nullptr){}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk(){
    delete leftChild;
    delete rightChild;
}

template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept{
    return element;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild()const noexcept{
    return (leftChild != nullptr);
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
    return (rightChild !=  nullptr);
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
    if(leftChild == nullptr)
        throw std::out_of_range("campo vuoto!");
    return *leftChild;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
    if(rightChild == nullptr)
        throw std::out_of_range("campo vuoto!");
    return *rightChild;
}


//******************** BinaryTreeLnk *************************
//************************************************************
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk* copyTree(const typename BinaryTreeLnk<Data>::NodeLnk* node) {
    if (!node)
        return nullptr;

    typename BinaryTreeLnk<Data>::NodeLnk* newNode = new BinaryTreeLnk<Data>::NodeLnk::NodeLnk(node->element);
    newNode->leftChild = copyTree(node->leftChild);
    newNode->rightChild = copyTree(node->rightChild);
    return newNode;
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const MappableContainer<Data>& mp){}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MutableMappableContainer<Data>&& mmp) noexcept{}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& copy) : root(copyTree(copy.root)){}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& bt) noexcept : root(std::exchange(bt.root, nullptr)){}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    Clear();
}

template <typename Data>
BinaryTreeLnk<Data> BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt){
    if(this != &bt){
        Clear();
        root = copyTree(bt.root);
    }
    return *this;
}

template <typename Data>
BinaryTreeLnk<Data> BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept {
    if(this != &bt){
        Clear();
        root = std::exchange(bt.root, nullptr);
    }
    return *this;
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& bt) const noexcept{
    return equals(root, bt.root);
}

template <typename Data>
bool BinaryTreeLnk<Data>::equals(const NodeLnk* node1, const NodeLnk* node2) const {
    if(!node1 && !node2)
        return true;
    if(!node1 || !node2)
        return false;
    return node1->element == node2->element && equals(node1->leftChild, node2->leftChild) && equals(node1->rightChild, node2->rightChild);
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& bt)const noexcept{
    return !(*this == bt);
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const{
    return root;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root(){
    return root;
}

template <typename Data>
void BinaryTreeLnk<Data>::Clear(){
    clearTree(root);
    root = nullptr;
}

template <typename Data>
void BinaryTreeLnk<Data>::clearTree(NodeLnk* node){
    if(!node)
        return;
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

/* ************************************************************************** */

}
