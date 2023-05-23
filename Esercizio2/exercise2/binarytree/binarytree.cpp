
namespace lasd {

/* ************************************************************************** */

/*********************** NODE *************************************/
/* ************************************************************************** */
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept{
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
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept{
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
void BinaryTree<Data>::PreOrderMap( MapFunctor fun) {
    if(size != 0)
        PreOrderMap(fun, &(Root()));
}

template <typename Data>
void BinaryTree<Data>::PreOrderMap( MapFunctor fun, Node* node ) {
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
void BinaryTree<Data>::PostOrderMap(MapFunctor fun) {
    if(size != 0)
        PostOrderMap(fun, &(Root()));
}

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
void BinaryTree<Data>::InOrderMap(MapFunctor fun, Node* node) const{
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
void BinaryTree<Data>::BreadthMap(MapFunctor fun) {
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

template <typename Data>
bool BinaryTree<Data>::Exists(const Data& value) const noexcept{
    return ExistsRecursive(&(Root()), value);
}

template <typename Data>
bool BinaryTree<Data>::ExistsRecursive(Node* node, const Data& value) const noexcept{
    if(!(node->IsLeaf()))
        return false;
    if(node->Element() == value)
        return true;
    bool existsLeft = ExistsRecursive(&(node->LeftChild()), value);
    bool existsRight = ExistsRecursive(&(node->RightChild()), value);
    return existsLeft || existsRight;
}

//*********************** MutableBinaryTree *************************
//*******************************************************************

// Specifiche funzioni membro

template <typename Data>
void MutableBinaryTree<Data>::Map(const MutableMapFunctor& f) const {
  MutableBinaryTree<Data>& nonConstTree = const_cast<MutableBinaryTree<Data>&>(*this);
  nonConstTree.PreOrderMap(const_cast<MutableMapFunctor&>(f), &(nonConstTree.Root()));
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap( MutableMapFunctor f)  {
    this->PreOrderMap(f, &(Root()));
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap( MutableMapFunctor f, MutableNode* node) {
    if (node) {
        f(node->Element());
        PreOrderMap(f, &(node->LeftChild()));
        PreOrderMap(f, &(node->RightChild()));
    }
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MutableMapFunctor f) {
    this->PostOrderMap(f, &(Root()));
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MutableMapFunctor f, MutableNode* node) {
    if (node) {
        PostOrderMap(f, &(node->LeftChild()));
        PostOrderMap(f, &(node->RightChild()));
        f(node->Element());
    }
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(const MutableMapFunctor f)  {
    this->InOrderMap(f, &(Root()));
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(const MutableMapFunctor f, MutableNode* node)  {
    if (node) {
        InOrderMap(f, &(node->LeftChild()));
        f(node->Element());
        InOrderMap(f, &(node->RightChild()));
    }
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(const MutableMapFunctor f) {
    if(size != 0){
        BreadthMap(f, &(Root()));
    }
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(const MutableMapFunctor f, MutableNode* node) {
    QueueLst<MutableNode*> q;
    q.Enqueue(node);

    while(!q.Empty()){
        MutableNode* current = q.Head();
        q.Dequeue();

        f(current->Element());

        if(current->HasLeftChild()){
            q.Enqueue(&(current->LeftChild()));
        }
        if(current->HasRightChild()){
            q.Enqueue(&(current->RightChild()));
        }
    }
}



//*********************** BTPreOrderIterator ************************
//*******************************************************************
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &bt){
    current = &bt.Root();
}

// copy constr
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data> &ab){
    current = ab.current;
    stk = ab.stack;
}

//move constr
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& ab) noexcept{
    std::swap(current, ab.current);
    stk = std::move(ab.stk);
}

//distruttore
template <typename Data>
BTPreOrderIterator<Data>::~BTPreOrderIterator(){
    stk.Clear();
    delete current;
    current = nullptr;
}

//copy ass
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& ab){
    BTPreOrderIterator<Data> *tmp = new BTPreOrderIterator<Data>(ab);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> &&ab) noexcept {
    std::swap(current, ab.current);
    stk = std::move(ab.stk);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> &ab) const noexcept {
    if(current!=ab.current || stk != ab.stk)
        return false;
    return true;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> &ab) const noexcept {
    return !(*this==ab);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Terminated");
        
    return current->Element();
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
    return (current == nullptr);
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Iterator PreOrder terminated.");

    if(current->HasRightChild())
        stk.Push(&(current->RightChild()));
    
    if(current->HasLeftChild())
        stk.Push(&(current->LeftChild()));

    if(stk.Empty())
        current = nullptr;
    else
        current = stk.TopNPop(); 
    
    return (*this);
}

template<typename Data>
void BTPreOrderIterator<Data>::Reset() const noexcept {
    stk.Clear();
    if (this->Root() != nullptr) {
        stk.Push(this->Root());
        current = this->Root();
    }
    else {
        current = nullptr;
    }
}


//******************************BTPreOrderMutableIterator******************************
//*************************************************************************************

// Specific constructors
template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const MutableBinaryTree<Data>& tree) :
    BTPreOrderIterator<Data>(tree) // Call the base class constructor
{}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& other) :
    BTPreOrderIterator<Data>(other) // Call the base class constructor
{}

// Move constructor
template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& other) noexcept :
    BTPreOrderIterator<Data>(std::move(other)) // Call the base class constructor
{}

/* ************************************************************************ */

// Destructor
template <typename Data>
BTPreOrderMutableIterator<Data>::~BTPreOrderMutableIterator() {}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator<Data>& other) {
    BTPreOrderIterator<Data>::operator=(other); // Call the base class assignment operator
    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator<Data>&& other) noexcept {
    BTPreOrderIterator<Data>::operator=(std::move(other)); // Call the base class assignment operator
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator<Data>& other) const noexcept {
    return BTPreOrderIterator<Data>::operator==(other); // Call the base class comparison operator
}

template <typename Data>
bool BTPreOrderMutableIterator<Data>::operator!=(const BTPreOrderMutableIterator<Data>& other) const noexcept {
    return BTPreOrderIterator<Data>::operator!=(other); // Call the base class comparison operator
}

/* ************************************************************************ */

// Specific member functions (inherited from MutableIterator)

template <typename Data>
Data& BTPreOrderMutableIterator<Data>::operator*() const {
    if (this->current == nullptr) {
        throw std::out_of_range("Iterator out of range");
    }
    return this->current->element;
}

//************************** BTPostOrderIterator ****************************
//***************************************************************************

// Specific constructors
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) : current(nullptr), last(nullptr) {
    // Push the root of the tree onto the stack
    if (bt.current != nullptr) {
        stk.Push(&bt.Root());
    }
}


/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data> &ab) {
    current = ab.current;
    last = ab.last;
    stk = ab.stk;
}

// Move constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data> &&ab) noexcept {
    std::swap(current,ab.current);
    std::swap(last,ab.last);
    stk = std::move(ab.stk);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BTPostOrderIterator<Data>::~BTPostOrderIterator() {
    stk.Clear();
    delete current ;
    current = nullptr;;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> &ab) {
    BTPostOrderIterator<Data> *tmp = new BTPostOrderIterator<Data>(ab);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> &&ab) noexcept {
    std::swap(current, ab.current);
    std::swap(last,ab.last);
    stk = std::move(ab.stk);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> &ab) const noexcept {
    if(current!=ab.current || last!=ab.last || stk!=ab.stk)
        return false;
    return true;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> &ab) const noexcept {
    return !(*this==ab);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Terminated");

    return current->Element();
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ************************************************************************ */

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Iterator PostOrder terminated.");

    if(stk.Empty()){
        current = nullptr;
        last = nullptr;
    }else{
        current = stk.TopNPop();
        if(current->HasRightChild() && !(&(current->RightChild())==last)){
            stk.Push(current);
            current = &(current->RightChild());
            while (current->HasLeftChild()) {
                stk.Push(current);
                current = &(current->LeftChild());
            }

            if(current->HasRightChild()) {
                stk.Push(current);
                current = &(current->RightChild());
                while(current->HasLeftChild() || current->HasRightChild()) {
                    if(current->HasLeftChild()) {
                        stk.Push(current);
                        current = &(current->LeftChild());
                    } else {
                        stk.Push(current);
                        current = &(current->RightChild());
                    }
                }
            }
        }
    }
    last = current;
    return (*this);
}


template <typename Data>
void BTPostOrderIterator<Data>::Reset() const noexcept {
    // Svuota lo stack
    while (!stk.Empty()) {
        stk.Pop();
    }

    // Reimposta i puntatori
    current = this->Root();
    last = nullptr;
}

//************************** BTPostOrderMutableIterator ************************
//******************************************************************************
template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const MutableBinaryTree<Data>& tree) {
    this->current = nullptr;
    this->last = nullptr;
    // Push the root of the tree onto the stack
    if (!tree.Empty()) {
        this->stk->Push(&tree.Root());
    }
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data>& other) {
    this->stk(other.stk); 
    this->current = other.current;
    this->last = other.last;
  }

