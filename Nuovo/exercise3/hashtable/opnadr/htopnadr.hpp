
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
 #include "../vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data>{
                        // Must extend HashTable<Data>
//---------dovrei impl Hashable
private:

  Vector<Data> table;

protected:

  using HashTable<Data>::size;
using HashTable<Data>::count;
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
  HashTableOpnAdr(HashTableOpnAdr&&) const noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr() ;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&) ;

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) const noexcept;

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

  ulong HashKey(ulong, const Data& ) const;
  Data& Find(ulong );
  ulong FindEmpty(ulong ) const;
  void RemoveAux( index );

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
