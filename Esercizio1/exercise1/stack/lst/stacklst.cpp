
namespace lasd {


/* ************************************************************************** */
//                                NODE
//COSTRUTTORE
template <typename Data>
StackLst<Data>::Node::Node(const Data& val){
    valore_nodo = val;
    next = nullptr;
}

//Copy costructor
template <typename Data>
typename StackLst<Data>::Node& QueueLst<Data>::Node::operator=(const Node& copy){
    if(this != &copy){
        valore_nodo = copy.valore_nodo;
        next = copy.next; 
    }
    return *this;
}

//Move costructor
template <typename Data>
typename StackLst<Data>::Node& QueueLst<Data>::Node::operator=(Node&& nodo){
    if(this != &nodo){
        std::swap(valore_nodo, nodo.valore_nodo);
        std::swap(next, nodo.next);
    }
    return *this;
}

//Uguaglianza
template <typename Data>
bool StackLst<Data>::Node::operator==(const Node &node2) const noexcept{
    return (valore_nodo == node2.valore_nodo);
}

//Disuguaglianza
template <typename Data>
bool StackLst<Data>::Node::operator!=(const Node &node2) const noexcept{
    return !(valore_nodo == node2.valore_nodo);
}


/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

// Costruttore (MappableContainer)
template <typename Data>
StackLst<Data>::StackLst(const MappableContainer<Data>& mappCont){                  
    size = 0;
    mappCont.Map([&](const auto& val){
        Push(val);
    });
}

// Costruttore (MutableMappableContainer)
template <typename Data>
StackLst<Data>::StackLst(const MutableMappableContainer<Data>& mutMapCont) :  top(nullptr){
    size = 0;
    mutMapCont.Map([&](const auto& val){
        Push(val);
    });
            
}


// Copy Constructor
template <typename Data>
StackLst<Data>::StackLst(const StackLst& other){
    for (Node* p = other.top; p != nullptr; p = p->next) {
        enqueue(p->valore_nodo);
    }
}

// Move Constructor
template <typename Data>
StackLst<Data>::StackLst(StackLst&& other) noexcept{
    top = other.top;
    size = other.size;
    other.top = nullptr;
    other.size = 0;
}

template <typename Data>
StackLst<Data>::~StackLst() {
    while(!top == nullptr){
        Pop();
    }
}

//Copy assignment
template <typename Data>
StackLst<Data> &StackLst<Data>::operator=(const StackLst<Data> &assList)
{
    StackLst<Data> *tmplist = new StackLst<Data>(assList);
    std::swap(*tmplist, *this);
    delete (tmplist);
    return *this;
}

//Move assignment
template <typename Data>
StackLst<Data> &QueueLst<Data>::operator=(StackLst<Data> &&assList) noexcept
{
    std::swap(top, assList.top);
    std::swap(size, assList.size);
}  

template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& other) const noexcept{
    if(size != other.size)
        return false;
    Nodo curr = Top();
    Nodo curr2 = other.Top();
    while(!curr == nullptr){
        if(curr->valore_nodo != curr2->valore_nodo)
            return false;
        curr = curr->next;
        curr2 = curr2->next;
    }
    return true;
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& other) const noexcept{
    return !(*this == other);
}

////////// fine funz base ////////////

template <typename Data>
Data& StackLst<Data>::Top() const {
    if(top == nullptr)
        throw std::length_error("Stack vuoto");
    return top->valore_nodo;
}

template <typename Data>
Data& StackLst<Data>::Top(){
    if(top == nullptr)
        throw std::length_error("Stack vuoto");
    return  top->valore_nodo;
}




template <typename Data>
void StackLst<Data>::Pop()  {
    if(top == nullptr)
        throw std::length_error("Stack vuoto");
    Nodo* curr = top;
    top = top->next;
    delete curr;

}

template <typename Data>
Data& StackLst<Data>::TopNPop()  {
    if(top == nullptr)
        throw std::length_error("Stack vuoto");
    Data val = top->valore_nodo;
    Pop();
    return val;
}

template <typename Data>
void StackLst<Data>::Push(const Data& val) const  {
    Node* curr = new Node{val};
    curr->next = top;
    top = curr;
    size++; 
}

template <typename Data>
void StackLst<Data>::Push( Data&& val)  {
    Node* curr = new Node{val};
    top = curr;
    size++; 
}



/* ************************************************************************** */

}
