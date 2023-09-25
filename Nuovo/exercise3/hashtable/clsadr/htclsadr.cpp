
namespace lasd {

/* ************************************************************************** */

  // Specific constructors
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(ulong dim){
    dimensione = dim;
    table =  Vector<BST<Data>*>(dimensione);
    size = 0;
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
  } 
  
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const MappableContainer<Data>& map) {
    dimensione = map.Size()*2;
    size = 0;
    table =  Vector<BST<Data>*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
    map.Map([&](const Data& item) {
        Insert(item);
    });
  }  
  
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(ulong dim, const MappableContainer<Data>& map) {
    dimensione = dim;
    size = 0;
    table =  Vector<BST<Data>*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
    map.Map([&](const Data& item) {
        Insert(item);
    });
  }  
  
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(MutableMappableContainer<Data>&& map) {
    dimensione = map.Size() * 2;
    size = 0;
    table =  Vector<BST<Data>*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
    map.Map([&](Data&& item) {
        Insert(std::move(item));
    });
  }  
  
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(ulong dim, MutableMappableContainer<Data>&& map) {
    dimensione = dim;
    size = 0;
    table =  Vector<BST<Data>*>(dimensione);
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
  HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& ht) {
    dimensione = ht.dimensione;
    size = 0;
    table =  Vector<BST<Data>*>(dimensione);
    for(ulong i = 0; i < dimensione; i++){
      table[i] = nullptr;
    }
    for(ulong i = 0; i < dimensione; i++){
      if(ht.table[i] != nullptr){
        table[i] = new BST<Data>(*ht.table[i]);
        size += table[i]->Size();
      }
    }
  } 

  // Move constructor
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& ht) noexcept{
    if(this != &ht){
      std::swap(dimensione, ht.dimensione);
      std::swap(size, ht.size);
      std::swap(table, ht.table);
    }
  } 

  /* ************************************************************************ */

  // Destructor
  template<typename Data>
  HashTableClsAdr<Data>::~HashTableClsAdr() {
    Clear();
    dimensione = 0;
  } 

  /* ************************************************************************ */

  // Copy assignment
  template<typename Data>
  HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr& ht) {
    Clear();
    if(dimensione != ht.dimensione) Resize(ht.dimensione);
    for(ulong i = 0; i < dimensione; i++){
      if(ht.table[i] != nullptr){
        table[i] = new BST<Data>(*ht.table[i]);
        size += table[i]->Size();
      }
    }
    return *this;
  } 

  // Move assignment
  template<typename Data>
  HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& ht) noexcept{
    if(this != &ht){
      std::swap(dimensione, ht.dimensione);
      std::swap(size, ht.size);
      std::swap(table, ht.table);
    }
    return *this;
  } 

  /* ************************************************************************ */

  // Comparison operators
  template<typename Data>
  bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& ht) const noexcept{
    if(size != ht.size) return false;
    for(ulong i = 0; i < dimensione; i++){
      if((table[i] != nullptr && ht.table[i] == nullptr) || (table[i] == nullptr && ht.table[i] != nullptr)) return false;
      if(table[i] != nullptr && ht.table[i] != nullptr){
        if(*table[i] != *ht.table[i]) return false;
      }
    }
    return true;
  } 
  
  template<typename Data>
  bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& ht) const noexcept{
    return !(*this == ht);
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  template<typename Data>
  bool HashTableClsAdr<Data>::Insert(const Data& value) {
    if(Exists(value)) return false;
    if(size >= dimensione * 0.75) Resize(dimensione*2);

    ulong index = HashKey(value) % dimensione;

    if(table[index] == nullptr)
      table[index] = new BST<Data>();

    if(table[index]->Insert(value)){
      size++;
      return true;
    }else return false;
  }  
  
  template<typename Data>
  bool HashTableClsAdr<Data>::Insert(Data&& value) noexcept {
    if(Exists(value)) return false;
    if(size >= dimensione * 0.75) Resize(dimensione*2);

    ulong index = HashKey(value) % dimensione;

    if(table[index] == nullptr)
      table[index] = new BST<Data>();

    if(table[index]->Insert(std::move(value))){
      size++;
      return true;
    }else return false;
  }  
  
  template<typename Data>
  bool HashTableClsAdr<Data>::Remove(const Data& value) {
    ulong index = HashKey(value) % dimensione;
    if(table[index] == nullptr) return false;

    if(table[index]->Remove(value)){
      size--;
      if(table[index]->Empty()){
        delete table[index];
        table[index] = nullptr;
      }
      return true;
    }else return false;
  }  

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  template<typename Data>
  bool HashTableClsAdr<Data>::Exists(const Data& value) const noexcept {
    ulong index = HashKey(value) % dimensione;
    if(table[index] == nullptr) return false;
    return table[index]->Exists(value);
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)
  template<typename Data>
  void HashTableClsAdr<Data>::Resize(const ulong dim) {
    Vector<Data*> tmp(size);
    ulong index = 0;
    for(ulong i = 0; i < dimensione; i++){
      if(table[i] != nullptr){
        
        table[i]->Map([&](const Data& item){
          tmp[index] = new Data(item);
          index++;
        });
      }
    }
    Clear();
    table.Resize(dim);
    for(ulong i = dimensione; i < dim; i++){
      table[i] = nullptr;
    }
    dimensione = dim;
    size = 0;
    for(ulong i = 0; i < tmp.Size(); i++){
      Insert(*tmp[i]);
      delete tmp[i];
    }
  }  

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  template<typename Data>
  void HashTableClsAdr<Data>::Clear() {
    for(ulong i = 0; i < dimensione; i++){
      if(table[i] != nullptr){
        table[i]->Clear();
        delete table[i];
        table[i] = nullptr;
      }
    }
    size = 0;
  }  


  // per non rendere la classe astratta
  template<typename Data>
  bool HashTableClsAdr<Data>::InsertAll( const MappableContainer<Data>& map) {
    map.Map([&](const Data& item) {
        Insert(item);
    });
    return true;
  }

  template<typename Data>
  bool HashTableClsAdr<Data>::InsertAll(MutableMappableContainer<Data>&& map) noexcept {
    map.Map([&](Data& item) {
        Insert(std::move(item));
    });
    return true;
  }

  template<typename Data>
  bool HashTableClsAdr<Data>::RemoveAll(const MappableContainer<Data>& map) {
    map.Map([&](const Data& item) {
        Remove(item);
    });
    return true;
  }

  template<typename Data>
  bool HashTableClsAdr<Data>::InsertSome(const MappableContainer<Data>& map, ulong numElem) {
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong insertCount = 0;
    map.Map([&](const Data& item) {
        if(insertCount < numElem){
          Insert(item);
          insertCount++;
        }
    });
    return true;
  }

  template<typename Data>
  bool HashTableClsAdr<Data>::InsertSome(MutableMappableContainer<Data>&& map, ulong numElem) noexcept {
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong insertCount = 0;
    map.Map([&](Data& item) {
        if(insertCount < numElem){
          Insert(std::move(item));
          insertCount++;
        }
    });
    return true;
  }

  template<typename Data>
  bool HashTableClsAdr<Data>::RemoveSome(const MappableContainer<Data>& map, ulong numElem) {
    if(numElem == 0)return true;
    if(numElem > map.Size()) return false;
    ulong removeCount = 0;
    map.Map([&](const Data& item) {
        if(removeCount < numElem){
          Remove(item);
          removeCount++;
        }
    });
    return true;
  }

/* ************************************************************************** */

}
