namespace lasd {

/* ************************************************************************** */


template<typename Data>
Vector<Data>::Vector(const ulong new_size){
    Elements = new Data[new_size]{};
    size = new_size;
    capacity = new_size;
}

template<typename Data>
Vector<Data>::Vector(const MappableContainer<Data>& mp){
    size = mp.Size();
    capacity = mp.Size();
    Elements = new Data[capacity]{};
    ulong index = 0;
    mp.Map([&index, this](const auto& element){
        Elements[index++] = element;
    });

    // size = mp.Size();
    // capacity = mp.Size();
    // Elements = new Data[size];
    // for(ulong i = 0 ; i < size; i++){
    //     Elements[i] = mp[i];
    // }
}

template<typename Data>
Vector<Data>::Vector(MutableMappableContainer<Data>&& mp){
    size = mp.Size();
    capacity = mp.Size();
    Elements = new Data[size];
    ulong index = 0;
    mp.Map([&index, this](Data& item) {
        Elements[index++] = std::move(item);
    });
}

//copy
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& other){
    size = other.size; 
    Elements = new Data[other.size];
    for (ulong i = 0; i < size; ++i) {
    Elements[i] = other.Elements[i];
    }
}

//move
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
	std::swap(Elements, vec.Elements);
	std::swap(size, vec.size);
}

template<typename Data>
Vector<Data>::~Vector(){
//    delete[] Elements;
    Clear();
}

// copy assignemnt
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& other){
	Vector<Data>* tmpvec = new Vector<Data>(other);
	std::swap(*tmpvec, *this);
	delete tmpvec;
	return *this;
}

//move assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& other) noexcept{
	std::swap(Elements, other.Elements);
	std::swap(size, other.size);
	return *this;
}

//Operator ==
template<typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept {
	if (size == vec.size) {
		for (ulong i = 0; i < size; i++) {
			if (Elements[i] != vec.Elements[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
	
}

//Operator !=
template<typename Data>
bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept {
	return !(*this == vec);
}

template<typename Data>
void Vector<Data>::Clear(){
    // delete[] Elements;
    // Elements = nullptr;
    // size = 0;
    // capacity = 0;
    for(ulong i = 0; i < size; i++){
        Elements[i].~Data();
    }
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}

template<typename Data>
void Vector<Data>::Resize(const ulong new_size){
    if(new_size < 1){
       Clear();
       return; 
    }
        
    if(new_size > 0 && new_size != size){
        Data* tmpEl = new Data[new_size];
        ulong min = (size < new_size) ? size : new_size;
        
        for(ulong i = 0; i < min; i++){
            tmpEl[i] = Elements[i];
        }
        delete[] Elements;
        Elements = tmpEl;
        size = new_size;
        capacity = new_size;
    }
}

// [] non mutabile
template <typename Data>
Data& Vector<Data>::operator[](const ulong index) const    {
    // Controlla se l'indice è valido
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
        // Controlla se l'array è stato allocato
    if (Elements == nullptr) {
        throw std::runtime_error("Array not allocated");
    }
    // Restituisci la referenza all'elemento di indice specificato
    return Elements[index];
}

// [] mutabile
template <typename Data>
Data& Vector<Data>::operator[](ulong index) {
    // Controlla se l'indice è valido
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
        // Controlla se l'array è stato allocato
    if (Elements == nullptr) {
        throw std::runtime_error("Array not allocated");
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
    Data temp;
    for (ulong i = 0; i < size; i++){
        ulong jmin = i;
        for(ulong j = i+1; j < size; j++){
            if(Elements[j] < Elements[jmin])
            jmin = j;
        }
        if( i != jmin){
            temp = Elements[jmin];
            Elements[jmin] = Elements[i];
            Elements[i] = temp;
        }
    }
}


/* ************************************************************************** */
/* ************************************************************************** */
/************Funzioni aggiuntive*********************/
template <typename Data>
bool Vector<Data>::Exists(const Data& val) const noexcept{
    for(ulong i = 0; i < size; i++){
        if( Elements[i] == val )
            return true;
    } return false;
}

//Vector MapPreOrder
template<typename Data>
void Vector<Data>::PreOrderMap(MapFunctor function) {
	for (ulong i = 0; i < size; i++) {
		function(Elements[i]);
	}
}

//Vector MapPostOrder
template<typename Data>
void Vector<Data>::PostOrderMap(MapFunctor function) {
	ulong index = size;
	while (index > 0) {
		function(Elements[--index]);
	}
}

/* ************************************************************************** */

//Vector FoldPreOrder
template<typename Data>
void Vector<Data>::PreOrderFold(FoldFunctor function, void* parametro) const {
	for (ulong i = 0; i < size; i++) {
		function(Elements[i], parametro);
	}
}

//Vector FoldPostOrder
template<typename Data>
void Vector<Data>::PostOrderFold(FoldFunctor function, void* parametro) const {
	ulong index = size;
	while (index > 0) {
		function(Elements[--index], parametro);
	}
}

/* ************************************************************************** */
template <typename Data>
void Vector<Data>::Map(const MapFunctor& fun) const{
    for(ulong i = 0; i < size; i++){
        fun(Elements[i]);
    }
}

template <typename Data>
void Vector<Data>::Map(const MutableMapFunctor& fun) const{
    for(ulong i = 0; i < size; i++){
        fun(Elements[i]);
    }
}


//Vector MapPreOrder
template<typename Data>
void Vector<Data>::PreOrderMap(MutableMapFunctor function) {
	for (ulong i = 0; i < size; i++) {
		function(Elements[i]);
	}
}

//Vector MapPostOrder
template<typename Data>
void Vector<Data>::PostOrderMap(MutableMapFunctor function) {
	ulong index = size;
	while (index > 0) {
		function(Elements[--index]);
	}
}

}
