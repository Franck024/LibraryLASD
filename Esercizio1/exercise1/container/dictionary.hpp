
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data>{
                            // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer&) = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const DictionaryContainer&) = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data&) = 0; // Copy of the value
  virtual bool Insert(Data&&) = 0; // Move of the value
  virtual bool Remove(const Data&) = 0;

  virtual bool InsertAll(const MappableContainer<Data>&) noexcept = 0; // Copy of the value; From MappableContainer; True if all are inserted
  virtual bool InsertAll(MutableMappableContainer<Data>&&) noexcept = 0; // Move of the value; From MutableMappableContainer; True if all are inserted
  virtual bool RemoveAll(const MappableContainer<Data>&) = 0; // From MappableContainer; True if all are removed

  virtual bool InsertSome(const MappableContainer<Data>&, const Data&) noexcept = 0; // Copy of the value; From MappableContainer; True if some are inserted
  virtual bool InsertSome(MutableMappableContainer<Data>&&, const Data&) noexcept = 0; // Move of the value; From MutableMappableContainer; True if some are inserted
  virtual bool RemoveSome(const MappableContainer<Data>&, const Data&) = 0; // From MappableContainer; True if some is removed

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
