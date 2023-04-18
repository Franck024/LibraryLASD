#include <iterator>
namespace lasd {

/* ************************************************************************** */
//                                NODE
//COSTRUTTORE
template <typename Data>
List<Data>::Node::Node(const Data& val){
    valore_nodo = val;
    next = nullptr;
}

//Copy costructor
template <typename Data>
typename List<Data>::Node& List<Data>::Node::operator=(const Node& copy){
    if(this != &copy){
        valore_nodo = copy.valore_nodo;
        next = copy.next; 
    }
    return *this;
}

//Move costructor
template <typename Data>
typename List<Data>::Node& List<Data>::Node::operator=(Node&& nodo){
    if(this != &nodo){
        std::swap(valore_nodo, nodo.valore_nodo);
        std::swap(next, nodo.next);
    }
    return *this;
}

//Uguaglianza
template <typename Data>
bool List<Data>::Node::operator==(const Node &node2) const noexcept{
    return (valore_nodo == node2.valore_nodo);
}

//Disuguaglianza
template <typename Data>
bool List<Data>::Node::operator!=(const Node &node2) const noexcept{
    return !(valore_nodo == node2.valore_nodo);
}


/* ************************************************************************** */
/* ************************************************************************** */
//                LIST
// Costruttore di default
template<typename Data>
List<Data>::List() : head(nullptr), tail(nullptr) {size = 0;}

// Costruttore (MappableContainer)
template <typename Data>
List<Data>::List(const MappableContainer<Data>& mappCont){                  
    size = 0;
    mappCont.Map([&](const auto& val){
        InsertAtFront(val);
    });
}

// Costruttore (MutableMappableContainer)
template <typename Data>
List<Data>::List(const MutableMappableContainer<Data>& mutMapCont) :  head(nullptr), tail(nullptr){
    size = 0;
    mutMapCont.Map([&](const auto& val){
        InsertAtFront(val);
    });
            
}

//Copy costructor
template <typename Data>
List<Data>::List(const List<Data> &copyList) : head(nullptr), tail(nullptr){
    Node *tmp = copyList.head;
    while(tmp!=nullptr){
        InsertAtBack(tmp->valore_nodo);
        tmp=tmp->next;
    }
}


//Move costructor
template <typename Data>
List<Data>::List(List<Data> &&moveList) noexcept :  head(moveList.head), tail(moveList.tail){
    size = moveList.size;
    moveList.size = 0;                                  //inizializza i campi (copia) e ripulisce la vecchia lista 
    moveList.head = 0;
    moveList.tail = 0;
}

// Distruttore
template <typename Data>
List<Data>::~List() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

//Copy assignment
template <typename Data>
List<Data> &List<Data>::operator=(const List<Data> &assList)
{
    List<Data> *tmplist = new List<Data>(assList);
    std::swap(*tmplist, *this);
    delete (tmplist);
    return *this;
}

//Move assignment
template <typename Data>
List<Data> &List<Data>::operator=(List<Data> &&assList) noexcept
{
    std::swap(head, assList.head);
    std::swap(tail, assList.tail);
    std::swap(size, assList.size);
    return *this;
}

//CONFRONTO
template <typename Data>
bool List<Data>::operator==(const List<Data>& list2) const noexcept{
    if(size != list2.size){
        return false;
    }
    Node* node1 = head;
    Node* node2 = list2.head;
    while(node1 != nullptr && node2 != nullptr){
        if(node1->valore_nodo != node2->valore_nodo){
            return false;
        }
        node1 = node1->next;
        node2 = node2->next;
    }
    return true;
}

template <typename Data>
bool List<Data>::operator!=(const List<Data>& list2) const noexcept{
    return !(*this == list2);
}

//-------------- >>>> Specifiche funzioni
// INSERIMENTO IN TESTA
template <typename Data>
void List<Data>::InsertAtFront(const Data& val)noexcept{                            // prende la testa del nodo e il valore da aggiungere
    Node* newNode = new Node(val);                                            // crea il nuovo nodo
    newNode->next = head;                                                     // punta il nuovo nodo al nodo esistente
    head = newNode;                                                           // definisce la nuova testa
    size++;
}

//INSERIMENTO IN TESTA (move)
template <typename Data>
void List<Data>::InsertAtFront(Data&& val) noexcept{
    Node* newNode = std::move(val);
    if (head) {
        newNode->next = std::move(head);
        head = std::move(newNode);
    } else {
        head = std::move(newNode);
        tail = head;
    }
    size++;
}

//REMOVE FRONT(eccezione empty)
template <typename Data>
void List<Data>::RemoveFromFront(){
    if(head != nullptr){
        Node* tmp = head;
        head = head->next;
        size--;
        delete tmp;
    }else   throw std::length_error("Lista vuota");
}

//REMOVE FRONT (return Data)
template <typename Data>
Data& List<Data>::FrontNRemove(){
    if(head != nullptr){
        Node* tmp = head;
        Data removedData = tmp->valore_nodo;
        head = head->next;
        size--;
        delete tmp;
        return removedData;
    }else   throw std::length_error("Lista vuota");
}

// INSERIMENTO IN CODA
template <typename Data>
void List<Data>::InsertAtBack(const Data& val)noexcept{
    Node* newNode = new Node(val);
    if(head == nullptr)                                                       // se true la struttura è vuota e il nuovo nodo è unico
        head = newNode;
    else{                                                                     // si scorre fino ad arrivare all ultimo nodo e viene aggiunto il nuovo
        Node* current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;                                               
    }                                                                          
    size++;
    tail = newNode;
} 

//INSERIMENTO IN CODA (move)
template <typename Data>
void List<Data>::InsertAtBack(Data&& val) noexcept{
    Node* newNode = std::move(val);
    if (tail) {
        tail->next = std::move(newNode);
        tail = tail->next;
    } else {
        head = std::move(newNode);
        tail = head;
    }
    size++;
}
//-------------- <<<< Specifiche funzioni


//-------------- >>>> ClearableContainer
//Clear
template <typename Data>
void List<Data>::Clear(){
    if(size > 0){
        while(head != nullptr){
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
}
//-------------- <<<< ClearableContainer


//-------------- >>>> DictionaryContainer

//INSERT (copy)
template <typename Data>
void List<Data>::Insert(ulong index, const Data& val) {          
    if(index < 0 || index > size)
        throw std::out_of_range("Indice fuori range");
    Node* newNode = new Node(val);
    if(index == 0){
        newNode->next = head;
        head = newNode;
        if(tail == nullptr){
           tail = newNode; 
        } else if(index == size){
            tail->next = newNode;
            tail = newNode;
        }else{
            Node* prev = head;
            for (ulong i = 0; i < index - 1; i++) {
                prev = prev->next;
            }
            newNode->next = prev->next;
            prev->next = newNode;
        }
        size++;
    }

}

//INSERT (move)
template <typename Data>
void List<Data>::Insert(ulong index, Data&& val) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Indice fuori range");
    }

    Node* newNode = new Node(std::move(val));
    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* prev = head;
        for (ulong i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        newNode->next = prev->next;
        prev->next = newNode;
    }
    size++; 
}

// Funzione per la rimozione di un nodo dalla lista
template <typename Data>
void List<Data>::Remove(ulong index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Indice fuori range");
    }

