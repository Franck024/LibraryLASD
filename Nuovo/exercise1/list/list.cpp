
namespace lasd {

/* ************************************************************************** */

/* ************************************************************************** */
//                                NODE

// Costruttori
template <typename Data>
List<Data>::Node::Node(const Data& val){
    valore = val;
    next = nullptr;
}

template <typename Data>
List<Data>::Node::Node(Data&& val) noexcept{
    std::swap(valore, val);
    next = nullptr;
}

//copy constr
template <typename Data>
List<Data>::Node::Node(const Node& nodo){
    valore = nodo.valore;
    next = nodo.next;
}

//move cost
template <typename Data>
List<Data>::Node::Node(Node&& nodo) noexcept{
    std::swap(valore, nodo.valore);
    std::swap(next, nodo.next);
}

// operatore == e !=
template <typename Data>
bool List<Data>::Node::operator==(const Node& nodo) const noexcept{
    return (valore == nodo.valore);
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& nodo) const noexcept{
    return !(valore == nodo.valore);
}

/* ************************************************************************** */
/* ************************************************************************** */
//                LIST

//Costruttori
template <typename Data>
List<Data>::List( MappableContainer<Data>& map){
    size = 0;
    map.Map([&](const Data& item){
        InsertAtBack(item);
    });
}

template <typename Data>
List<Data>::List(MutableMappableContainer<Data>&& map) {
    size = 0;

    map.Map([&](Data& item){
        InsertAtBack(std::move(item));
    });

}

// Copy constructor
template <typename Data>
List<Data>::List(const List& lista) {
    Node *tmp = lista.head;
    while(tmp != nullptr){
        InsertAtBack(tmp ->valore);
        tmp = tmp->next;
    }
}

// Move constructor
template <typename Data>
List<Data>::List(List&& lista) noexcept{
    std::swap(head, lista.head);
    std::swap(tail, lista.tail);
    std::swap(size, lista.size);
    
};

/* ************************************************************************ */

// Destructor
template <typename Data>
List<Data>::~List(){
    Clear();
} ;

/* ************************************************************************ */

// Copy assignment
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& lista){
    List<Data> *tmp = new List<Data>(lista);
    std::swap(*tmp, *this);
    delete(tmp);
    return *this;
}

// Move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& lista) noexcept{
    std::swap(head, lista.head);
    std::swap(tail, lista.tail);
    std::swap(size, lista.size);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool List<Data>::operator==(const List<Data>& lista) const noexcept{
    if(size != lista.size) return false;
    Node* node1 = head;
    Node* node2 = lista.head;
    while( node1 != nullptr && node2 != nullptr){
        if( node1->valore != node2->valore) return false;
        node1 = node1->next;
        node2 = node2->next;
    }
    return true;
}

template <typename Data>
bool List<Data>::operator!=(const List<Data>& lista) const noexcept{
    return !(*this == lista);
}


  // Specific member functions
template <typename Data>
void List<Data>::InsertAtFront(const Data& val) noexcept{
    Node* newNode = new Node(val);
    if(head == nullptr){
        head = tail = newNode;
    }else{
        newNode->next = head;
        head = newNode;
    } size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& val) noexcept{
    Node* newNode = new Node(val);
    if(head == nullptr){
        head = std::move(newNode);
        tail = head;
    }else{
        newNode->next = std::move(head);
        head = std::move(newNode);
    }size++;
}

template <typename Data>
void List<Data>::RemoveFromFront(){
    if(head != nullptr){
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }else throw std::length_error("Struttura vuota");
}

template <typename Data>
Data List<Data>::FrontNRemove(){
    if(head != nullptr){
        Node* tmp = head;
        Data remNode = head->valore;
        head = head->next;
        delete tmp;
        size--;
        return remNode;
    }else throw std::length_error("Struttura vuota");    
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& val) noexcept{
    Node* newNode = new Node(val);
    if(head == nullptr)
        head = newNode;
    else{
        tail->next = newNode;
    }
    size++;
    tail = newNode;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& val) noexcept{
    Node* newNode = new Node(std::move(val));
    if(head == nullptr)
        head = newNode;
    else{
        tail->next = newNode;
        }
    size++;
    tail = newNode;    
}

