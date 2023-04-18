
namespace lasd {

/* ************************************************************************** */
template<typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data>& mp){
    size = mp.Size();
    Elements = new Data[size];
    for(ulong i = 0 ; i < size ; i++){
        Elements[i] = mp[i];
    }
}

template<typename Data>
QueueVec<Data>::QueueVec(MutableMappableContainer<Data>& mp){
    size = mp.Size();
    Elements = new Data[size];
    for(ulong i = 0 ; i < size ; i++){
        Elements[i] = mp[i];
    }
}

// Costruttore di copia
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& other) : size(other.Size()) {
    // Alloca un nuovo vettore di dimensione mSize
    mElements = new Data[size];
    
    // Copia gli elementi di other.mElements nel nuovo vettore
    for (ulong i = 0; i < size; i++) {
        Elements[i] = other.Elements[i];
    }
}

// Costruttore di spostamento
template<typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& other) : mSize(other.mSize), mElements(other.mElements) {
    // Imposta gli attributi dell'oggetto other a valori di default
    other.size = 0;
    other.Elements = nullptr;
}

// Distruttore
template <typename Data>
QueueVec<Data>::~QueueVec() {
    delete[] Elements;
}

// Copy assignment operator
template<typename Data>
QueueVec<Data>::QueueVec<Data>& operator=(const QueueVec<Data>& other) {
    if (this != &other) {
        // Dealloca la memoria dell'oggetto corrente
        delete[] Elements;
        
        // Crea una copia profonda degli elementi di other.mElements
        size = other.size;
        Elements = new Data[size];
        for (ulong i = 0; i < size; i++) {
            Elements[i] = other.Elements[i];
        }
    }
    
    return *this;
}

// Move assignment operator
template<typename Data>
QueueVec<Data>::QueueVec<Data>& operator=(QueueVec<Data>&& other) {
    if (this != &other) {
        // Dealloca la memoria dell'oggetto corrente
        delete[] Elements;
        
        // "Ruba" il puntatore mElements dell'oggetto other
        size = other.size;
        Elements = other.Elements;
        
        // Imposta gli attributi dell'oggetto other a valori di default
        other.size = 0;
        other.Elements = nullptr;
    }
    
    return *this;
}

// Operatore di uguaglianza
template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& other) const {
    if (size != other.size) {
        return false;
    }
    
    for (int i = 0; i < size; i++) {
        if (Elements[i] != other.Elements[i]) {
            return false;
        }
    }
    
    return true;
}

// Operatore di disuguaglianza
template<typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& other) const {
    return !(*this == other);
}

inline bool Empty() const noexcept{
    return (size == 0);
}

template <typename Data>
Data& QueueVec<Data>::Head() const override{
    if (Empty()) {
        throw std::length_error("Coda vuota");
    }
    return Vector<Data>::Front();
}

template <typename Data>
Data& QueueVec<Data>::Head() override{
    if (Empty()) {
        throw std::length_error("Coda vuota");
    }
    return Vector<Data>::Front();
}

template <typename Data>
Data& QueueVec<Data>::Dequeue() {
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
    
    return first;
}

template <typename Data>
Data& QueueVec<Data>::HeadNDequeue(ulong n) override{
    if (n > size) {
        throw std::length_error("La coda non ha abbastanza elementi.");
    }
    
    // Ottieni il dato dal primo elemento della coda
    Data& dequeuedData = Elements[0];
    
    // Sposta gli elementi rimanenti di n posizioni a sinistra
    for (int i = 0; i < size - n; i++) {
        Elements[i] = Elements[i + n];
    }
    
    // Decrementa la dimensione della coda e dealloca gli elementi rimanenti
    size -= n;
    Data* newElements = new Data[size];
    for (int i = 0; i < size; i++) {
        newElements[i] = Elements[i];
    }
    delete[] Elements;
    Elements = newElements;
    
    // Restituisci il dato dequeuedData
    return dequeuedData;
}

// ENQUEUE  (move)
template <typename Data>
void QueueVec<Data>::Enqueue(const Data& element) const override{
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
/* ************************************************************************** */

}
