
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

  virtual bool Insert(const Data&); // Copy of the value
  virtual bool Insert(Data&&); // Move of the value
  virtual bool Remove(Data&);

  virtual bool InsertAll(const MappableContainer<Data>&) noexcept; // Copy of the value; From MappableContainer; True if all are inserted
  virtual bool InsertAll(MutableMappableContainer<Data>&&) noexcept; // Move of the value; From MutableMappableContainer; True if all are inserted
  virtual bool RemoveAll(const MappableContainer<Data>&); // From MappableContainer; True if all are removed

  virtual bool InsertSome(const MappableContainer<Data>&, const Data&) noexcept; // Copy of the value; From MappableContainer; True if some are inserted
  virtual bool InsertSome(MutableMappableContainer<Data>&&, const Data&) noexcept; // Move of the value; From MutableMappableContainer; True if some are inserted
  virtual bool RemoveSome(const MappableContainer<Data>&, const Data&); // From MappableContainer; True if some is removed

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