    Node* nodeToRemove = nullptr;
    if (index == 0) {
        nodeToRemove = head;
        head = head->next;
    } else {
        Node* prev = head;
        for (ulong i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        nodeToRemove = prev->next;
        prev->next = nodeToRemove->next;
    }
    delete nodeToRemove;
    size--;
}
//-------------- <<<< DictionaryContainer

//-------------- >>>> LinearContainer
//operator (non mutabile)
template <typename Data>
Data &List<Data>::operator[](const ulong index) const {
    if (index >= LinearContainer<Data>::Size()) {
        throw std::out_of_range("Indice fuori dai limiti");
    }
                                                            // Scorrere la lista per trovare l'elemento corrispondente all'indice
    Node* current = head;
    ulong i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }

    return current->valore_nodo;
}

//operator (mutabile)
template <typename Data>
Data &List<Data>::operator[](ulong index)    {
    if (index >= LinearContainer<Data>::Size()) {
        throw std::out_of_range("Indice fuori dai limiti");
    }
        // Scorrere la lista per trovare l'elemento corrispondente all'indice
    Node* current = head;
    ulong i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }

    return current->valore_nodo;
}

// FRONT Per una lista non mutabile (const List<Data>&)
template <typename Data>
Data& List<Data>::Front() const {                     // restituisce una referenza costante al primo
    if (head != nullptr) {                                  // elemento della lista, in modo da accedergli 
        return head->valore_nodo;                                  // senza modificarlo
    } else {
        throw std::length_error("Lista vuota");
    }
}

// FRONT Per una lista mutabile (List<Data>&)
template <typename Data>
Data& List<Data>::Front() {                                 // restituisce una referenza al primo elemento
    if (head != nullptr) {                                  // che può essere utilizzata per modificare
        return head->valore_nodo;                                 // l'elemento
    } else {
        throw std::length_error("Lista vuota");
    }
}

// BACK Per una lista non mutabile (const List<Data>&)
template <typename Data>
Data& List<Data>::Back() const {                      // stesso di Front
    if (tail != nullptr) {
        return tail->valore_nodo;
    } else {
        throw std::length_error("Lista vuota");
    }
}

