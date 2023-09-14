
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
     curr = &bt.Root();
     init = curr;

  //   stk.Push(&bt.Root());
    // curr = stk.Top();
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator& bt){
    curr = bt.curr;
    stk = bt.stk;
init = curr;
  }

  // Move constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& bt) noexcept{

    curr = bt.curr;
    stk = std::move(bt.stk);
    init = curr;
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTPreOrderIterator<Data>::~BTPreOrderIterator(){
    stk.Clear();
    curr = nullptr;
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& bt){
    curr = bt.curr;
    stk = bt.stk;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& bt) noexcept{
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
    return (curr == nullptr );
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++(){
    // if(!stk.Empty()){
    //   curr = stk.Top();
    //   stk.Pop();

    //   if(curr->HasRightChild()) stk.Push(&(curr->RightChild()));
    //   if(curr->HasLeftChild()) stk.Push(&(curr->LeftChild()));
    // }else curr = nullptr;
    // return *this;
    //-------------------------------------------
    if(curr != nullptr){
      if(curr->HasRightChild()) stk.Push(&(curr->RightChild()));
      if(curr->HasLeftChild()) stk.Push(&(curr->LeftChild()));
      if(!stk.Empty()){
        curr = stk.Top();
        stk.Pop();  
      }  else curr = nullptr;
    }
    return *this;
    //----------------------------------------------
  //   if(curr->HasLeftChild()){
  //     if(curr->HasRightChild()) stk.Push(&(curr->RightChild()));
  //     curr = &(curr->LeftChild());
  //     return *this;
  //   }
  //   if(curr->HasRightChild()){
  //     curr = &(curr->RightChild());
  //     return *this;
  //   }
  //   if(!stk.Empty()){
  //     curr = stk.Top();
  //     stk.Pop();
  //     return *this;
  //   }else{
  //     curr = nullptr;
  //     return *this;
  //   }
   }

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  template <typename Data>
  void BTPreOrderIterator<Data>::Reset()noexcept{
    curr = init;
    stk.Clear();
  }
//--------------------------------------------
//--------------BTPreOrderMutableIterator---------

  // Specific constructors
  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator( MutableBinaryTree<Data>& bt) : BTPreOrderIterator<Data>(bt){
    // if(curr != nullptr)
    //   stk.Push(curr);
   // curr = &bt.Root();
    }

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
    stk.Clear();
    curr = nullptr;
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

//Function inizializzazione
template <typename Data>
void BTPostOrderIterator<Data>::inizializzazione() {
    while (curr->HasLeftChild()) {
        stk.Push(curr);
        curr = &(curr->LeftChild());
    }

    if(curr->HasRightChild()) {
        stk.Push(curr);
        curr = &(curr->RightChild());
        inizializzazione();
    }
}

  // Specific constructors
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt){
    curr = &bt.Root();
    last = nullptr;
    init = curr;
    
    if (curr) {
        while (curr->HasLeftChild() || curr->HasRightChild()) {
            if (curr->HasLeftChild()) {
                stk.Push(curr);
                curr = &(curr->LeftChild());
            } else if (curr->HasRightChild()) {
                stk.Push(curr);
                curr = &(curr->RightChild());
            }
        }
    }
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& bt){
    curr = bt.curr;
    stk = bt.stk;
    last = bt.last;
    init = curr;
  }

  // Move constructor
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& bt) noexcept{
    std::swap(curr, bt.curr);
    std::swap(last, bt.last);
    stk = std::move(bt.stk);
    init = curr;
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTPostOrderIterator<Data>::~BTPostOrderIterator(){
    stk.Clear();
    curr = nullptr;
    last = nullptr;
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& bt){
    curr = bt.curr;
    stk = bt.stk;
    last = bt.last;
    init = curr;
    return *this;    
  }

  // Move assignment
  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& bt) noexcept{
    std::swap(curr, bt.curr);
    std::swap(last, bt.last);
    stk = std::move(bt.stk);
    init = curr;
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
      if(Terminated())
        throw std::out_of_range("Iterator PostOrder terminated.");

    if(stk.Empty()){
        curr = nullptr;
        last = nullptr;
    }else{
        curr = stk.TopNPop();
        if(curr->HasRightChild() && !(&(curr->RightChild())==last)){
            stk.Push(curr);
            curr = &(curr->RightChild());
            inizializzazione();
        }
    }
    last = curr;
    return *this;

  }



  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  template <typename Data>
  void BTPostOrderIterator<Data>::Reset() noexcept{
    // Puliamo la pila
    stk.Clear();
    curr = init;
    last = nullptr;

    // Se l'albero non è vuoto, eseguo l'inizializzazione
    if (curr) {
        while (curr->HasLeftChild() || curr->HasRightChild()) {
            if (curr->HasLeftChild()) {
                stk.Push(curr);
                curr = &(curr->LeftChild());
            } else if (curr->HasRightChild()) {
                stk.Push(curr);
                curr = &(curr->RightChild());
            }
        }
    }
  }

//---------------------------------------------
//------------BTPostOrderMutableIterator-------

  // Specific constructors
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator( MutableBinaryTree<Data>& bt) : BTPostOrderIterator<Data>(bt){
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BTPostOrderMutableIterator& bt) : BTPostOrderIterator<Data>(bt){

  }

  // Move constructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(BTPostOrderMutableIterator&& bt) noexcept{
    std::swap(curr, bt.curr);
    std::swap(last, bt.last);
    init = curr;
    stk = std::move(bt.stk);    
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::~BTPostOrderMutableIterator() {
    stk.Clear();
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
    init = curr;
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
    init = curr;
    while(curr->HasLeftChild()){
      stk.Push(curr);
      curr = &(curr->LeftChild());
    }
    if(!curr->HasLeftChild() && curr->HasRightChild())
      stk.Push(curr);
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& bt){
    curr = &bt.Root();
    stk = bt.stk;
    init = curr;
  }

  // Move constructor
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(bt.stk);
    init = curr;
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTInOrderIterator<Data>::~BTInOrderIterator(){
    stk.Clear();
    curr = nullptr;
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
    std::swap(init, bt.init);
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
    curr = init; 

    //riposiziono l iteratore sul nodo più a sinistra
    while (curr && curr->HasLeftChild()) {
      stk.Push(curr);
      curr = &(curr->LeftChild());
    }
  }

//---------------------------------------------
//------------------BTInOrderMutableIterator---

  // Specific constructors
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator( MutableBinaryTree<Data>& bt) : BTInOrderIterator<Data>(bt){
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>& bt) : BTInOrderIterator<Data>(bt){

  }

  // Move constructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    stk = std::move(bt.stk);
    init = curr;
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::~BTInOrderMutableIterator(){
    curr = nullptr;
    stk.Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator<Data>& bt){
    curr = bt.curr;
    stk = bt.stk;
    init = curr;
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
    init = curr;
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& bt){
    curr = bt.curr;
    que = bt.que;
    init = curr;
  }

  // Move constructor
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& bt) noexcept{
    std::swap(curr, bt.curr);
    que = std::move(bt.que);
    init = curr;
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTBreadthIterator<Data>::~BTBreadthIterator(){
    que.Clear();
    curr = nullptr;
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
    curr = init;
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
    que.Clear();
    curr = nullptr;
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
