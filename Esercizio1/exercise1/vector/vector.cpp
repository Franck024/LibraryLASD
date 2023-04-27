namespace lasd {

/* ************************************************************************** */

template<typename Data>
Vector<Data>::Vector(const ulong new_size){
    Elements = new Data[new_size]{};
    size = 0;
    capacity = new_size;
}

template<typename Data>
Vector<Data>::Vector(const MappableContainer<Data>& mp){
    size = 0;
    capacity = Size();
    Elements = new Data[size];
    mp.Map([&](const Data& element){
        Elements[size++] = element;
    });
}

template<typename Data>
Vector<Data>::Vector(const MutableMappableContainer<Data>& mp){
    size = 0;
    capacity = Size();
    Elements = new Data[size];
    mp.Map([&](const Data& element){
        Elements[size++] = element;
    });
}

//copy
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& other){
    size = other.size; 
    capacity = other.capacity;
    Elements = new Data[other.size];
    for (std::size_t i = 0; i < size; ++i) {
    Elements[i] = other.Elements[i];
    }
}

//move
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
	std::swap(Elements, vec.Elements);
	std::swap(size, vec.size);
    std::swap(capacity, vec.capacity);
}

template<typename Data>
Vector<Data>::~Vector(){
    delete[] Elements;
}

//Operator ==
template<typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept {
	if (size == vec.size) {
		for (ulong i = 0; i < size; ++i) {
			if (Elements[i] != vec.Elements[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
	
}

// copy assignemnt
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& other){
    if(this != &other){
        delete[] Elements;
        const ulong new_size = other.size;
        Elements = new Data[new_size];
        size = other.size;
        capacity = new_size;
        std::copy(other.Elements, other.Elements + other.size, Elements);
    }
    return *this;
}

//move assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& other) noexcept{
    if(this != &other){
        delete[] Elements;
        Elements = other.Elements;
        size = other.size;
        capacity = other.capacity;
        other.Elements = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

//Operator !=
template<typename Data>
bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept {
	return !(*this == vec);
}

template<typename Data>
void Vector<Data>::Clear(){
    delete[] Elements;
    Elements = nullptr;
    size = 0;
    capacity = 0;
}

template<typename Data>
void Vector<Data>::Resize(const ulong new_size){
    if(new_size < 1)
        Clear();
    if(new_size > 0 && new_size != capacity){
        Data* tmpEl = new Data[new_size]{};
        ulong min = (capacity < new_size) ? capacity : new_size;
        
        for(ulong i = 0; i < min; i++){
            tmpEl[i] = Elements[i];
        }
        delete[] Elements;
        Elements = tmpEl;
        capacity = new_size;
    }
}

// [] non mutabile
template <typename Data>
Data& Vector<Data>::operator[](const ulong index) const    {
    // Controlla se l'indice è valido
    if (index >= capacity) {
        throw std::out_of_range("Index out of range");
    }
    // Restituisci la referenza all'elemento di indice specificato
    return Elements[index];
}

// [] mutabile
template <typename Data>
Data& Vector<Data>::operator[](ulong index) {
    // Controlla se l'indice è valido
    if (index >= capacity) {
        throw std::out_of_range("Index out of range");
    }
    // Restituisci la referenza mutabile all'elemento di indice specificato
    return Elements[index];
}

//Front non mutabile
template <typename Data>
Data& Vector<Data>::Front() const    {
    if (size == 0) {
        throw std::length_error("Vettore vuoto");
    }
    return Elements[0];
}

//Front mutabile
template <typename Data>
Data& Vector<Data>::Front()    {
    if (size == 0) {
        throw std::length_error("Vettore vuoto");
    }
    return Elements[0];
}

//Back non mutabile
template <typename Data>
Data& Vector<Data>::Back() const    {
    if (size == 0) {
        throw std::length_error("Vettore vuoto");
    }
    return Elements[size-1];
}

//Back mutabile
template <typename Data>
Data& Vector<Data>::Back()    {
    if (size == 0) {
        throw std::length_error("Vettore vuoto");
    }
    return Elements[size-1];
}

template <typename Data>
void Vector<Data>::Sort()   {
    for (ulong i = 0; i < size - 1; i++) {
        for (ulong j = 0; j < size - i - 1; j++) {
            if (Elements[j] > Elements[j + 1]) {
                std::swap(Elements[j], Elements[j + 1]);
            }
        }
    }
}
/* ************************************************************************** */

}
