
namespace lasd {

/* ************************************************************************** */
  // Specific constructors
  template<typename Data>
  Vector<Data>::Vector(const ulong n_alloc) {
    size = n_alloc;
    elem = new Data[n_alloc];
  }

  template<typename Data>
  Vector<Data>::Vector(MappableContainer<Data>& map){
    size = map.Size();
    ulong index = 0;
    elem = new Data[size];
    map.Map([&](const Data& item){
      elem[index++] = item;
    });

  }

  template<typename Data>
  Vector<Data>::Vector(MutableMappableContainer<Data>&& map){
    size = map.Size();
    elem = new Data[size];
    ulong index = 0;
    map.Map([&](Data& item){
      elem[index++] = std::move(item);
    });
  }

  /* ************************************************************************ */

  // Copy constructor
  template<typename Data>
  Vector<Data>::Vector(const Vector<Data>& vec){
    size = vec.size;
    elem = new Data[vec.size];
    for(ulong i = 0; i < size; i++){
        elem[i] = vec.elem[i];
    }
  }

  // Move constructor
  template<typename Data>
  Vector<Data>::Vector(Vector<Data>&& vec) noexcept{
    std::swap(elem, vec.elem);
    std::swap(size, vec.size);
  }

  /* ************************************************************************ */

  // Destructor
  template<typename Data>
  Vector<Data>::~Vector(){ Clear(); }

  /* ************************************************************************ */

  // Copy assignment
  template<typename Data>
  Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec){
    Vector<Data>* tmp = new Vector<Data>(vec);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
  }

  // Move assignment
  template<typename Data>
  Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept{
	std::swap(elem, vec.elem);
	std::swap(size, vec.size);
	return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template<typename Data>
  bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept{
    if(size != vec.size) return false;
    for(uint i = 0; i < size; i++){
        if(elem[i] != vec.elem[i]) return false;
    }

    return true;
  }

  template<typename Data>
  bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept{
    return !(*this == vec);
  }

  // Specific member function (inherited from ClearableContainer)
  template<typename Data>
  void Vector<Data>::Clear(){
    delete[] elem;
    elem = nullptr;
    size = 0;
  }

  // Specific member function (inherited from ResizableContainer)
  template<typename Data>
  void Vector<Data>::Resize(const ulong new_size){
    if(new_size == 0) Clear();
    if(new_size > 0 && new_size != size){
        ulong min = (size < new_size) ? size : new_size;
        Data* tmp = new Data[new_size];
        for(ulong i = 0 ; i < min; i++){
            tmp[i] = elem[i];
        }
        delete[] elem;
        elem = tmp;
        size = new_size;
    }
  }


  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
  template<typename Data>
  Data& Vector<Data>::operator[](const ulong index) const{
    if(index >= size || index < 0) throw std::out_of_range("out of range");
    return elem[index];
  } 

  template<typename Data>
  Data& Vector<Data>::operator[](const ulong index){
    if(index >= size || index < 0) throw std::out_of_range("out of range");
    return elem[index];
  } 

  template<typename Data>
  Data& Vector<Data>::Front() const{
    if(size == 0 || elem == nullptr) throw std::length_error("Struttura vuota");
    return elem[0];
  } 

  template<typename Data>
  Data& Vector<Data>::Front() {
    if(size == 0 || elem == nullptr) throw std::length_error("Struttura vuota");
    return elem[0];
  } 
  
  template<typename Data>
  Data& Vector<Data>::Back() const{
    if(size == 0 || elem == nullptr) throw std::length_error("Struttura vuota");
    return elem[size-1];
  } 
  
  template<typename Data>
  Data& Vector<Data>::Back() {
    if(size == 0 || elem == nullptr) throw std::length_error("Struttura vuota");
    return elem[size-1];
  } 


  // Specific member function (inherited from SortableLinearContainer)
  template<typename Data>
  void Vector<Data>::Sort(){
    if(size != 0){
      for (ulong i = 0; i < size - 1; ++i) {
        for (ulong j = 0; j < size - i - 1; ++j) {
          if (elem[j] > elem[j + 1]) {
            std::swap(elem[j], elem[j + 1]);
          }
        }
      }
    }
  }



/* ************************************************************************** */
/* ************************************************************************** */
/************Funzioni aggiuntive*********************/

//Vector Fold
template<typename Data>
void Vector<Data>::Fold(const FoldFunctor function, void* parametro) const {
	for (ulong i = 0; i < size; i++) {
		function(elem[i], parametro);
	}
}

//Vector FoldPreOrder
template<typename Data>
void Vector<Data>::PreOrderFold(const FoldFunctor function, void* parametro) const {
	for (ulong i = 0; i < size; i++) {
		function(elem[i], parametro);
	}
}

//Vector FoldPostOrder
template<typename Data>
void Vector<Data>::PostOrderFold(const FoldFunctor function, void* parametro) const {
	ulong index = size;
	while (index > 0) {
		function(elem[--index], parametro);
	}
}

/* ************************************************************************** */
template <typename Data>
void Vector<Data>::Map( MapFunctor fun)const {
    for(ulong i = 0; i < size; i++){
        fun(elem[i]);
    }
}

//Vector MapPreOrder
template<typename Data>
void Vector<Data>::PreOrderMap(MapFunctor function) const {
	for (ulong i = 0; i < size; i++) {
		function(elem[i]);
	}
}

//Vector MapPostOrder
template<typename Data>
void Vector<Data>::PostOrderMap(MapFunctor function) const{
	ulong index = size;
	while (index > 0) {
		function(elem[--index]);
	}
}

template <typename Data>
void Vector<Data>::Map( MutableMapFunctor fun) {
    for(ulong i = 0; i < size; i++){
        fun(elem[i]);
    }
}


//Vector MapPreOrder
template<typename Data>
void Vector<Data>::PreOrderMap(MutableMapFunctor function) {
	for (ulong i = 0; i < size; i++) {
		function(elem[i]);
	}
}

//Vector MapPostOrder
template<typename Data>
void Vector<Data>::PostOrderMap(MutableMapFunctor function) {
	ulong index = size;
	while (index > 0) {
		function(elem[--index]);
	}
}

/* ************************************************************************** */

}
