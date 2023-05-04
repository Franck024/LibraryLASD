#include <climits>
#include <iostream>
namespace lasd {

/* ************************************************************************** */


/////////////// costruttori ////////////////

template <typename Data>
StackVec<Data>::StackVec() : Vector<Data>() {
    size = 0;
    capacity = 5;
    Elements = new Data[capacity]{};
}

template <typename Data>
StackVec<Data>::StackVec(const MappableContainer<Data>& mp){  
    size = mp.Size();
    capacity = mp.Size();
    Elements = new Data[mp.Size()];
    mp.PreOrderMap([this](const Data& value) {
        Push(value);
    });
}

template <typename Data>
StackVec<Data>::StackVec(const MutableMappableContainer<Data>& mp) : Vector<Data>(mp){}

///////////////  ---------- //////////////
////////////// classici metodi ////////////

// Copy Constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& other){
    capacity = other.capacity;
    size = other.size;
    Elements = new Data[capacity];
    for (ulong i = 0; i < size; ++i) {
        Elements[i] = other.Elements[i];
    }
}

// Move Constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& other) noexcept{
    capacity = other.capacity;
    size = other.size;
    Elements = other.Elements;
    other.capacity = 0;
    other.size = 0;
    other.Elements = nullptr;
}

// Copy Assignment Operator
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& other){
    if (this != &other) {
        capacity = other.capacity;
        size = other.size;
        delete[] Elements;
        Elements = new Data[capacity];
        for (ulong i = 0; i < size; ++i) {
            Elements[i] = other.Elements[i];
        }
    }
    return *this;
}

// Move Assignment Operator
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& other) noexcept{
    if (this != &other) {
        capacity = other.capacity;
        size = other.size;
        delete[] Elements;
        Elements = other.Elements;
        other.capacity = 0;
        other.size = 0;
        other.Elements = nullptr;
    }
    return *this;
}

template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& other) const noexcept{
    if (size != other.size) {
        return false;
    }
    for (ulong i = 0; i < size; ++i) {
        if (Elements[i] != other.Elements[i]) {
            return false;
        }
    }
    return true;
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& other) const noexcept{
    return !(*this == other);
}
//////////////// -------------- ///////////
///////////// metodi stack //////////

template <typename Data>
Data& StackVec<Data>::Top() const {
    if(size == 0) {
        throw std:: length_error(" Stack vuoto"); // se lo stack è vuoto, solleva un'eccezione
    }
    return Elements[size - 1];
}

template <typename Data>
Data& StackVec<Data>::Top(){
    if(size == 0) {
        throw std:: length_error(" Stack vuoto"); // se lo stack è vuoto, solleva un'eccezione
    }
    return Elements[size - 1];
}

template <typename Data>
void StackVec<Data>::Pop()  {
    if(size == 0) {
        throw std:: length_error(" Stack vuoto"); // se lo stack è vuoto, solleva un'eccezione
    }
    Elements[size - 1].~Data();
    size--;
    if(size <= capacity / 4) {
        Reduce(capacity / 2); // dimezza la capacità se lo stack è vuoto al 25%
    }
}

template <typename Data>
void StackVec<Data>::Push(const Data& val) {
    if(size == capacity) {
        Expand(2 * capacity); // raddoppia la capacità se il vettore è pieno
    }
    Elements[size] = val; // inserisce l'elemento in cima allo stack
    size++;
}

template <typename Data>
void StackVec<Data>::Push( Data&& val)  {
    if(size == capacity) {
        Expand(2 * capacity); // raddoppia la capacità se il vettore è pieno
    }
    Elements[size] = val; // inserisce l'elemento in cima allo stack
    size++;
}

template <typename Data>
Data StackVec<Data>::TopNPop()  {
    if(size == 0)
        throw std::length_error("Stack vuoto!");
    Data val = Elements[size-1];
    Pop();
    return val;      
}

/* ************************************************************************** */


// Restituisce true se lo stack è vuoto, altrimenti false
template <typename Data>
bool StackVec<Data>::Empty() const  noexcept {
    return (size == 0);
}

// Restituisce il numero di elementi nello stack
template <typename Data>
ulong StackVec<Data>::Size() const noexcept{
    return size;
}

// Rimuove tutti gli elementi dallo stack e dal vector
template <typename Data>
void StackVec<Data>::Clear(){
    Vector<Data>::Clear();
}

// Espande la capacità del vector sottostante a una nuova capacità
template <typename Data>
void StackVec<Data>::Expand(const ulong new_capacity){
    if (new_capacity < capacity) { // verifica se la nuova capacità è maggiore di quella attuale
        return;
    }
    if(new_capacity > ULONG_MAX - sizeof(Data)) {
        Resize(ULONG_MAX - sizeof(Data));
    }
    else
        Resize(new_capacity);
}

// Riduce la capacità del vector sottostante al numero di elementi presenti
template <typename Data>
void StackVec<Data>::Reduce(const ulong new_capacity){
    if( new_capacity < size)
        Resize(size);
    if (new_capacity > capacity) { // verifica se la nuova capacità è maggiore di quella attuale
        throw std::length_error("Nuova capacità maggiore alla capacità attuale");
    }    
    Resize(capacity - new_capacity);
}
/* ************************************************************************** */

}
