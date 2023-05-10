#include <climits>
#include <iostream>
namespace lasd {

/* ************************************************************************** */


/////////////// costruttori ////////////////

template <typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>() {
    size = 0;
    capacity = 5;
    Elements = new Data[capacity]{};
}

template <typename Data>
QueueVec<Data>::QueueVec(const MappableContainer<Data>& mp){  
    size = mp.Size();
    capacity = mp.Size();
    Elements = new Data[mp.Size()];
    mp.PreOrderMap([this](const Data& value) {
        Push(value);
    });
}

template <typename Data>
QueueVec<Data>::QueueVec(const MutableMappableContainer<Data>& mp) : Vector<Data>(mp){}

///////////////  ---------- //////////////
////////////// classici metodi ////////////

// Copy Constructor
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec& other){
    capacity = other.capacity;
    size = other.size;
    Elements = new Data[capacity];
    for (ulong i = 0; i < size; ++i) {
        Elements[i] = other.Elements[i];
    }
}

// Move Constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec&& other) noexcept{
    capacity = other.capacity;
    size = other.size;
    Elements = other.Elements;
    other.capacity = 0;
    other.size = 0;
    other.Elements = nullptr;
}

// Copy Assignment Operator
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& other){
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
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& other) noexcept{
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
bool QueueVec<Data>::operator==(const QueueVec<Data>& other) const noexcept{
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
bool QueueVec<Data>::operator!=(const QueueVec<Data>& other) const noexcept{
    return !(*this == other);
}
//////////////// -------------- ///////////
///////////// metodi queue //////////


template <typename Data>
Data& QueueVec<Data>::Head() const  {
    if(size == 0) {
        throw std:: length_error(" Lista vuota"); // se la coda è vuota, solleva un'eccezione
    }
    return Elements[0];
}

template <typename Data>
Data& QueueVec<Data>::Head()  {
    if(size == 0) {
        throw std:: length_error(" Lista vuota"); // se la lista è vuota, solleva un'eccezione
    }
    return Elements[0];
}

template <typename Data>
void QueueVec<Data>::Dequeue() {
    if(size == 0) {
        throw std:: length_error(" Lista vuota"); // se la lista è vuota, solleva un'eccezione
    }
    for(int i = 0; i < size - 1; i++){
        Elements[i] = Elements[i+1];
    }
    Elements[size - 1].~Data();
    size--;
    ulong temp = size;
    if(size <= capacity / 4) {
        Reduce(capacity / 2); // dimezza la capacità se la lista è vuota al 25%
    }
    size = temp;
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue()  {
    if(size != 0){
        Data val = Elements[0];
        Dequeue();
        return val; 
    }
    throw std::length_error("Lista vuota!");
}

// ENQUEUE  
template <typename Data>
void QueueVec<Data>::Enqueue(const Data& element){
    ulong temp = size;
    if(size == capacity) {
        Expand(2 * capacity); // raddoppia la capacità se il vettore è pieno
    }
    Elements[temp] = element; // inserisce l'elemento in cima alla coda
    size = ++temp;
}

// ENQUEUE (move)
template <typename Data>
void QueueVec<Data>::Enqueue(Data&& element) {
    ulong temp = size;
    if(size == capacity) {
        Expand(2 * capacity); // raddoppia la capacità se il vettore è pieno
    }
    Elements[temp] = std::move(element); // inserisce l'elemento in cima alla coda
    size = ++temp;
}

template <typename Data>
ulong QueueVec<Data>::Size() const noexcept {
    return size;
}

// Metodo Clear con deallocazione di memoria
template <typename Data>
void QueueVec<Data>::Clear() {
    Vector<Data>::Clear();
}

//METODI SPECIALI

// Espande la capacità del vector sottostante a una nuova capacità
template <typename Data>
void QueueVec<Data>::Expand(const ulong new_capacity){
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
void QueueVec<Data>::Reduce(const ulong new_capacity){
    if( new_capacity < size)
        Resize(size);
    if (new_capacity > capacity) { // verifica se la nuova capacità è maggiore di quella attuale
        throw std::length_error("Nuova capacità maggiore alla capacità attuale");
    }    
    Resize(capacity - new_capacity);
}

// Metodo SwapVectors
template <typename Data>
void QueueVec<Data>::SwapVectors(QueueVec<Data>& other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(Elements, other.Elements);
}

template <typename Data>
bool QueueVec<Data>::Empty() const noexcept{
    return (size == 0);
}

/* ************************************************************************** */

}
