
namespace lasd {

/* ************************************************************************** */
/* ************************************************************************** */

// Costruttore (MappableContainer)
template <typename Data>
QueueLst<Data>::QueueLst(const MappableContainer<Data>& mappCont) : List<Data>(mappCont){}

// Costruttore (MutableMappableContainer)
template <typename Data>
QueueLst<Data>::QueueLst(const MutableMappableContainer<Data>& mutMapCont) :  List<Data>(mutMapCont){}

// Costruttore di copia
template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& other) : List<Data>(other){}

// Costruttore di spostamento
template <typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& other) noexcept : List<Data>(std::move(other)) {}

//Copy assignment
template <typename Data>
QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst<Data> &assList)
{
    List<Data>::operator=(assList);
    return *this;
}

//Move assignment
template <typename Data>
QueueLst<Data> &QueueLst<Data>::operator=(QueueLst<Data> &&assList) noexcept
{
    List<Data>::operator=(std::move(assList));
    return *this;
}   

//Confronto
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& other) const noexcept {
    return List<Data>::operator==(other);
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data>& other) const noexcept {
    return !(*this == other);
}



////////// Fine funzioni classiche ////////////

template <typename Data>
Data& QueueLst<Data>::Head()  {
    if (List<Data>::Empty()) {
        throw std::length_error("Coda vuota");
    }
    return List<Data>::Front();
}

template <typename Data>
Data& QueueLst<Data>::Head() const  {
    if (List<Data>::Empty()) {
        throw std::length_error("Coda vuota");
    }
    return List<Data>::Front();
}

template <typename Data>
void QueueLst<Data>::Dequeue()   {
    if (List<Data>::Empty()) {
        throw std::length_error("La coda è vuota");
    }
    List<Data>::RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue(){
    if (List<Data>::Empty()) {
        throw std::length_error("La coda è vuota");
    }
    return List<Data>::FrontNRemove();
}


//copy
template <typename Data>
void QueueLst<Data>::Enqueue(const Data& item) {
    List<Data>::InsertAtBack(item);
}



//move
template <typename Data>
void QueueLst<Data>::Enqueue( Data&& item)  {
    List<Data>::InsertAtBack(item);
}





/* ************************************************************************** */

}
