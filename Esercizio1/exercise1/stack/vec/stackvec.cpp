
namespace lasd {

/* ************************************************************************** */

template <typename Data>
StackVec<Data>::StackVec(const MappableContainer<Data>& mp){  // fare
    size = mp.Size();
}

template <typename Data>
StackVec<Data>::StackVec(const MutableMappableContainer<Data>& mp){  //fare
    size = mp.Size();
}

// Copy Constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec& other){
    m_vector = other.m_vector;
}

// Move Constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec&& other) noexcept{
    m_vector = std::move(other.m_vector);
}

template <typename Data>
StackVec<Data>::~StackVec() {
    m_vector.~Vector();
}

// Copy Assignment Operator
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& other) {
    if (this != &other) {
        m_vector = other.m_vector;
    }
    return *this;
}

// Move Assignment Operator
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& other) noexcept {
    m_vector = std::move(other.m_vector);
    return *this;
}

template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& other) const noexcept{
    return m_vector == other.m_vector;
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& other) const noexcept{
    return !(*this == other);
}

template <typename Data>
void StackVec<Data>::Pop()  {
    m_vector.Remove(size - 1 );
}

template <typename Data>
Data& StackVec<Data>::Top() const {
    return   m_vector.Front();
}

template <typename Data>
Data& StackVec<Data>::Top(){
    return   m_vector.Front();
}

template <typename Data>
void StackVec<Data>::Push(const Data& val) const  {
      m_vector.InsertAtBack(val);
}

template <typename Data>
void StackVec<Data>::Push( Data&& val)  {
      m_vector.InsertAtBack(val);
}

template <typename Data>
Data& StackVec<Data>::TopNPop()  {
    return m_vector.FrontNRemove();
}

/* ************************************************************************** */


// Restituisce true se lo stack è vuoto, altrimenti false
template <typename Data>
bool StackVec<Data>::Empty() const
{
    return std::Stack<Data>::Empty();
}

// Restituisce il numero di elementi nello stack
template <typename Data>
size_t StackVec<Data>::Size() const
{
    return std::Stack<Data>::Size();
}

// Rimuove tutti gli elementi dallo stack e dal vector
template <typename Data>
void StackVec<Data>::Clear()
{
    while (!Stack<Data>::Empty())
    {
        Stack<Data>::Pop();
    }
    Vector<Data>::Clear();
}

// Espande la capacità del vector sottostante a una nuova capacità
template <typename Data>
void StackVec<Data>::Expand(ulong new_capacity)
{
    Vector<Data>::reserve(new_capacity);
}

// Riduce la capacità del vector sottostante al numero di elementi presenti
template <typename Data>
void StackVec<Data>::Reduce()
{
    Vector<Data>(Vector<Data>::begin(), Vector<Data>::end()).swap(Vector<Data>());
    Vector<Data>::shrink_to_fit();
}
/* ************************************************************************** */

}
