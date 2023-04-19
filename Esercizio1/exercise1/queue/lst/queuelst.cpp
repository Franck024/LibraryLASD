
namespace lasd {

/* ************************************************************************** */
//                                NODE
//COSTRUTTORE
template <typename Data>
QueueLst<Data>::Node::Node(const Data& val){
    valore_nodo = val;
    next = nullptr;
}

//Copy costructor
template <typename Data>
typename QueueLst<Data>::Node& QueueLst<Data>::Node::operator=(const Node& copy){
    if(this != &copy){
        valore_nodo = copy.valore_nodo;
        next = copy.next; 
    }
    return *this;
}

//Move costructor
template <typename Data>
typename QueueLst<Data>::Node& QueueLst<Data>::Node::operator=(Node&& nodo){
    if(this != &nodo){
        std::swap(valore_nodo, nodo.valore_nodo);
        std::swap(next, nodo.next);
    }
    return *this;
}

//Uguaglianza
template <typename Data>
bool QueueLst<Data>::Node::operator==(const Node &node2) const noexcept{
    return (valore_nodo == node2.valore_nodo);
}

//Disuguaglianza
template <typename Data>
bool QueueLst<Data>::Node::operator!=(const Node &node2) const noexcept{
    return !(valore_nodo == node2.valore_nodo);
}


/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

// Costruttore (MappableContainer)
template <typename Data>
QueueLst<Data>::QueueLst(const MappableContainer<Data>& mappCont){                  
    size = 0;
    mappCont.Map([&](const auto& val){
        InsertAtFront(val);
    });
}

// Costruttore (MutableMappableContainer)
template <typename Data>
QueueLst<Data>::QueueLst(const MutableMappableContainer<Data>& mutMapCont) :  head(nullptr), rear(nullptr){
    size = 0;
    mutMapCont.Map([&](const auto& val){
        InsertAtFront(val);
    });
            
}

// Costruttore di copia
template <typename Data>
QueueLst<Data>::QueueLst(const QueueList& other) : head{nullptr}, rear{nullptr} {
    for (Node* p = other.head; p != nullptr; p = p->next) {
        enqueue(p->valore_nodo);
    }
}

// Costruttore di spostamento
template <typename Data>
QueueLst<Data>::QueueList(QueueList&& other) : head{other.head}, rear{other.rear} {
    other.head = nullptr;
    other.rear = nullptr;
}

// Distruttore
QueueLst<Data>::~QueueList() {
    while (!head == nullptr) {
        dequeue();
    }
}

//Copy assignment
template <typename Data>
QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst<Data> &assList)
{
    QueueLst<Data> *tmplist = new QueueLst<Data>(assList);
    std::swap(*tmplist, *this);
    delete (tmplist);
    return *this;
}

//Move assignment
template <typename Data>
QueueLst<Data> &QueueLst<Data>::operator=(QueueLst<Data> &&assList) noexcept
{
    std::swap(head, assList.head);
    std::swap(rear, assList.tail);
    std::swap(size, assList.size);
    return *this;
}   

//Confronto
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    Node this_node = Head();
    Node other_node = other.Head();
    while (this_node && other_node) {
        if (this_node->data != other_node->data) {
            return false;
        }
        this_node = this_node->next;
        other_node = other_node->next;
    }
    return true;
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data>& other) const noexcept {
    return !(*this == other);
}



////////// Fine funzioni classiche ////////////

template <typename Data>
Data& QueueLst<Data>::Head()  {
    if (head == nullptr) {
        throw std::length_error("Coda vuota");
    }
    return head->valore_nodo;
}

template <typename Data>
Data& QueueLst<Data>::Head() const  {
    if (head == nullptr) {
        throw std::length_error("Coda vuota");
    }
    return head->valore_nodo;
}

template <typename Data>
void QueueLst<Data>::Dequeue()   {
    if (head == nullptr) {
        throw std::length_error("La coda è vuota");
    }
    Node* oldHead = head;
    head = head->next;
    delete oldHead;
    if (head == nullptr) {
        rear = nullptr;
    }
}

template <typename Data>
Data& QueueLst<Data>::HeadNDequeue() const  {
    if (head == nullptr) {
        throw std::length_error("La coda è vuota");
    }
    Node* oldHead = head;
    head = head->next;
    Data val = oldHead->valore_nodo;
    delete oldHead;
    if (head == nullptr) {
        rear = nullptr;
    }
    return val;
}


//copy
template <typename Data>
void QueueLst<Data>::Enqueue(const Data& item) {
    Node* newNode = new Node{item};
    if (head == nullptr) {
        head = rear = newNode;
    } else {
        rear->next = newNode;
    }
    rear = newNode;
    size++;
}



//move
template <typename Data>
void QueueLst<Data>::Enqueue( Data&& item)  {
    Node* newNode = new Node{item};
    if (head == nullptr) {
        head = rear = newNode;
    } else {
        rear->next = newNode;
    }
    rear = newNode;
    size++;
}





/* ************************************************************************** */

}
