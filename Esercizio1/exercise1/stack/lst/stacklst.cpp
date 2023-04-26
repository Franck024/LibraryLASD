
namespace lasd {

/* ************************************************************************** */

// Costruttore (MappableContainer)              FARE
template <typename Data>
StackLst<Data>::StackLst(const MappableContainer<Data>& mappCont){                  
    size = 0;
    mappCont.Map([&](const auto& val){
        Push(val);
    });
}

// Costruttore (MutableMappableContainer)           FARE
template <typename Data>
StackLst<Data>::StackLst(const MutableMappableContainer<Data>& mutMapCont) :  top(nullptr){
    size = 0;
    mutMapCont.Map([&](const auto& val){
        Push(val);
    });
            
}


// Copy Constructor
template <typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& other) : List<Data>(other){}

// Move Constructor
template <typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& other) noexcept : List<Data>(std::move(other)) {}


//Copy assignment
template <typename Data>
StackLst<Data> &StackLst<Data>::operator=(const StackLst<Data> &assList)
{
    List<Data>::operation=(assList);
    return *this;
}

//Move assignment
template <typename Data>
StackLst<Data> &QueueLst<Data>::operator=(StackLst<Data> &&assList) noexcept
{
    List<Data>::operation=(std::move(assList));
    return *this;
}  

// Comparison
template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& other) const noexcept{
    return List<Data>::operation==(other);
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& other) const noexcept{
    return !(*this == other);
}

////////// fine funz base ////////////

template <typename Data>
Data& StackLst<Data>::Top() const {
    if(List<Data>::Empty())
        return throw std::length_error("Lista vuota");
    return this->Front();
}

template <typename Data>
Data& StackLst<Data>::Top(){
    if(List<Data>::Empty())
        return throw std::length_error("Lista vuota");
    return this->Front();
}




template <typename Data>
void StackLst<Data>::Pop()  {
    if(List<Data>::Empty())
        throw std::length_error("Lista vuota");
    this->RemoveFromFront();

}

template <typename Data>
Data& StackLst<Data>::TopNPop()  {
    if(List<Data>::Empty())
        return throw std::length_error("Lista vuota");
    return this->FrontNRemove();
}

template <typename Data>
void StackLst<Data>::Push(const Data& val) const  {
    List<Data>::InsertAtFront(val);
}

template <typename Data>
void StackLst<Data>::Push( Data&& val)  {
    List<Data>::InsertAtFront(val); 
}



/* ************************************************************************** */

}
