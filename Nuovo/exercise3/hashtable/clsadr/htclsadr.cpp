
namespace lasd {

/* ************************************************************************** */

  // Specific constructors
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(ulong dim){
    size = dim;
    table = new Vector<List<Data>>(size);
    count = 0;
  } 
  
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const MappableContainer<Data>& map) {
    size = map.Size()*2;
    count = 0;
    table = new Vector<List<Data>>(size);
    ulong i = 0;
    map.Map([&](Data& item) {
        Insert(item);
        i++;
    });
  }  
  
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(ulong dim, const MappableContainer<Data>& map) {
    size = dim;
    count = 0;
    table = new Vector<List<Data>>(size);
    ulong i = 0;
    map.Map([&](Data& item) {
        Insert(item);
        i++;           
    });
  }  
  
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(MutableMappableContainer<Data>&& map) {
    size = map.Size() * 2;
    count = 0;
    table = new Vector<List<Data>>(size);
    ulong i = 0;
    map.Map([&](Data&& item) {
        Insert(std::move(item));
        i++;
    });
  }  
  
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(ulong dim, MutableMappableContainer<Data>&& map) {
    size = dim;
    count = 0;
    table = new Vector<List<Data>>(size);
    ulong i = 0;
    map.Map([&](Data&& item) {
      Insert(std::move(item));
      i++;
    });
  }  

  /* ************************************************************************ */

  // Copy constructor
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& ht) {
    size = ht.size;
    count = ht.count;
    table = new Vector<List<Data>>(size);
    for(ulong i = 0; i < size; i++){
      table[i] = ht.table[i];
    }
  } 

  // Move constructor
  template<typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& ht) noexcept{
    size = ht.size;
    count = ht.count;
    table = new Vector<List<Data>>(size);
    for(ulong i = 0; i < size; i++){
      table[i] = std::move(ht.table[i]);
    }
  } 

  /* ************************************************************************ */

  // Destructor
  template<typename Data>
  HashTableClsAdr<Data>::~HashTableClsAdr() {
    size = 0;
    count = 0;
    delete[] table;
  } 

  /* ************************************************************************ */

  // Copy assignment
  template<typename Data>
  HashTableClsAdr& HashTableClsAdr<Data>::operator=(const HashTableClsAdr&) {
    size = ht.size;
    count = ht.count;
    table = new Vector<List<Data>>(size);
    for(ulong i = 0; i < size; i++){
      table[i] = ht.table[i];
    }
    return *this;
  } 

  // Move assignment
  template<typename Data>
  HashTableClsAdr& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& ht) noexcept{
    size = ht.size;
    count = ht.count;
    table = new Vector<List<Data>>(size);
    for(ulong i = 0; i < size; i++){
      table[i] = std::move(ht.table[i]);
    }
    return *this;
  } 

  /* ************************************************************************ */

  // Comparison operators
  template<typename Data>
  bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& ht) const noexcept{
    if(count != ht.count) return false;
    for(ulong i = 0; i < size; i++){
      if(table[i] != ht.table[i]) return false;
    }
  } 
  
  template<typename Data>
  bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& ht) const noexcept{
    return !(*this == ht);
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  template<typename Data>
  bool HashTableClsAdr<Data>::Insert(const Data& value) {
    if(count >= size) Resize(size*2);
    ulong index = HashKey(value) % size;
    table[index].InsertAtBack(value);
    count++;
    return true;
  }  
  
  template<typename Data>
  bool HashTableClsAdr<Data>::Insert(Data&& value) noexcept {
    if(count >= size) Resize(size*2);
    ulong index = HashKey(value) % size;
    table[index].InsertAtBack(std::move(value));
    count++;
    return true;
  }  
  
  template<typename Data>
  bool HashTableClsAdr<Data>::Remove(const Data& value) {
    ulong index = HashKey(value) % size;
    if(table[index].Exists(value)){
      table[index].Remove(value);
      count--;
      return true;
    }
    return false;
  }  

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  template<typename Data>
  bool HashTableClsAdr<Data>::Exists(const Data& value) const noexcept {
    ulong index = HashKey(value) % size;
    return table[index].Exists(value);
  } 

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)
  template<typename Data>
  void HashTableClsAdr<Data>::Resize(const ulong dim) {
    size = dim;
    table.Resize(size);
  }  

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  template<typename Data>
  void HashTableClsAdr<Data>::Clear() {
    count = 0;
    table.Clear();
  }  

/* ************************************************************************** */

}