  // Move constructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data>&& other) noexcept{
    this->stk(std::move(other.stk));
    this->current = other.current;
    this->last = other.last;    
    other.current = nullptr;
    other.last = nullptr;
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTPostOrderMutableIterator<Data>::~BTPostOrderMutableIterator() {}

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator<Data>& other){
    this->stk = other.stk;
    this->current = other.current;
    this->last = other.last;
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator<Data>&& other) noexcept{
    this->stk = std::move(other.stk);
    std::swap(this->current, other.current);
    std::swap(this->last, other.last);
    other.current = nullptr;
    other.last = nullptr;
    delete other.stk;
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool BTPostOrderMutableIterator<Data>::operator==(const BTPostOrderMutableIterator<Data>& other) const noexcept{
    return (this->current == other.current && this->last == other.last);
  }

template <typename Data>
  bool BTPostOrderMutableIterator<Data>::operator!=(const BTPostOrderMutableIterator<Data>& other) const noexcept{
    return !(*this == other);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
template <typename Data>
  Data& BTPostOrderMutableIterator<Data>::operator*() const{
    if (this->Terminated()) {
      throw std::out_of_range("Iterator out of range");
    }
    return this->current->Element();
  }

//************************** BTInOrderIterator ********************************
//*****************************************************************************

// Specific constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &bt) : current(nullptr), stk(){
    typename BinaryTree<Data>::Node* root = bt.Root();
    while (root != nullptr) {
        stk.Push(root);
        root = &root->LeftChild();
    }
    if (!stk.Empty()) {
        current = stk.Top();
    }
}


/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data> &ab) {
    current = ab.current;
    stk = ab.stk;
}

