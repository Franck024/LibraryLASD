
namespace lasd {

/* ************************************************************************** */

/*********************** NODE *************************************/
/* ************************************************************************** */
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const &Node node) const noexcept{
    if(node.Element() == this->Element()){
        bool thisDx = this->HasRightChild();
        bool thisSx = this->HasLeftChild();
        bool nodeDx = node.HasRightChild();
        bool nodeSx = node.HasLeftChild();

        if( thisDx == nodeDx && thisSx == nodeSx){
            if(thisSx && thisDx)
                return ((node.LeftChild() == LeftChild()) && (node.RightChild() == RightChild()));
            else if(thisSx)
                return (node.LeftChild() == LeftChild());
            else if(thisDx)
                return (node.RightChild() == RightChild());
            else return true;
        }
    } return false;
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const &Node node) const noexcept{
    return !(*this == node);
}

template <typename Data>
bool BinaryTree<Data>::Node::IsLeaf() const noexcept{
    return !(HasLeftChild() || HasRightChild());
}
/* ************************************************************************** */
/* ************************************************************************** */

/***********************BinaryTree****************************/
/* ************************************************************************** */

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data> &ab)const noexcept{
    if(size == ab.size)
        if(size != 0)
            return Root() == ab.Root();
        else return true;
    return false;
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data> &ab)const noexcept{
    return !(*this == ab);
}

//********* Metodi inerenti a FoldableContainer
template <typename Data>
void BinaryTree<Data>::Fold(const FoldFunctor& fun , void* acc) const{
    // if(size == 0)
    //     return;
    // if()
}

//********* '' ''        ''   MappableContainer
template <typename Data>
void BinaryTree<Data>::Map(const MapFunctor& fun) const{

}

//*******     ''       ''    PreOrderMap
template <typename Data>
void BinaryTree<Data>::PreOrderMap(MapFunctor){
    if(size != 0)
        PreOrderMap(fun, &(Root()));
}

template <typename Data>
void BinaryTree<Data>::PreOrderMap(MapFunctor fun, Node* node ){
    if(node != nullptr){
        fun(node->Element()); 
        if(node->HasLeftChild())
            PreOrderMap(fun, &(node->LeftChild()));
        if(node->HasRightChild())
            PreOrderMap(fun, &(node->RightChild()));
    }
}

//***********   ''     ''    PostOrderMap
template <typename Data>
void BinaryTree<Data>::PostOrderMap(MapFunctor fun){
    if(size != 0)
        PostOrderMap(fun, &(Root()));


template <typename Data>
void BinaryTree<Data>::PostOrderMap(MapFunctor fun, Node* node){
    if(node != nullptr){
        if(node->HasLeftChild())
            PostOrderMap(fun, &(node->LeftChild()));
        if(node->HasRightChild())
            PostOrderMap(fun, &(node->RightChild()));
    }
}

//*************   ''     ''      InOrderMap
template <typename Data>
void BinaryTree<Data>::InOrderMap(MapFunctor fun) const{
    if(size != 0)
        InOrderMap(fun, &(Root()));
}

template <typename Data>
void BinaryTree<Data>::InOrderMap(MapFunctor fun, Node* node) {
    if(node != nullptr){
        if(node->HasLeftChild())
            InOrderMap(fun, &(node->LeftChild()));

        fun(node->Element());

        if(node->HasRightChild())
            InOrderMap(fun, &(node->RightChild()));
    }
}

//************* ''        ''          BreadthMap
template <typename Data>
void BinaryTree<Data>::BreadthMap(MapFunctor fun){
    if(size != 0)
        BreadthMap(fun, &(Root()));
}

template <typename Data>
void BinaryTree<Data>::BreadthMap(MapFunctor fun, Node* node) {
    lasd::QueueLst<Node*> coda;
    coda.Enqueue(node);
    Node* tmp;

    while(!(coda.Empty())){
        tmp = coda.HeadNDequeue();
        fun(tmp->Element());
        
        if(tmp->HasLeftChild())
            coda.Enqueue(&(tmp->LeftChild()));
        
        if(tmp->HasRightChild())
            coda.Enqueue(&(tmp->RightChild()));
  }
}

/* ************************************************************************** */
/* ************************************************************************** */
}
