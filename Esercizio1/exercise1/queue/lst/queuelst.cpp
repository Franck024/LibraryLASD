
namespace lasd {

/* ************************************************************************** */

template <typename Data>
QueueLst<Data>::QueueLst(const MappableContainer<Data>& mp){  // fare
    size = mp.Size();
}

template <typename Data>
QueueLst<Data>::QueueLst(const MutableMappableContainer<Data>& mp){  //fare
    size = mp.Size();
}

// Costruttore di copia
QueueLst<Data>::QueueList(const QueueList& other) : head{nullptr}, tail{nullptr} {
    for (Node* p = other.head; p != nullptr; p = p->next) {
        enqueue(p->data);
    }
}

// Costruttore di spostamento
QueueLst<Data>::QueueList(QueueList&& other) : head{other.head}, tail{other.tail} {
    other.head = nullptr;
    other.tail = nullptr;
}

// Distruttore
QueueLst<Data>::~QueueList() {
    while (!head == nullptr) {
        dequeue();
    }
}

template <typename Data>
bool QueueLst<Data>::operator==(const QueueList<Data>& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    ListNode this_node = Head();
    ListNode other_node = other.Head();
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
bool QueueLst<Data>::operator!=(const QueueList<Data>& other) const noexcept {
    return !(*this == other);
}

void QueueLst<Data>::Dequeue() override {
    if (head == nullptr) {
        throw std::runtime_error("La coda è vuota");
    }
    ListNode* oldHead = head;
    head = head->next;
    delete oldHead;
    if (head == nullptr) {
        tail = nullptr;
    }
}

//copy
const void QueueLst<Data>::Enqueue(const Data& item) const override{
    ListNode* newNode = new ListNode{item};
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
    }
    tail = newNode;
    size++;
}

//move
const void QueueLst<Data>::Enqueue( Data&& item) const override{
    ListNode* newNode = new ListNode{item};
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
    }
    tail = newNode;
    size++;
}

template <typename Data>
Data& QueueLst<Data>::Head() override{
    if (head == nullptr) {
        throw std::runtime_error("Coda vuota");
    }
    return head->data;
}

template <typename Data>
const Data& QueueLst<Data>::Head() const override{
    if (head == nullptr) {
        throw std::runtime_error("Coda vuota");
    }
    return head->data;
}


template <typename Data>
Data& QueueLst<Data>::HeadNDequeue(ulong n) const override{
    // Crea una nuova coda vuota per contenere gli elementi estratti
    QueueList<Data> extracted_items;
    
    // Esegue l'estrazione degli elementi dalla coda corrente               //la funz crea una nuova coda e inserisce i primi n elementi 
    for (ulong i = 0; i < n && !empty(); ++i) {                             // della vecchia coda
        extracted_items.Enqueue(Dequeue());
    }
    
    // Restituisce la coda contenente gli elementi estratti
    return extracted_items;
}
/* ************************************************************************** */

}
