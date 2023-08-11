
namespace lasd {

/* ************************************************************************** */

//------------NODE -------------------

    // Comparison operators
    template <typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept{
        if(this->Element() != node.Element()) return false;
        bool dx = this->HasRightChild();
        bool sx = this->HasLeftChild();
        bool nDx = node.HasRightChild();
        bool nSx = node.HasLeftChild();

        if( dx == nDx && sx == nSx){
            if(sx && dx)
                return ((compareNode.LeftChild() == LeftChild()) && (compareNode.RightChild() == RightChild())); 
            else if (thisSX)
                return (compareNode.LeftChild() == LeftChild());
            else if (thisDX)
                return (compareNode.RightChild() == RightChild());
            else
                return true;          
        }
        return false;
    }

    template <typename Data>
    bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept{
        return !(*this == node);
    }

//------------------------------------
//----------- BinaryTree--------------

  // Comparison operators
  template <typename Data>
  bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept{
    if(size == bt.size)
        if(size != 0)
            return Root() == bt.Root();
        else return true;
    return false;
  }

  template <typename Data>
  bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept{
    return !(*this == bt);
  }

  // Specific member function (inherited from FoldableContainer)
  template <typename Data>
  void BinaryTree<Data>::Fold(const FoldFunctor fun, void* acc) const{
    // --------- IDK ------- ??????
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  template <typename Data>
  void BinaryTree<Data>::Map(const MapFunctor fun){
    PreOrderMap(fun);
  }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::PreOrderMap(const MapFunctor fun){
    if(size != 0) PreOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::PostOrderMap(const MapFunctor fun){
    if(size != 0) PostOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::InOrderMap(const MapFunctor fun){
    if(size != 0) InOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::BreadthMap(const MapFunctor fun){
    if(size != 0) BreadthMap(fun, &(Root()));
  }

protected:

  // Auxiliary member function (for PreOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::PreOrderMap(const MapFunctor fun, Node* node){
    if(node != nullptr){
        fun(node->Element()); 
        if(node->HasLeftChild())
            PreOrderMap(fun, &(node->LeftChild()));
        if(node->HasRightChild())
            PreOrderMap(fun, &(node->RightChild()));
    }    
  }

  /* ************************************************************************ */

  // Auxiliary member function (for PostOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::PostOrderMap(const MapFunctor fun , Node* node) {
    if(node != nullptr){
        if(node->HasLeftChild())
            PostOrderMap(fun, &(node->LeftChild()));
        if(node->HasRightChild())
            PostOrderMap(fun, &(node->RightChild()));
    }
  }

  /* ************************************************************************ */

  // Auxiliary member function (for InOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::InOrderMap(const MapFunctor fun, Node* node){
    if(node != nullptr){
    if(node->HasLeftChild())
        InOrderMap(fun, &(node->LeftChild()));

    fun(node->Element());

    if(node->HasRightChild())
        InOrderMap(fun, &(node->RightChild()));
    }
  }

  /* ************************************************************************ */

  // Auxiliary member function (for BreadthMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::BreadthMap(const MapFunctor fun, Node* node){
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

//-------------------------------------
//----------MutableBinaryTree----------------

  // Specific member function (inherited from MutableMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::Map(MutableMapFunctor fun){
    PreOrderMap(fun);
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::PreOrderMap(MutableMapFunctor fun){
    if(size != 0) PreOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::PostOrderMap(MutableMapFunctor fun) {
    if(size != 0) PostOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MutableInOrderMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::InOrderMap(MutableMapFunctor fun) {
    if(size != 0) InOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBreadthMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::BreadthMap(MutableMapFunctor fun) {
    if(size != 0) BreadthMap(fun, &(Root()));
  }

protected:

  // Auxiliary member function (for MutablePreOrderMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::PreOrderMap(MutableMapFunctor fun, Node* node){
    if(node != nullptr){
        fun(node->Element()); 
        if(node->HasLeftChild())
            PreOrderMap(fun, &(node->LeftChild()));
        if(node->HasRightChild())
            PreOrderMap(fun, &(node->RightChild()));
    }      
  }

  /* ************************************************************************ */

  // Auxiliary member function (for MutablePostOrderMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::PostOrderMap(MutableMapFunctor fun, Node* node){
    if(node != nullptr){
        if(node->HasLeftChild())
            PostOrderMap(fun, &(node->LeftChild()));
        if(node->HasRightChild())
            PostOrderMap(fun, &(node->RightChild()));
    }    
  }

  /* ************************************************************************ */

  // Auxiliary member function (for MutableInOrderMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::InOrderMap(MutableMapFunctor fun, Node* node){
    if(node != nullptr){
    if(node->HasLeftChild())
        InOrderMap(fun, &(node->LeftChild()));

    fun(node->Element());

    if(node->HasRightChild())
        InOrderMap(fun, &(node->RightChild()));
    }    
  }

  /* ************************************************************************ */

  // Auxiliary member function (for MutableBreadthMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::BreadthMap(MutableMapFunctor fun, Node* node){
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

//------------------------------------------
//-----------BTPreOrderIterator-------------

  // Specific constructors
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt){
    curr = &bt.Root();
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator& bt){
    curr = bt.curr;
    stk = bt.stk;
  }

