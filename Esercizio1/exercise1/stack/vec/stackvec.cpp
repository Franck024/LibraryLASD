
#define CAPACITY 3

namespace lasd {

/* ************************************************************************** */


/////////////// costruttori ////////////////
template <typename Data>
StackVec<Data>::StackVec(){  
    // capacity = CAPACITY;
    // Elements = new Data[capacity]{};
    size = 0;
}

template <typename Data>
StackVec<Data>::StackVec(const MappableContainer<Data>& mp) : Vector<Data>(mp){  
    size = mp.Size();
    Vector<Data>::Resize(size*2);
}

template <typename Data>
StackVec<Data>::StackVec(const MutableMappableContainer<Data>& mp) : Vector<Data>(mp){  
    size = mp.Size();
}

///////////////  ---------- //////////////
////////////// classici metodi ////////////

// Copy Constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec& other) : Vector<Data>(other){}

// Move Constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec&& other) noexcept : Vector<Data>(other){}

// Copy Assignment Operator
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& other){
    Vector<Data>::operator=(other);
    return *this;
}

// Move Assignment Operator
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& other) noexcept{
    Vector<Data>::operator=(std::move(other));
    return *this;
}

template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& other) const noexcept{
    return Vector<Data>::operator==(other);
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& other) const noexcept{
    return !(*this == other);
}
//////////////// -------------- ///////////
///////////// metodi stack //////////

template <typename Data>
Data& StackVec<Data>::Top() const {
   return Vector<Data>::Back();
}

template <typename Data>
Data& StackVec<Data>::Top(){
    return Vector<Data>::Back();
}

template <typename Data>
void StackVec<Data>::Pop()  {
    Vector<Data>::Resize(size - 1 );
}

template <typename Data>
void StackVec<Data>::Push(const Data& val) const  {
    Vector<Data>::operator[](size+1) = val;
    size++;
}

template <typename Data>
void StackVec<Data>::Push( Data&& val)  {
    Vector<Data>::operator[](size + 1) = val;
    size++;
}

template <typename Data>
Data& StackVec<Data>::TopNPop()  {
    Data* val = Top();
    Pop();
    return val;
}

/* ************************************************************************** */


// Restituisce true se lo stack è vuoto, altrimenti false
template <typename Data>
bool StackVec<Data>::Empty() {
    return (size == 0);
}

// Restituisce il numero di elementi nello stack
template <typename Data>
size_t StackVec<Data>::Size() const{
    return size;
}

// Rimuove tutti gli elementi dallo stack e dal vector
template <typename Data>
void StackVec<Data>::Clear(){
    Vector<Data>::Clear();
}

// Espande la capacità del vector sottostante a una nuova capacità
template <typename Data>
void StackVec<Data>::Expand(ulong new_capacity){
    Vector<Data>::Resize(new_capacity);
}

// Riduce la capacità del vector sottostante al numero di elementi presenti
template <typename Data>
void StackVec<Data>::Reduce(ulong new_capacity){
    Vector<Data>::Resize(new_capacity);
}
/* ************************************************************************** */

}
