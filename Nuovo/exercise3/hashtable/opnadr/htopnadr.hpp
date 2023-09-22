
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data>{
                        // Must extend HashTable<Data>
private:

  Vector<Data*> table;

protected:

  using HashTable<Data>::size;
using HashTable<Data>::dimensione;
  // ...

public:

  // Default constructor
  HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(ulong) ; // A hash table of a given size
  HashTableOpnAdr(const MappableContainer<Data>&) ; // A hash table obtained from a MappableContainer
  HashTableOpnAdr(ulong, const MappableContainer<Data>&) ; // A hash table of a given size obtained from a MappableContainer
  HashTableOpnAdr(MutableMappableContainer<Data>&&) ; // A hash table obtained from a MutableMappableContainer
  HashTableOpnAdr(ulong, MutableMappableContainer<Data>&&) ; // A hash table of a given size obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&) ;

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr() ;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr<Data>& operator=(const HashTableOpnAdr&) ;

  // Move assignment
  HashTableOpnAdr<Data>& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  bool operator!=(const HashTableOpnAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Copy of the value
  bool Insert(Data&&) noexcept override; // Move of the value
  bool Remove(const Data&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(const ulong) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override; // Override Container member

public:

  // Auxiliary member functions

  ulong HashKey(const Data& ) const;
  const Data& Find(ulong) const;
  ulong FindEmpty(ulong ) const;
  void RemoveAux( ulong );

  
  // per non rendere la classe astratta
    inline bool InsertAll( const MappableContainer<Data>& container) { return false;};
    inline bool InsertAll(MappableContainer<Data>&& container) noexcept { return false;};
    inline bool RemoveAll(const MappableContainer<Data>& container) { return false;};
    inline bool RemoveAll(MappableContainer<Data>&& container) noexcept { return false;};
    inline bool InsertSome(const MappableContainer<Data>& container) { return false;};
    inline bool InsertSome(MappableContainer<Data>&& container) noexcept { return false;};
    inline bool RemoveSome(const MappableContainer<Data>& container) { return false;};

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