// BACK Per una lista mutabile (List<Data>&)
template <typename Data>
Data& List<Data>::Back() {                                  // stesso di Front
    if (tail != nullptr) {
        return tail->valore_nodo;
    } else {
        throw std::length_error("Lista vuota");
    }
}

//-------------- <<<< LinearContainer

/* *****************************    Foldable   ************************************ */
template <typename Data>
void List<Data>::Fold(const FoldFunctor& functor, void* accumulator)  const    {     // applicata ad una sequenza di elementi, che combina ogni elemento con il risultato parziale della riduzione fino ad ottenere un unico valore.
    Data* acc = static_cast<Data*>(accumulator);                                    //cast del void
    for (const Node* curr = head; curr != nullptr; curr = curr->next) {       //cicla i nodi
        functor(static_cast<const Data&>(curr->valore_nodo), acc);
    }
}


//Preorderfoldable
template <typename Data>
void List<Data>::PreOrderFold(FoldFunctor func, void* initial_value)  {
    PreOrderFold(func,initial_value, head);

}

template <typename Data>
void List<Data>::PreOrderFold(FoldFunctor func, void* initial_value, Node* node) const {
    if (node == nullptr) {
        return;
    }
    func(node->valore_nodo, initial_value);
    if(node->next != nullptr)
        PreOrderFold(func, initial_value, node->next);

}
//--------------

//Postorderfoldabel             
template <typename Data>
void List<Data>::PostOrderFold(FoldFunctor fun, void* initial_value) {
    PostOrderFold(fun, initial_value, head);
}

template <typename Data>
void List<Data>::PostOrderFold(FoldFunctor fun, void* initial_value, Node* node) const{
    if(node == nullptr)
        return;
    PostOrderFold(fun, initial_value, node->next);
    const Data& value = node->valore_nodo;
    fun(value, initial_value);
}
//-------------

/* *****************************    Mappable   ************************************ */
template <typename Data>
void List<Data>::Map(const MapFunctor& fun) const{
    Node* current = head;                                                                 
    while (current != nullptr) {
        fun(current->valore_nodo);
        current = current->next;                                                                
    }
}


// PREORDER (PreOrderMappableContainer)
template <typename Data>
void List<Data>::PreOrderMap(MapFunctor fun)  {
    PreOrderMap(fun, head);
}

template <typename Data>
void List<Data>::PreOrderMap(MapFunctor fun, Node* node) {
    Node* current = node;                                                                 
    while (current != nullptr) {
        fun(current->valore_nodo);
        current = current->next;                                                                
    }
}
//------------

//POSTORDER (PostOrderMappableContainer)
template <typename Data>
void List<Data>::PostOrderMap(MapFunctor fun) {
    PostOrderMap(fun, head);
}

template <typename Data>
void List<Data>::PostOrderMap(MapFunctor fun, Node* node ) {
    if (node == nullptr) {
        return;
    }
    
    // Visita la coda in post-order
    PostOrderMap(fun, node->next);
    
    // Applica la funzione MapFunctor al valore del nodo
    fun(node->valore_nodo);
}
//----------------
//---MUTABLE

template <typename Data>
void List<Data>::Map(const MutableMapFunctor& fun) const    {
    Node* current = head;                                                                 
    while (current != nullptr) {
        fun(current->valore_nodo);
        current = current->next;                                                                
    }
}

// PREORDER (MutableMapFunctor)
template <typename Data>
void List<Data>::PreOrderMap(MutableMapFunctor fun)  {
    PreOrderMap( fun, head);
}

template <typename Data>
void List<Data>::PreOrderMap(MutableMapFunctor fun, Node* node) {
    if(node == nullptr)
        return ;
    Node* current = node;                                                                 
    while (current != nullptr) {
        fun(current->valore_nodo);
        current = current->next;                                                                
    }
}
//------------

//POSTORDER (MutableMapFunctor)
template <typename Data>
void List<Data>::PostOrderMap(MutableMapFunctor fun) {
    PostOrderMap(fun, head);
}

template <typename Data>
void List<Data>::PostOrderMap(MutableMapFunctor fun, Node* node ) {
    if (node == nullptr) {
        return;
    }
    
    // Visita il sotto-albero sinistro in post-order
    PostOrderMap(fun, node->next);
    
    // Applica la funzione MapFunctor al valore del nodo
    Data& node_value = node->valore_nodo;
    fun(node_value);
}
//----------------


// // Funzione per la stampa dei valori della lista
// void List::print() const {
//     Node* curr = head;
//     while (curr != nullptr) {
//         std::cout << curr->data << " ";
//         curr = curr->next;
//     }
//     std::cout << std::endl;
// }
// }
