
namespace lasd {

/* ************************************************************************** */

  // Specific constructors
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim){
    size = dim;
    table = new Vector<Data>(size);
    count = 0;
  }

  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const MappableContainer<Data>& map) {
    size = map.Size()*2;
    count = 0;
    table = new Vector<Data>(size);
    ulong i = 0;
    map.Map([&](Data& item) {
        Insert(item);
        i++;
    });

  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim, const MappableContainer<Data>& map) {
    size = dim;
    count = 0;
    table = new Vector<Data>(size);
    ulong i = 0;
    map.Map([&](Data& item) {
        Insert(item);
        i++;           
        
    });
  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(MutableMappableContainer<Data>&& map) {
    size = map.Size() * 2;
    count = 0;
    table = new Vector<Data>(size);
    ulong i = 0;
    map.Map([&](Data&& item) {
        Insert(std::move(item));
        i++;
    });
 
  } 
  
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(ulong dim, MutableMappableContainer<Data>&& map) {
    size = dim;
    count = 0;
    table = new Vector<Data>(size);
    ulong i = 0;
    map.Map([&](Data&& item) {
      Insert(std::move(item));
      i++; 
    });
  }

  /* ************************************************************************ */

  // Copy constructor
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& ht) {
    size = ht.Size();
    count = 0;
    table = new Vector<Data>(size);
    for(ulong i = 0; i <size; i++){
        table[i] = ht.table[i];
        count++;
    }
  }

  // Move constructor
  template<typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& ht) const noexcept{
    std::swap(size, ht.size);
    table = new Vector<Data>(size);
    table = std::move(ht.table);
    std::swap(count, ht.count);
  }

  /* ************************************************************************ */

  // Destructor
  template<typename Data>
  HashTableOpnAdr<Data>::~HashTableOpnAdr() {
    size = 0;
    table.Clear();
    count = 0;
  }

  /* ************************************************************************ */

  // Copy assignment
  template<typename Data>
  HashTableOpnAdr& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& ht) {
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
  HashTableOpnAdr& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& ht) const noexcept{
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
    if(size != ht.size || count != ht.count) return false;
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
    if(count >= size * 0.75) Resize(size*2);
    ulong index = HashKey(value) % size;

    if(table[index] != nullptr) //gestione collisione con sondaggio lineare
      index = FindEmpty(index);
    
    table[index] = value;
    count++;

    return true;
  } 
  
  template<typename Data>
  bool HashTableOpnAdr<Data>::Insert(Data&& value) noexcept {
    if(count >= size * 0.75) Resize(size*2);
    ulong index = HashKey(value) % size;

    if(table[index] != nullptr) //gestione collisione con sondaggio lineare
      index = FindEmpty(index);
    
    table[index] = std::move(value);
    count++;
    
    return true;
  } 
  
  template<typename Data>
  bool HashTableOpnAdr<Data>::Remove(const Data& value) {
    ulong index = HashKey(value) % size;
    
    if(table[index] != nullptr){
      while(table[index] != value){
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
    return table.Find(value) != nullptr;

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
    size = 0;
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
  Data& HashTableOpnAdr<Data>::Find(ulong key){
    if(table[key] != nullptr)
      return table[key];
    throw std::length_error("Elemento non trovato");
  }
  
  template<typename Data>
  ulong HashTableOpnAdr<Data>::FindEmpty(ulong key) const{
    ulong index = key;
    while(table[index] != nullptr){
      index = (index + 1) % size;
    }
    return index;
  }
  
  template<typename Data>
  void HashTableOpnAdr<Data>::RemoveAux( index key){
    table[key] = nullptr;

    //gestire le collisioni
    key = (key + 1) % size;
    while(table[key] != nullptr){
      Data temp = table[key];
      table[key] = nullptr;
      Insert(temp);
      key = (key + 1) % size;
    }
  }


/* ************************************************************************** */

}
