
namespace lasd {

/* ************************************************************************** */

  // Specific constructors
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim){
    dimensione = dim;
    table =  Vector<Data*>(dimensione);
    size = 0;
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
  }

  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const MappableContainer<Data>& map) {
    dimensione = map.Size()*2;
    size = 0;
    table =  Vector<Data*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
    map.Map([&](const Data& item) {
        Insert(item);
    });

  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim, const MappableContainer<Data>& map) {
    dimensione = dim;
    size = 0;
    table =  Vector<Data*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
    map.Map([&](const Data& item) {
        Insert(item);
    });
  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(MutableMappableContainer<Data>&& map) {
    dimensione = map.Size() * 2;
    size = 0;
    table =  Vector<Data*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
    map.Map([&](Data&& item) {
        Insert(std::move(item));
    });
 
  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim, MutableMappableContainer<Data>&& map) {
    dimensione = dim;
    size = 0;
    table =  Vector<Data*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
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
    dimensione = ht.dimensione;
    size = 0;
    table =  Vector<Data*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
        table[i] = ht.table[i];
        if(table[i] != nullptr)
          size++;
    }
  }

  // Move constructor
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& ht)  noexcept{
    std::swap(dimensione, ht.dimensione);
    table = std::move(ht.table);
    std::swap(size, ht.size);
  }

  /* ************************************************************************ */

  // Destructor
  template<typename Data>
  HashTableOpnAdr<Data>::~HashTableOpnAdr() {
    Clear();
    dimensione = 0;
  }

  /* ************************************************************************ */

  // Copy assignment
  template<typename Data>
  HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& ht) {
    Clear();
    if(dimensione != ht.dimensione)
      Resize(ht.dimensione);
    for(ulong i = 0; i < ht.dimensione; i++){
      if(ht.table[i] != nullptr){
        table[i] = new Data(*(ht.table[i]));
        size++;
      }
    }
    return *this;
  }

  // Move assignment
  template<typename Data>
  HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& ht) noexcept{
    if(this != &ht){
        std::swap(dimensione, ht.dimensione);
        std::swap(table, ht.table);
        std::swap(size, ht.size);

    }
    return *this;
  }

  /* ************************************************************************ */

  // Comparison HashKeys
  template<typename Data>
  bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& ht) const noexcept{
    if(size != ht.size) return false;
    for(ulong i = 0; i < dimensione; i++){
      if(table[i] != nullptr){
        if(!ht.Exists(*table[i])) return false;
      }
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

    if(size >= dimensione * 0.75){
      ulong tmp = dimensione;
      Resize(dimensione*2);
    } 

    ulong index = HashKey(value) % dimensione;
    
    if(table[index] != nullptr) //gestione collisione con sondaggio lineare
      index = FindEmpty(index);
    
    table[index] = new Data(value);
    size++;
    return true;
  } 
  
  template<typename Data>
  bool HashTableOpnAdr<Data>::Insert(Data&& value) noexcept {
    if(Exists(value)) return false;

    if(size >= dimensione * 0.75){
      ulong tmp = dimensione;
      Resize(dimensione*2);
    } 

    ulong index = HashKey(value) % dimensione;
    
    if(table[index] != nullptr) //gestione collisione con sondaggio lineare
      index = FindEmpty(index);
    
    table[index] = new Data(std::move(value));
    size++;
    
    return true;
  } 
  
  template<typename Data>
  bool HashTableOpnAdr<Data>::Remove(const Data& value) {
    if(!Exists(value)) return false;

    ulong index = HashKey(value) % dimensione;
    
    if(table[index] != nullptr){ //gestione collisione con sondaggio lineare
      while(*table[index] != value){
        index = (index + 1) % dimensione;
      }
      RemoveAux(index);
      size--;
      return true;
    }
    return false;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  template<typename Data>
  bool HashTableOpnAdr<Data>::Exists(const Data& value) const noexcept {
    ulong index = HashKey(value) % dimensione;
    if(table[index] == nullptr) return false;
    while(table[index] != nullptr){
      if(*table[index] == value)
        return true;
      index = (index + 1) % dimensione;
    }
    return false;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)
  template<typename Data>
  void HashTableOpnAdr<Data>::Resize(const ulong dim) {
    table.Resize(dim);
    for(ulong i = dimensione; i < dim; i++){
      table[i] = nullptr;
    }
    dimensione = dim;

    ulong tmp_count = size;
    ulong index = 0;

    Vector<Data*> tmp(size);
    for(ulong i = 0; i < dimensione; i++){
      if(table[i] != nullptr){
        tmp[index] = table[i];
        index++;
        table[i] = nullptr;
      }
    }
    for(ulong i = 0; i < index; i++){
      Insert(*tmp[i]);
    }
    tmp.Clear();
    size = tmp_count;
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  template<typename Data>
  void HashTableOpnAdr<Data>::Clear() {
    for(ulong i = 0; i < dimensione; i++){
      if(table[i] != nullptr){
       // delete table[i];
        table[i] = nullptr;
      }
    }
    size = 0;
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
      index = (index + 1) % dimensione;
    }
    return index;
  }
  
  template<typename Data>
  void HashTableOpnAdr<Data>::RemoveAux( ulong key){
    if(table[key] != nullptr){
      delete table[key];
      table[key] = nullptr;

      //gestire le collisioni
      key = (key + 1) % dimensione;
      
    ulong index = 0;
    Vector<Data*> tmp(size);
    while(table[key] != nullptr){
      tmp[index] = table[key];
      table[key] = nullptr;
      size--;
      index++;
      key = (key + 1) % dimensione;
    }
    for(ulong i = 0; i < index; i++){
      Insert(*tmp[i]);
    }
    tmp.Clear();
      // while(table[key] != nullptr){
      //   Data* temp = table[key];
      //   table[key] = nullptr;
      //   size--;
      //   Insert(*temp);
      //   delete temp;
      //   key = (key + 1) % dimensione;
      // }      
    }
  }

  // per non rendere la classe astratta
  template <typename Data>
  bool HashTableOpnAdr<Data>::InsertAll( const MappableContainer<Data>& map){
    map.Map([&](const Data& item) {
        Insert(item);
    });
    return true;
  }

  template <typename Data>
  bool HashTableOpnAdr<Data>::InsertAll(MutableMappableContainer<Data>&& map) noexcept{
    map.Map([&](Data& item) {
        Insert(std::move(item));
    });
    return true;
  }

  template <typename Data>
  bool HashTableOpnAdr<Data>::RemoveAll(const MappableContainer<Data>& map ){
    map.Map([&](const Data& item) {
        Remove(item);
    });
    return true;
  }

/* ************************************************************************** */

}