  // Move constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(br.stk);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTPreOrderIterator<Data>::~BTPreOrderIterator(){
    Reset();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTPreOrderIterator& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator& bt){
    BTPreOrderIterator<Data> *tmp = new BTPreOrderIterator<Data>(bt);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTPreOrderIterator& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& bt) noexcept{
    BTPreOrderIterator<Data> *tmp = new BTPreOrderIterator<Data>(std::move(bt));
    std::swap(*tmp, *this);
    delete tmp;
    return *this;    
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& bt) const noexcept{
    if(curr != bt.curr) return false;
    if( stk != bt.stk) return false;
    return true;
  }

  template <typename Data>
  bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  template <typename Data>
  Data& BTPreOrderIterator<Data>::operator*() const{
    if(Terminated()) throw std::out_of_range("Fuori range!");
    return curr->Element();
  }

  template <typename Data>
  bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    return (curr == nullptr);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  template <typename Data>
  BTPreOrderIterator& BTPreOrderIterator<Data>::operator++(){
    if(Terminated()) throw std::out_of_range("Fuori range");
    if(curr->HasRightChild()) stk.Push(&(curr->RightChild()));
    if(curr->HasLeftChild()) stk.Push(&(curr->LeftChild()));
    if(stk.Empty()) curr = nullptr;
    else curr = stk.TopNPop();
    return *this;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  template <typename Data>
  void BTPreOrderIterator<Data>::Reset()noexcept{
    delete curr;
    curr = nullptr;
    stk.Clear();
  }
//--------------------------------------------
//--------------BTPreOrderMutableIterator---------

  // Specific constructors
  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const MutableBinaryTree<Data>& bt){
    curr = &bgt.Root();
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BTPreOrderMutableIterator& bt){
    stk = bt.stk;
    curr = bt.curr;
  }

  // Move constructor
  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(BTPreOrderMutableIterator&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(bt.stk);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTPreOrderMutableIterator<Data>::~BTPreOrderMutableIterator(){
    delete curr;
    curr = nullptr;
    stk.Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTPreOrderMutableIterator& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator& bt){
    BTPreOrderMutableIterator<Data> *tmp = new BTPreOrderMutableIterator<Data>(bt);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTPreOrderMutableIterator& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(br.stk);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator& bt) const noexcept{
    if(curr != bt.curr || stk != bt.stk) return false;
    return true;
  }

  template <typename Data>
  bool BTPreOrderMutableIterator<Data>::operator!=(const BTPreOrderMutableIterator& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  template <typename Data>
  Data& BTPreOrderMutableIterator<Data>::operator*(){
    if(curr == nullptr) throw std::out_of_range("Terminated");      
    return current->Element();
}

//---------------------------------------------
//--------------BTPostOrderIterator------------

  // Specific constructors
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt){
    curr = &bt.Root();
    last = curr;
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& bt){
    curr = bt.curr;
    stk = bt.stk;
    last = bt.last;
  }

  // Move constructor
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& bt) noexcept{
    std::swap(curr, bt.curr);
    std::swap(last, bt.last);
    stk = std::move(bt.stk);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTPostOrderIterator<Data>::~BTPostOrderIterator(){
    Reset();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTPostOrderIterator& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& bt){
    curr = bt.curr;
    stk = bt.stk;
    last = bt.last;
    return *this;    
  }

  // Move assignment
  template <typename Data>
  BTPostOrderIterator& BTPostOrderIterator<Data>::operator=(BTPostOrderIterato&& bt) noexcept{
    BTPostOrderIterator<Data> *tmp = new BTPostOrderIterator<Data>(bt);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;   
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator& bt) const noexcept{
    if(curr != bt.curr || last != bt.last) return false;
    if(stk != bt.stk) return false;
    return true;
  }
  
  template <typename Data>
  bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  template <typename Data>
  Data& BTPostOrderIterator<Data>::operator*() const{
    if(Terminated()) throw std::out_of_range("Fuori range");
    return curr->Element();    
  }

  template <typename Data>
  bool BTPostOrderIterator<Data>::Terminated() const noexcept{
    return (curr == nullptr);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  template <typename Data>
  BTPostOrderIterator& BTPostOrderIterator<Data>::operator++(){
    if(stk.Empty()){
        curr = nullptr;
        return *this;
    }
    else{
        if((stk.Top()->HasRightChild()) && (&(stk.Top()->RightChild())) != curr){
            curr = &(stk.Top()->RightChild());
            curr = LeftMostLeft(curr, stk)
            return *this;
        }
        else{
            curr = stk.TopNPop();
            return *this;
        }
    }
  }

template <typename Data> ///////// aggiubnto io di supporto
BinaryTree<Data>::Node* LeftMostLeft(Node* node, std::stack<Node*>& stk) {
    while (node) {
        stk.Push(node);
        if (node->left)
            node = node->left;
        else
            node = node->right;
    }
    if (!stk.Empty()) {
        Node* leftmost = stk.Top();
        stk.Pop();
        return leftmost;
    }
    return nullptr;
}


  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  template <typename Data>
  void BTPostOrderIterator<Data>::Reset() noexcept{
    stk.Clear();
    delete curr;
    delete last;
    curr = nullptr;
    last = nullptr;
  }

//---------------------------------------------
//------------BTPostOrderMutableIterator-------

  // Specific constructors
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const MutableBinaryTree<Data> bt) {
    curr = &bt.Root();
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BTPostOrderMutableIterator& bt) {
    curr = bt.curr;
    stk = bt.stk;
    last = bt.last;
  }

  // Move constructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(BTPostOrderMutableIterator&& bt) noexcept{
    std::swap(curr, bt.curr);
    std::swap(last, bt.last);
    stk = std::move(bt.stk);    
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::~BTPostOrderMutableIterator() {
    stk.Clear();
    delete curr;
    delete last;
    curr = nullptr;
    last = nullptr;
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTPostOrderMutableIterator& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& bt) {
    curr = bt.curr;
    stk = bt.stk;
    last = bt.last;
    return *this;  
  }

  // Move assignment
  template <typename Data>
  BTPostOrderMutableIterator& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& bt) noexcept{
    BTPostOrderMutableIterator<Data> *tmp = new BTPostOrderMutableIterator<Data>(bt);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;     
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTPostOrderMutableIterator<Data>::operator==(const BTPostOrderMutableIterator& bt) const noexcept{
    if(curr != bt.curr || last != bt.last) return false;
    if(stk != bt.stk) return false;
    return true; 
  }
  
  template <typename Data>
  bool BTPostOrderMutableIterator<Data>::operator!=(const BTPostOrderMutableIterator& bt) const noexcept{
    return !(*this == bt);    
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  template <typename Data>
  Data& BTPostOrderMutableIterator<Data>::operator*(){
    if(curr == nullptr) throw std::out_of_range("Fuori range");
    return curr->Element(); 
  }

//---------------------------------------------

/* ************************************************************************** */

}
