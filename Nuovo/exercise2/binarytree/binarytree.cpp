
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
                return ((node.LeftChild() == LeftChild()) && (node.RightChild() == RightChild())); 
            else if (sx)
                return (node.LeftChild() == LeftChild());
            else if (dx)
                return (node.RightChild() == RightChild());
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
    Fold(fun, acc, &Root());
  }

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  template <typename Data>
  void BinaryTree<Data>::Map( MapFunctor fun)const{
    PreOrderMap(fun);
  }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::PreOrderMap( MapFunctor fun)const{
    if(size != 0) PreOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::PostOrderMap( MapFunctor fun)const{
    if(size != 0) PostOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::InOrderMap( MapFunctor fun)const{
    if(size != 0) InOrderMap(fun, &(Root()));
  }

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::BreadthMap( MapFunctor fun)const{
    if(size != 0) BreadthMap(fun, &(Root()));
  }

  // Auxiliary member function (for PreOrderMappableContainer)
  template <typename Data>
  void BinaryTree<Data>::PreOrderMap( MapFunctor fun, Node* node)const{
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
  void BinaryTree<Data>::Fold(const FoldFunctor fun, void* acc, Node* node ) const{
    if (node != nullptr) {
        fun(node->Element(), acc);
        Fold(fun, acc, &node->LeftChild());
        Fold(fun, acc, &node->RightChild()); 
    }
  }

  template <typename Data>
  void BinaryTree<Data>::PostOrderMap( MapFunctor fun , Node* node) const{
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
  void BinaryTree<Data>::InOrderMap( MapFunctor fun, Node* node)const{
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
  void BinaryTree<Data>::BreadthMap( MapFunctor fun, Node* node)const{
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

  // Auxiliary member function (for MutablePreOrderMappableContainer)
  template <typename Data>
  void MutableBinaryTree<Data>::PreOrderMap(MutableMapFunctor fun, MutableNode* node){
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
  void MutableBinaryTree<Data>::PostOrderMap(MutableMapFunctor fun, MutableNode* node){
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
  void MutableBinaryTree<Data>::InOrderMap(MutableMapFunctor fun, MutableNode* node){
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
  void MutableBinaryTree<Data>::BreadthMap(MutableMapFunctor fun, MutableNode* node){
    lasd::QueueLst<MutableNode*> coda;
    coda.Enqueue(node);
    MutableNode* tmp;

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
    // curr = &bt.Root();

    stk.Push(&bt.Root());
    curr = stk.Top();
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator& bt){
    // curr = bt.curr;
    // stk = bt.stk;

    curr(bt.curr);
    stk(bt.stk);
  }

  // Move constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& bt) noexcept{
    // std::swap(curr, bt.curr);
    // stk = std::move(bt.stk);

    curr(bt.curr);
    stk(std::move(bt.stk));
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
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& bt){
    // BTPreOrderIterator<Data> *tmp = new BTPreOrderIterator<Data>(bt);
    // std::swap(*tmp, *this);
    // delete tmp;
    // return *this;

    curr = bt.curr;
    stk = bt.stk;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& bt) noexcept{
    // BTPreOrderIterator<Data> *tmp = new BTPreOrderIterator<Data>(std::move(bt));
    // std::swap(*tmp, *this);
    // delete tmp;
    // return *this;    

    curr = bt.curr;
    stk = std::move(bt.stk);
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
  const Data& BTPreOrderIterator<Data>::operator*() const{
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
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++(){
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
    curr = nullptr;
    stk.Clear();
  }
//--------------------------------------------
//--------------BTPreOrderMutableIterator---------

  // Specific constructors
  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const MutableBinaryTree<Data>& bt) : BTPreOrderIterator<Data>(bt){
    std::cout << "-----------------HERE-    -------------" << std::endl;}

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& bt) : BTPreOrderIterator<Data>(bt){
    // stk = bt.stk;
    // curr = bt.curr;
  }

  // Move constructor
  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& bt) noexcept{
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
  BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator<Data>& bt){
    BTPreOrderMutableIterator<Data> *tmp = new BTPreOrderMutableIterator<Data>(bt);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(bt.stk);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator<Data>& bt) const noexcept{
    if(curr != bt.curr || stk != bt.stk) return false;
    return true;
  }

  template <typename Data>
  bool BTPreOrderMutableIterator<Data>::operator!=(const BTPreOrderMutableIterator<Data>& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  template <typename Data>
  Data& BTPreOrderMutableIterator<Data>::operator*(){
    if(curr == nullptr) throw std::out_of_range("Terminated");      
    return curr->Element();
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
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& bt){
    curr = bt.curr;
    stk = bt.stk;
    last = bt.last;
    return *this;    
  }

  // Move assignment
  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& bt) noexcept{
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
  const Data& BTPostOrderIterator<Data>::operator*() const{
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
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){
    if (!stk.Empty()) {
        // Continua ad estrarre nodi dallo stack finché non si trova un nodo valido
        while (curr != nullptr || !stk.Empty()) {
            if (curr != nullptr) {
                stk.Push(curr);
                curr = &(curr->LeftChild());
            } else {
                struct BinaryTree<Data>::Node* temp = stk.Top();
                if (&(temp->RightChild()) != nullptr && &(temp->RightChild()) != last) {
                    curr = &(temp->RightChild());
                } else {
                    curr = nullptr;
                    last = temp;
                    stk.Pop();
                }
            }
        }
    }

    return *this;
  }



  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  template <typename Data>
  void BTPostOrderIterator<Data>::Reset() noexcept{
    stk.Clear();
    curr = nullptr;
    last = nullptr;
  }

//---------------------------------------------
//------------BTPostOrderMutableIterator-------

  // Specific constructors
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const MutableBinaryTree<Data>& bt) : BTPostOrderIterator<Data>(bt){
    curr = nullptr;
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
  BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& bt) {
    curr = bt.curr;
    stk = bt.stk;
    last = bt.last;
    return *this;  
  }

  // Move assignment
  template <typename Data>
  BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& bt) noexcept{
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
//-------------------BTInOrderIterator---------

  // Specific constructors
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt){
    curr = &bt.Root();
    while(curr->HasLeftChild()){
      stk.Push(curr);
      curr = &(curr->LeftChild());
    }
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& bt){
    curr = &bt.Root();
    stk = bt.stk;
  }

  // Move constructor
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(bt.stk);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTInOrderIterator<Data>::~BTInOrderIterator(){
    Reset();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& bt){
    BTInOrderIterator<Data> *tmp = new BTInOrderIterator<Data>(bt);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& bt) const noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(bt.stk);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& bt) const noexcept{
    if(curr != bt.curr || stk != bt.stk) return false;
    return true;
  }

  template <typename Data>
  bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  template <typename Data>
  const Data& BTInOrderIterator<Data>::operator*() const{
    if(Terminated()) throw std::out_of_range("Termine");
    return curr->Element();
  }

  template <typename Data>
  bool BTInOrderIterator<Data>::Terminated() const noexcept{
    return (curr == nullptr);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++(){
    if(Terminated()) throw std::out_of_range("Terminato");
    if(curr->HasRightChild()){
      curr = &(curr->RightChild());
      while(curr->HasLeftChild()){
      stk.Push(curr);
      curr = &(curr->LeftChild());
      }
    }
    else{
      if(stk.Empty()) curr = nullptr;
      else curr = stk.TopNPop();
    }
    return *this;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  template <typename Data>
  void BTInOrderIterator<Data>::Reset() noexcept{
    stk.Clear();
    curr = nullptr;
  }

//---------------------------------------------
//------------------BTInOrderMutableIterator---

  // Specific constructors
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(const MutableBinaryTree<Data>& bt) : BTInOrderIterator<Data>(bt){
    curr = nullptr;
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>& bt){
    curr = bt.curr;
    stk = bt.stk;
  }

  // Move constructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(bt.stk);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::~BTInOrderMutableIterator(){
    delete curr;
    curr = nullptr;
    stk.Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator<Data>& bt){
    curr = bt.curr;
    stk = bt.stk;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(bt.stk);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTInOrderMutableIterator<Data>::operator==(const BTInOrderMutableIterator<Data>& bt) const noexcept{
    if(curr != bt.curr || stk != bt.stk) return false;
    return true;
  }
  
  template <typename Data>
  bool BTInOrderMutableIterator<Data>::operator!=(const BTInOrderMutableIterator<Data>& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  template <typename Data>
  Data& BTInOrderMutableIterator<Data>::operator*(){
    if(curr == nullptr) throw std::out_of_range("Terminato");
    return curr->Element();
  }

//---------------------------------------------
//------------BTBreadthIterator----------------

  // Specific constructors
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt){
    curr = &bt.Root();
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& bt){
    curr = bt.curr;
    que = bt.que;
  }

  // Move constructor
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    que = std::move(bt.que);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTBreadthIterator<Data>::~BTBreadthIterator(){
    Reset();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& bt){
    curr = bt.curr;
    que = bt.que;  
    return *this;  
  }

  // Move assignment
  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    que = std::move(bt.que);    
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& bt) const noexcept{
    if(curr != bt.curr || que != bt.que) return false;
    return true;
  }
  
  template <typename Data>
  bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  template <typename Data>
  const Data& BTBreadthIterator<Data>::operator*() const{
    if(Terminated()) throw std::out_of_range("Terminated");

    return curr->Element();
  }

  template <typename Data>
  bool BTBreadthIterator<Data>::Terminated() const noexcept{
    return (curr == nullptr);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++(){
    if(Terminated()) throw std::out_of_range("ITerminato");
    
    if(curr->HasLeftChild()) que.Enqueue(&(curr->LeftChild()));
    
    if(curr->HasRightChild()) que.Enqueue(&(curr->RightChild()));
    
    if(que.Empty()) curr = nullptr;
    else curr = que.HeadNDequeue();

    return (*this);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  template <typename Data>
  void BTBreadthIterator<Data>::Reset() noexcept{
    curr = nullptr;
    que.Clear();
  }

//---------------------------------------------
//-----------BTBreadthMutableIterator----------

  // Specific constructors
  template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const MutableBinaryTree<Data>& bt) : BTBreadthIterator<Data>(bt){
    curr = nullptr;
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>& bt) {
    curr = bt.curr;
    que = bt.que;
  }

  // Move constructor
  template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    que = std::move(bt.que);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTBreadthMutableIterator<Data>::~BTBreadthMutableIterator(){
    delete curr;
    curr= nullptr;
    que.Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator<Data>& bt){
    curr = bt.curr;
    que = bt.que;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    que = std::move(bt.que);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTBreadthMutableIterator<Data>::operator==(const BTBreadthMutableIterator<Data>& bt) const noexcept{
    if(curr != bt.curr || que != bt.que) return false;
    return true;
  }
  
  template <typename Data>
  bool BTBreadthMutableIterator<Data>::operator!=(const BTBreadthMutableIterator<Data>& bt) const noexcept{
    return !(*this == bt);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  template <typename Data>
  Data& BTBreadthMutableIterator<Data>::operator*(){
    if(curr == nullptr) throw std::out_of_range("Terminated");
    return curr->Element();
}

//----------------------------------------------

/* ************************************************************************** */

}
