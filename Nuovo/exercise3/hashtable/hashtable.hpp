
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:
  ulong operator()(const Data& key) const noexcept{ // (concrete function should not throw exceptions)
    ulong hash = 0;
    const char* keyBytes = reinterpret_cast<const char*>(&key);
    ulong keySize =  sizeof(Data);

    for (ulong i = 0; i < keySize; ++i) {
      hash = (hash * 31) + static_cast<ulong>(keyBytes[i]);
    }

    return hash ;
  }
};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer,
                  virtual public DictionaryContainer<Data>{
                  // Must extend ResizableContainer,
                  //             DictionaryContainer<Data>

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;

  // ...
  ulong count = 0; //aggiunto da me
public:

  // Destructor
  ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator!=(const HashTable&) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  inline ulong HashKey(const Data& key) const{Hashable<Data> hash; return hash(key);};

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
