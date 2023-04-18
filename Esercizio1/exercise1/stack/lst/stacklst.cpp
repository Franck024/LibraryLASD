
namespace lasd {

/* ************************************************************************** */

template <typename Data>
StackLst<Data>::StackLst(const MappableContainer<Data>& mp){  // fare
    size = mp.Size();
}

template <typename Data>
StackLst<Data>::StackLst(const MutableMappableContainer<Data>& mp){  //fare
    size = mp.Size();
}

// Copy Constructor
template <typename Data>
StackLst<Data>::StackLst(const StackLst& other){
    m_list = other.m_list;
}

// Move Constructor
template <typename Data>
StackLst<Data>::StackLst(StackLst&& other) noexcept{
    m_list = std::move(other.m_list);
}

template <typename Data>
StackLst<Data>::~StackLst() {
    m_list.~List();
}

// Copy Assignment Operator
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& other) {
    if (this != &other) {
        m_list = other.m_list;
    }
    return *this;
}

// Move Assignment Operator
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& other) noexcept {
    m_list = std::move(other.m_list);
    return *this;
}

template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& other) const noexcept{
    return m_list == other.m_list;
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& other) const noexcept{
    return !(*this == other);
}

template <typename Data>
void StackLst<Data>::Pop()  {
    m_list.Remove(size - 1 );
}

template <typename Data>
Data& StackLst<Data>::Top() const {
    return   m_list.Front();
}

template <typename Data>
Data& StackLst<Data>::Top(){
    return   m_list.Front();
}

template <typename Data>
void StackLst<Data>::Push(const Data& val) const  {
      m_list.InsertAtBack(val);
}

template <typename Data>
void StackLst<Data>::Push( Data&& val)  {
      m_list.InsertAtBack(val);
}

template <typename Data>
Data& StackLst<Data>::TopNPop()  {
    return m_list.FrontNRemove();
}

/* ************************************************************************** */

}
