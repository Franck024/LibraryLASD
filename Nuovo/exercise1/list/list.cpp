
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
List<Data>::Node::operator==(const Node& nodo) const noexcept{
    return (valore == nodo.valore);
}

template <typename Data>
List<Data>::Node::operator!=(const Node& nodo) const noexcept{
    return !(valore == nodo.valore);
}

/* ************************************************************************** */
/* ************************************************************************** */
//                LIST

//Costruttori
template <typename Data>
List<Data>::List(const MappableContainer<Data>& map){
    size = 0;
    
    auto mapFunctor = [this](const Data& elem){
        this->InsertAtBack(elem);
    };
    map.Map(mapFunctor);

}

template <typename Data>
List<Data>::List(const MutableMappableContainer<Data>& map){
    size = 0;
    
    auto mapFunctor = [this](const Data& elem){
        this->InsertAtBack(elem);
    };
    map.Map(mapFunctor);

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
List<Data>::List& operator=(const List&) ;

// Move assignment
template <typename Data>
List<Data>::List& operator=(List&&) noexcept;

/* ************************************************************************ */

// Comparison operators
template <typename Data>
List<Data>::bool operator==(const List&) const noexcept;

template <typename Data>
List<Data>::bool operator!=(const List&) const noexcept;

/* ************************************************************************** */

}