// Move constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> &&ab) noexcept {
    std::swap(current,ab.current);
    stk = std::move(ab.stk);
}
/* ************************************************************************ */

// Destructor
template <typename Data>
BTInOrderIterator<Data>::~BTInOrderIterator() {
        stk.Clear();
    current = nullptr;;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> &ab) {
    BTInOrderIterator<Data> *tmp = new BTInOrderIterator<Data>(ab);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> &&ab) noexcept {
    std::swap(this->current, ab.current);
    this->stk = std::move(ab.stk);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> &ab) const noexcept {
    if(current!=ab.current || stk!=ab.stk)
        return false;
    return true;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data> &ab) const noexcept {
    return !(*this==ab);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Terminated");

    return current->Element();
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ************************************************************************ */

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
    if (stk.Empty() && !current) {  // empty iterator
        throw std::out_of_range("Incrementing empty iterator");
    }

    if (current && current->HasRightChild()) {  // go to the RightChild subtree
        stk.Push(current);
        current = &current->RightChild();
        while (current->HasLeftChild()) {
            stk.Push(current);
            current = &current->LeftChild();
        }
    } else if (!stk.Empty()) {  // go up in the tree
        current = stk.Top();
        stk.Pop();
    } else {  // end of iteration
        current = nullptr;
    }
    return *this;
}

template <typename Data>
void BTInOrderIterator<Data>::Reset() const noexcept {
    // Svuota lo stack e riposiziona il puntatore alla radice dell'albero
    stk.Clear();
    current = &(this->Root());
    // Aggiungi tutti i nodi del sottoalbero sinistro alla pila
    while (current != nullptr) {
        stk.Push(current);
        current = &(current->LeftChild());
    }
}

