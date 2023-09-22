
namespace lasd {

/* ************************************************************************** */

  // Specific constructors
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim){
    size = dim;
    table =  Vector<Data*>(size);
    count = 0;
    for(ulong i = 0; i < size; i++){
      table[i] = nullptr;
    }
  }

  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const MappableContainer<Data>& map) {
    size = map.Size()*2;
    count = 0;
    table =  Vector<Data*>(size);
    for(ulong i = 0; i < size; i++){
      table[i] = nullptr;
    }
    map.Map([&](const Data& item) {
        Insert(item);
    });

  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim, const MappableContainer<Data>& map) {
    size = dim;
    count = 0;
    table =  Vector<Data*>(size);
    for(ulong i = 0; i < size; i++){
      table[i] = nullptr;
    }
    map.Map([&](const Data& item) {
        Insert(item);
    });
  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(MutableMappableContainer<Data>&& map) {
    size = map.Size() * 2;
    count = 0;
    table =  Vector<Data*>(size);
    for(ulong i = 0; i < size; i++){
      table[i] = nullptr;
    }
    map.Map([&](Data&& item) {
        Insert(std::move(item));
    });
 
  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim, MutableMappableContainer<Data>&& map) {
    size = dim;
    count = 0;
    table =  Vector<Data*>(size);
    for(ulong i = 0; i < size; i++){
      table[i] = nullptr;
    }
    map.Map([&](Data&& item) {
      Insert(std::move(item));
    });
  }

  /* ************************************************************************ */

  // Copy constructor
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& ht) {
    size = ht.Size();
    count = 0;
    table =  Vector<Data*>(size);
    for(ulong i = 0; i < size; i++){
        table[i] = ht.table[i];
        if(table[i] != nullptr)
          count++;
    }
  }

  // Move constructor
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& ht)  noexcept{
    std::swap(size, ht.size);
    table = std::move(ht.table);
    std::swap(count, ht.count);
  }

  /* ************************************************************************ */

  // Destructor
  template<typename Data>
  HashTableOpnAdr<Data>::~HashTableOpnAdr() {
    size = 0;
    count = 0;
    table.~Vector();
  }

  /* ************************************************************************ */

  // Copy assignment
  template<typename Data>
  HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& ht) {
    if(this != &ht){
        size = ht.size;
        table.Resize(size);
        for(ulong i = 0; i < size; i++){
            table[i] = ht.table[i];
            count++;
        }
    }
    return *this;
  }

  // Move assignment
  template<typename Data>
  HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& ht) noexcept{
    if(this != &ht){
        size = ht.size;
        table = std::move(ht.table);
        ht.size = 0;
        count = ht.count;
    }
    return *this;
  }

  /* ************************************************************************ */

  // Comparison HashKeys
  template<typename Data>
  bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& ht) const noexcept{
    if(count != ht.count) return false;
    for(ulong i = 0; i < size; i++){
        if(table[i] != ht.table[i]) return false;
    }
    return true;
  }
  
  template<typename Data>
  bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr& ht) const noexcept{
    return !(*this == ht);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  template<typename Data>
  bool HashTableOpnAdr<Data>::Insert(const Data& value) {
    if(Exists(value)) return false;

    if(count >= size * 0.75){
      ulong tmp = size;
      Resize(size*2);
      for( ulong i = tmp; i < size; i++){
        table[i] = nullptr;
      }
    } 

    ulong index = HashKey(value) % size;
    
    if(table[index] != nullptr) //gestione collisione con sondaggio lineare
      index = FindEmpty(index);
    
    table[index] = new Data(value);
    count++;
    return true;
  } 
  
  template<typename Data>
  bool HashTableOpnAdr<Data>::Insert(Data&& value) noexcept {
    if(Exists(value)) return false;

    if(count >= size * 0.75){
      ulong tmp = size;
      Resize(size*2);
      for( ulong i = tmp; i < size; i++){
        table[i] = nullptr;
      }
    } 

    ulong index = HashKey(value) % size;
    
    if(table[index] != nullptr) //gestione collisione con sondaggio lineare
      index = FindEmpty(index);
    
    table[index] = new Data(std::move(value));
    count++;
    
    return true;
  } 
  
  template<typename Data>
  bool HashTableOpnAdr<Data>::Remove(const Data& value) {
    if(!Exists(value)) return false;

    ulong index = HashKey(value) % size;
    
    if(table[index] != nullptr){ //gestione collisione con sondaggio lineare
      while(*table[index] != value){
        index = (index + 1) % size;
      }
      RemoveAux(index);
      count--;
      return true;
    }
    return false;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  template<typename Data>
  bool HashTableOpnAdr<Data>::Exists(const Data& value) const noexcept {
    ulong index = this->HashKey(value) % size;
    while(table[index] != nullptr){
      if(*table[index] == value)
        return true;
      index = (index + 1) % size;
    }
    return false;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)
  template<typename Data>
  void HashTableOpnAdr<Data>::Resize(const ulong dim) {
    size = dim;
    table.Resize(dim);
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  template<typename Data>
  void HashTableOpnAdr<Data>::Clear() {
    count = 0;
    table.Clear();
  } 


  // Auxiliary member functions
  template<typename Data>
  ulong HashTableOpnAdr<Data>::HashKey(const Data& key) const{
    Hashable<Data> hash;
    return hash(key);
  }
  
  template<typename Data>
  const Data& HashTableOpnAdr<Data>::Find(ulong key) const {
      if(table[key] != nullptr)
        return *table[key];
      throw std::length_error("Elemento non trovato");
  }
  
  template<typename Data>
  ulong HashTableOpnAdr<Data>::FindEmpty(ulong key) const{
    ulong index = key;

    while(table[index] != nullptr){
      index = (index + 1) % size;
    }
    if(index == key)
      throw std::length_error("Non ci sono spazi vuoti");
    return index;
  }
  
  template<typename Data>
  void HashTableOpnAdr<Data>::RemoveAux( ulong key){
    if(table[key] != nullptr){
      delete table[key];
      table[key] = nullptr;

      //gestire le collisioni
      key = (key + 1) % size;
      
      while(table[key] != nullptr){
        Data* temp = table[key];
        table[key] = nullptr;
        count--;
        Insert(*temp);
        delete temp;
        key = (key + 1) % size;
      }      
    }
  }


/* ************************************************************************** */

}
