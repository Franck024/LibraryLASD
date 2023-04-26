
#define CAPACITY 3

namespace lasd {

/* ************************************************************************** */


/////////////// costruttori ////////////////
template <typename Data>
StackVec<Data>::StackVec(){  
    capacity = CAPACITY;
    Elements = new Data[capacity]{};
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
    m_vector.Remove(size - 1 );
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