//*************************** BTInOrderMutableIterator ************************
//*****************************************************************************
template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(const MutableBinaryTree<Data>& tree){
    this->stk = tree.stk;
    this->current = tree.current; 
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>& other) {
    this->stk = other.stk;
    this->current = other.current; 
  }

  // Move constructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&& other) noexcept {
    this->stk = std::move(other.stk);
    std::swap(this->current, other.current);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  BTInOrderMutableIterator<Data>::~BTInOrderMutableIterator() {}

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator<Data>& other){
    if (this != &other) {
      this->stk = other.stk;
      this->current = other.current;
    }
    return *this;
  }

  // Move assignment
  template <typename Data>
  BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator<Data>&& other) noexcept{
    if (this != &other) {
      MutableIterator<Data>::operator=(std::move(other));
      BTInOrderIterator<Data>::operator=(std::move(other));
      this->stk = std::move(other.stk);
      this->current = std::move(other.current);
    }
    return *this;
  }

  /* ************************************************************************ */

  // Specific comparison operators
  template <typename Data>
  bool BTInOrderMutableIterator<Data>::operator==(const BTInOrderMutableIterator<Data>& other) const noexcept {
    return this->current == other.current && MutableIterator<Data>::operator==(other) && BTInOrderIterator<Data>::operator==(other);
  }

template <typename Data>
  bool BTInOrderMutableIterator<Data>::operator!=(const BTInOrderMutableIterator<Data>& other) const noexcept {
    return this->current != other.current || MutableIterator<Data>::operator!=(other) || BTInOrderIterator<Data>::operator!=(other);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
template <typename Data>
  Data& BTInOrderMutableIterator<Data>::operator*() const {
    if (this->Terminated()) {
      throw std::out_of_range("Iterator has terminated");
    }
    return this->current->value;
  }

//**************************** BTBreadthIterator ******************************
//*****************************************************************************

// Specific constructors
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> &bt) {
    current = &bt.Root();
    que.Push(current);
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data> &ab) {
    current = ab.current;
    que = ab.que;
}

// Move constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data> &&ab) noexcept {
    std::swap(current,ab.current);
    que = std::move(ab.que);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BTBreadthIterator<Data>::~BTBreadthIterator() {
    que.Clear();
    delete current;
    current = nullptr;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data> &ab) {
    BTBreadthIterator<Data> *tmp = new BTBreadthIterator<Data>(ab);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> &&ab) noexcept {
    std::swap(current, ab.current);
    que = std::move(ab.que);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data> &ab) const noexcept {
    if(current!=ab.current || que!=ab.que)
        return false;
    return true;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data> &ab) const noexcept {
    return !(*this==ab);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Terminated");

    return current->Element();
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ************************************************************************ */

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    
    if(Terminated())
        throw std::out_of_range("Iterator Ampiezza terminated.");
    
    if(current->HasLeftChild())
        que.Enqueue(&(current->LeftChild()));
    
    if(current->HasRightChild())
        que.Enqueue(&(current->RightChild()));
    
    if(que.Empty())
        current = nullptr;
    else
        current = que.HeadNDequeue();

    return (*this);

}

template <typename Data>
void BTBreadthIterator<Data>::Reset() const noexcept {
    while (!que.Empty()) {
        que.Dequeue();
    }
    if (current) {
        que.Enqueue(current);
    }
}

//************************* MutableBTBreadthIterator ***************************
//******************************************************************************
template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const MutableBinaryTree<Data>& tree){
    this->current = &tree.Root();
    this->que.Push(this->current);
  }

template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>& other) {
    this->current = other.current;
    this->que = other.que;
  }

template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&& other) noexcept{
    std::swap(this->current, other.current);
    this->que = std::move(other.que); 
  }

template <typename Data>
  BTBreadthMutableIterator<Data>::~BTBreadthMutableIterator() {}

template <typename Data>
  BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator<Data>& other) {
    if (this != &other) {
      this->current = other.current;
      this->que = other.que;
    }
    return *this;
  }

template <typename Data>
  BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator<Data>&& other) noexcept {
    if (this != &other) {
      this->current = std::move(other.current);
      this->que = std::move(other.que);
    }
    return *this;
  }

template <typename Data>
  bool BTBreadthMutableIterator<Data>::operator==(const BTBreadthMutableIterator<Data>& other) const noexcept {
    return this->current == other.current && MutableIterator<Data>::operator==(other) && BTBreadthIterator<Data>::operator==(other);
  }

template <typename Data>
  bool BTBreadthMutableIterator<Data>::operator!=(const BTBreadthMutableIterator<Data>& other) const noexcept {
    return this->current != other.current || MutableIterator<Data>::operator!=(other) || BTBreadthIterator<Data>::operator!=(other);
  }

template <typename Data>
  Data& BTBreadthMutableIterator<Data>::operator*() const  {
    if (this->Terminated()) {
      throw std::out_of_range("Iterator has terminated");
    }
    return this->current->Element();
  }



/* ************************************************************************** */
/* ************************************************************************** */
}
