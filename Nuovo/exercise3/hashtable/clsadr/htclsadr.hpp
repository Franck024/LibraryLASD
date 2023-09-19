
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../vector.hpp"
#include "../list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data>{
                        // Must extend HashTable<Data>

private:

  Vector<List<Data>> table;

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::count;

  // ...

public:

  // Default constructor
  HashTableClsAdr() = default;

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(ulong) ; // A hash table of a given size
  HashTableClsAdr(const MappableContainer<Data>&) ; // A hash table obtained from a MappableContainer
  HashTableClsAdr(ulong, const MappableContainer<Data>&) ; // A hash table of a given size obtained from a MappableContainer
  HashTableClsAdr(MutableMappableContainer<Data>&&) ; // A hash table obtained from a MutableMappableContainer
  HashTableClsAdr(ulong, MutableMappableContainer<Data>&&) ; // A hash table of a given size obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr&) ;

  // Move constructor
  HashTableClsAdr(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableClsAdr() ;

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr& operator=(const HashTableClsAdr&) ;

  // Move assignment
  HashTableClsAdr& operator=(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr&) const noexcept;
  bool operator!=(const HashTableClsAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override;  // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) noexcept override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(const ulong) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