// Specific member function (inherited from ClearableContainer)
template <typename Data>
void List<Data>::Clear(){
    while(head != nullptr){
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    head = tail = nullptr;
    size = 0;
}

// Specific member functions (inherited from DictionaryContainer)
template <typename Data>
bool List<Data>::Insert(const Data& dato){
    Node* tmp = head;
    while(tmp != nullptr){
        if(tmp->valore == dato) return false;
        tmp = tmp->next;
    }
    InsertAtFront(dato);
    return true;
}

template <typename Data>
bool List<Data>::Insert(Data&& dato) noexcept{
    Node* tmp = head;
    while(tmp != nullptr){
        if(tmp->valore == dato) return false;
        tmp = tmp->next;
    }
    InsertAtFront(std::move(dato));
    return true;
}

template <typename Data>
bool List<Data>::Remove(const Data& val){
    if(size == 0) return false;
    Node* tmp = head;
    Node* prec = nullptr;    
    while(tmp != nullptr ){
        if(tmp->valore == val){
            if(prec != nullptr){
               prec->next = tmp->next;  
               if(tmp == tail) tail = prec;
            }
                
            else{
                head = tmp->next;
                if(head == nullptr) tail = nullptr;
            }
            delete tmp;
            size--;
            return true;
        }
    }
    return false;
}

// Specific member functions (inherited from LinearContainer)
template <typename Data>
Data& List<Data>::operator[](const ulong index) const{
    if(index >= size) throw std::length_error("Fuori indice");
    Node* curr = head;
    ulong i = 0;
    while(i < index){
        curr = curr->next;
        i++;
    }
    return curr->valore;
} 
template <typename Data>
Data& List<Data>::operator[](const ulong index){
    if(index >= size) throw std::length_error("Fuori indice");
    Node* curr = head;
    ulong i = 0;    
    while(i < index){
        curr = curr->next;
        i++;
    }
    return curr->valore;    
} 

template <typename Data>
Data& List<Data>::Front() const{
    if(size > 0)return head->valore; 
    throw std::length_error("Fuori indice");
        
}

template <typename Data>
Data& List<Data>::Front() {
    if(size > 0)return head->valore; 
    throw std::length_error("Fuori indice");
        
}

template <typename Data>
Data& List<Data>::Back() const{
    if(size > 0)return tail->valore;  
    throw std::length_error("Fuori indice");
     
}

template <typename Data>
Data& List<Data>::Back() {
    if(size > 0)return tail->valore; 
    throw std::length_error("Fuori indice");
      
}

// Specific member function (inherited from FoldableContainer)
template <typename Data>
void List<Data>::Fold(const FoldFunctor fun, void * acc) const{
    Node* tmp = head;
    while( tmp != nullptr){
        fun(tmp->valore, acc);
        tmp = tmp->next;
    }
}

/* ************************************************************************ */

// Specific member function (inherited from PreOrderFoldableContainer)
template <typename Data>
void List<Data>::PreOrderFold(const FoldFunctor fun, void* acc) const{
    PreOrderFold(fun, acc, head);
}

/* ************************************************************************ */

// Specific member function (inherited from PostOrderFoldableContainer)
template <typename Data>
void List<Data>::PostOrderFold(const FoldFunctor fun, void* acc) const{
    PostOrderFold(fun, acc, head);
}

// Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)
template <typename Data>
void List<Data>::PreOrderFold(const FoldFunctor fun, void* acc, Node* nodo) const{
    Node* tmp = nodo;
    while( tmp != nullptr){
        fun(tmp->valore, acc);
        tmp = tmp->next;
    }    
}

template <typename Data>
void List<Data>::PostOrderFold(const FoldFunctor fun, void* acc, Node* nodo) const{
    if (nodo == nullptr) return;
    PostOrderFold(fun, acc, nodo->next);
    fun(nodo->valore, acc);
}

// Specific member function (inherited from MappableContainer)
template <typename Data>
void List<Data>::Map( MapFunctor mapFun)const{
    Node* tmp = head;
    while(tmp != nullptr){
        mapFun(tmp->valore);
        tmp = tmp->next;
    }
}

/* ************************************************************************ */

// Specific member function (inherited from PreOrderMappableContainer)
template <typename Data>
void List<Data>::PreOrderMap( MapFunctor mapFun)const{
    PreOrderMap(mapFun, head);
}

/* ************************************************************************ */

// Specific member function (inherited from PostOrderMappableContainer)
template <typename Data>
void List<Data>::PostOrderMap( MapFunctor mapFun)const{
    PostOrderMap(mapFun, head);
}

// Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)
template <typename Data>
void List<Data>::PreOrderMap( MapFunctor mapFun, Node* nodo)const{
    Node* tmp = nodo;
    while( tmp != nullptr){
        mapFun(tmp->valore);
        tmp = tmp->next;
    } 

}

template <typename Data>
void List<Data>::PostOrderMap( MapFunctor mapFun, Node* nodo)const{
    if (nodo == nullptr) return;
    PostOrderMap(mapFun, nodo->next);
    mapFun(nodo->valore);
}

// Specific member function (inherited from MutableMappableContainer)
template <typename Data>
void List<Data>::Map(MutableMapFunctor mutFun){
    Node* tmp = head;
    while(tmp != nullptr){
        mutFun(tmp->valore);
        tmp = tmp->next;
    }    
}

/* ************************************************************************ */

// Specific member function (inherited from MutablePreOrderMappableContainer)
template <typename Data>
void List<Data>::PreOrderMap(MutableMapFunctor mutFun){
    PreOrderMap(mutFun, head);
}

/* ************************************************************************ */

// Specific member function (inherited from MutablePostOrderMappableContainer)
template <typename Data>
void List<Data>::PostOrderMap(MutableMapFunctor mutFun){
    PostOrderMap(mutFun, head);
}

// Auxiliary member functions (for MutablePreOrderMappableContainer & MutablePostOrderMappableContainer)
template <typename Data>
void List<Data>::PreOrderMap(MutableMapFunctor mutFun, Node* nodo){
    Node* tmp = nodo;
    while( tmp != nullptr){
        mutFun(tmp->valore);
        tmp = tmp->next;
    } 
}

template <typename Data>
void List<Data>::PostOrderMap(MutableMapFunctor mutFun, Node* nodo){
    if (nodo == nullptr) return;
    PostOrderMap(mutFun, nodo->next);
    mutFun(nodo->valore);
}
/* ************************************************************************** */
  // per non rendere la classe astratta
  template <typename Data>
  bool List<Data>::InsertAll( const MappableContainer<Data>& map){
    map.Map([&](const Data& item) {
        Insert(item);
    });
    return true;
  }

  template <typename Data>
  bool List<Data>::InsertAll(MutableMappableContainer<Data>&& map) noexcept{
    map.Map([&](Data& item) {
        Insert(std::move(item));
    });
    return true;
  }

  template <typename Data>
  bool List<Data>::RemoveAll(const MappableContainer<Data>& map ){
    map.Map([&](const Data& item) {
        Remove(item);
    });
    return true;
  }

  template <typename Data>
  bool List<Data>::InsertSome(const MappableContainer<Data>& map, ulong numElem){
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong insertCount = 0;
    map.Map([&](const Data& item) {
        if(insertCount < numElem){
          Insert(item);
          insertCount++;
        }
    });
    return true;
  }

  template <typename Data>
  bool List<Data>::InsertSome(MutableMappableContainer<Data>&& map, ulong numElem) noexcept{
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong insertCount = 0;
    map.Map([&](Data& item) {
        if(insertCount < numElem){
          Insert(std::move(item));
          insertCount++;
        }
    });
    return true;
  }

  template <typename Data>
  bool List<Data>::RemoveSome(const MappableContainer<Data>& map, ulong numElem){
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong removeCount = 0;
    map.Map([&](const Data& item) {
        if(removeCount < numElem){
          Remove(item);
          removeCount++;
        }
    });
    return true;
  }
}
