
namespace lasd {

/* ************************************************************************** */


/////////////// costruttori ////////////////
template <typename Data>
QueueVec<Data>::QueueVec(){  
    // capacity = CAPACITY;
    // Elements = new Data[capacity]{};
    size = 0;
}

template <typename Data>
QueueVec<Data>::QueueVec(const MappableContainer<Data>& mp) : Vector<Data>(mp){  
    size = mp.Size();
    Vector<Data>::Resize(size*2);
}

template <typename Data>
QueueVec<Data>::QueueVec(const MutableMappableContainer<Data>& mp) : Vector<Data>(mp){  
    size = mp.Size();
}

///////////////  ---------- //////////////
////////////// classici metodi ////////////

// Copy Constructor
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec& other) : Vector<Data>(other){}

// Move Constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec&& other) noexcept : Vector<Data>(other){}

// Copy Assignment Operator
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& other){
    Vector<Data>::operator=(other);
    return *this;
}

// Move Assignment Operator
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& other) noexcept{
    Vector<Data>::operator=(std::move(other));
    return *this;
}

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& other) const noexcept{
    return Vector<Data>::operator==(other);
}

template <typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& other) const noexcept{
    return !(*this == other);
}
//////////////// -------------- ///////////
///////////// metodi queue //////////


template <typename Data>
Data& QueueVec<Data>::Head() const  {
    if (Empty()) {
        throw std::length_error("Coda vuota");
    }
    return Vector<Data>::Front();
}

template <typename Data>
Data& QueueVec<Data>::Head()  {
    if (Empty()) {
        throw std::length_error("Coda vuota");
    }
    return Vector<Data>::Front();
}

template <typename Data>
void QueueVec<Data>::Dequeue() {
    if (Empty()) {
        throw std::length_error("Coda vuota");
    }
    // Salva il primo elemento della coda e sposta gli altri elementi di una posizione a sinistra
    Data first = Elements[0];
    for (ulong i = 0; i < size - 1; i++) {
        Elements[i] = Elements[i+1];
    }
    
    // Decrementa la dimensione della coda e dealloca l'ultimo elemento
    size--;
    Elements = realloc(Elements, sizeof(Data) * size);
}

template <typename Data>
Data& QueueVec<Data>::HeadNDequeue()  {
    if (n > size) {
        throw std::length_error("La coda non ha abbastanza elementi.");
    }
    
    // Ottieni il dato dal primo elemento della coda
    Data& dequeuedData = Head();
    
    Dequeue();
    
    // Restituisci il dato dequeuedData
    return dequeuedData;
}

// ENQUEUE  (move)
template <typename Data>
void QueueVec<Data>::Enqueue(const Data& element) const  {
    // Se la dimensione della coda è uguale alla capacità, raddoppia la capacità
    if (size == capacity) {
        capacity *= 2;
        Elements = realloc(Elements, sizeof(Data) * capacity);
    }
    // Aggiunge l'elemento in fondo alla coda
    Elements[mSize] = element;
    size++;
}

// ENQUEUE (move)
template <typename Data>
void QueueVec<Data>::Enqueue(Data&& element) {
    // Se la dimensione della coda è uguale alla capacità, raddoppia la capacità
    if (size == capacity) {
        capacity *= 2;
        Data* newElements = new Data[size - n];
        for (int i = 0; i < size - n; i++) {
            newElements[i] = Elements[i + n];
        }
        delete[] Elements;
        Elements = newElements;
    }
    // Aggiunge l'elemento in fondo alla coda
    Elements[size] = std::move(element);
    size++;
}

inline ulong QueueVec<Data>::Size() const noexcept {
    return size;
}

// Metodo Clear con deallocazione di memoria
void Clear() {
    delete[] Elements;
    Elements = nullptr;
    size = 0
    capacity = 0;
}

//METODI SPECIALI

// Metodo Expand
template <typename Data>
void QueueVec<Data>::Expand(ulong tmpcapacity) {
    if (tmpcapacity > capacity) {
        Data* newElements = (Data*)realloc(Elements, tmpcapacity * sizeof(Data));
        if (newElements == nullptr) {
            throw std::bad_alloc();
        }
        Elements = newElements;
        capacity = tmpcapacity;
    }
}

// Metodo Reduce
template <typename Data>
void QueueVec<Data>::Reduce() {
    if (capacity > size) {
        Data* newElements = (Data*)realloc(Elements, size * sizeof(Data));
        if (newElements == nullptr && size > 0) {
            throw std::bad_alloc();
        }
        Elements = newElements;
        capacity = size;
    }
}

// Metodo SwapVectors
template <typename Data>
void QueueVec<Data>::SwapVectors(QueueVec<Data>& other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(Elements, other.Elements);
}

inline bool Empty() const noexcept{
    return (size == 0);
}

/* ************************************************************************** */

}
