
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

//*********************** MutableBinaryTree *************************
//*******************************************************************


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
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& ab){
    std::swap(current, ab.current);
    stk = std::move(ab.stk);
}

//distruttore
template <typename Data>
BTPreOrderIterator<Data>::~BTPreOrderIterator(){
        stk.Clear();
    current = nullptr;;
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
    return (current==nullptr);
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    // If the stack is empty, there are no more nodes to visit
    if (stk.Empty()) {
        current = nullptr;
        return *this;
    }
    
    // Pop the next node to visit from the stack
    current = stk.Pop();
    
    // Push its right child and then its left child, if they exist
    if (current->HasRightChild()) {
        stk.Push(&current->RightChild());
    }
    if (current->HasLeftChild()) {
        stk.Push(&current->LeftChild());
    }
    
    return *this;
}

template<typename Data>
void BTPreOrderIterator<Data>::Reset() const noexcept {
    stk.Clear();
    if (Root() != nullptr) {
        stk.Push(Root());
        current = Root();
    }
    else {
        current = nullptr;
    }
}


//******************************BTPreOrderMutableIterator******************************
//*************************************************************************************



//************************** BTPostOrderIterator ****************************
//***************************************************************************

// Specific constructors
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) : current(nullptr), last(nullptr) {
    // Push the root of the tree onto the stack
    if (!bt.IsEmpty()) {
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
            getMostLeftLeaf();
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
    current = bt.Root();
    last = nullptr;
}

//************************** BTPostOrderMutableIterator ************************
//******************************************************************************


//************************** BTInOrderIterator ********************************
//*****************************************************************************

// Specific constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &bt) : current(nullptr), stk(){
    Data root = bt.Root();
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
    std::swap(current, ab.current);
    stk = std::move(ab.stk);
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

    if (current && current->HasRightChild()) {  // go to the right subtree
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
    current = &bt.Root();
    // Aggiungi tutti i nodi del sottoalbero sinistro alla pila
    while (current != nullptr) {
        stk.Push(current);
        current = &current->LeftChild();
    }
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



/* ************************************************************************** */
/* ************************************************************************** */
}
