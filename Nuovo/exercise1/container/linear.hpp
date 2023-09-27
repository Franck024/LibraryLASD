
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public MutablePreOrderMappableContainer<Data>,
                        virtual public MutablePostOrderMappableContainer<Data>{
                        // Must extend MutablePreOrderMappableContainer<Data>,
                        //             MutablePostOrderMappableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer operator=(const LinearContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer&) const noexcept = delete; // Comparison of abstract types is possible.
  bool operator!=(const LinearContainer&) const noexcept = delete; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator[](const ulong) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  virtual Data& operator[](const ulong) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  virtual Data& Front() const = 0; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Front() = 0; // (mutable version; concrete function must throw std::length_error when empty)

  virtual Data& Back() const = 0; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Back() = 0; // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void Fold(const FoldFunctor, void *) const override = 0; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderFoldableContainer)

  virtual void PreOrderFold(const FoldFunctor, void *) const override = 0; // Override PreOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderFoldableContainer)

  virtual void PostOrderFold(const FoldFunctor, void *) const override = 0; // Override PostOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  virtual void Map( MapFunctor)const override = 0; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap( MapFunctor)const override = 0; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap( MapFunctor)const override = 0; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  virtual void Map( MutableMapFunctor) override = 0; // Override MutableMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)

  virtual void PreOrderMap( MutableMapFunctor) override = 0; // Override MutablePreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)

  virtual void PostOrderMap( MutableMapFunctor) override = 0; // Override MutablePostOrderMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer : virtual public LinearContainer<Data>{
                                // Must extend LinearContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  SortableLinearContainer& operator==(const SortableLinearContainer&) const noexcept = delete; // Comparison of abstract types is possible.
  SortableLinearContainer& operator!=(const SortableLinearContainer&) const noexcept = delete; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Sort() = 0;

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
