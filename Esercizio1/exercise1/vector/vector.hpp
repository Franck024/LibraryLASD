
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public SortableLinearContainer<Data>,
               virtual public ResizableContainer{
                // Must extend ResizableContainer,
                //             SortableLinearContainer<Data>

private:

  // ...

protected:

  using SortableLinearContainer<Data>::size;

  Data* Elements = nullptr;
  ulong capacity = 0;

public:

  // Default constructor
  Vector() = default ;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const ulong) ; // A vector with a given initial dimension
  Vector(const MappableContainer<Data>&) ; // A vector obtained from a MappableContainer
  Vector(const MutableMappableContainer<Data>&) ; // A vector obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data>&) ;

  // Move constructor
  Vector(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector() ;

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector<Data>&);

  // Move assignment
  Vector& operator=(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data>&) const noexcept;
  bool operator!=(const Vector<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(const ulong ) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](const ulong) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](ulong) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() override; // Override SortableLinearContainer member

protected:

  // Auxiliary functions, if necessary!
  //per non rendere la classe astratta vado ad implementare tutti i metodi virtual
  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(const FoldFunctor&, void*)const override {}; // Override FoldableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from PreOrderFoldableContainer)
  void  PreOrderFold(const FoldFunctor, void*) const override ; // Override PreOrderFoldableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from PostOrderFoldableContainer)
  void  PostOrderFold(const FoldFunctor, void*) const override ; // Override PostOrderFoldableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFunctor;
  void Map(const MapFunctor&) const override ; // Override MappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from PreOrderMappableContainer)
  void PreOrderMap(MapFunctor) override ; // Override PreOrderMappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from PostOrderMappableContainer)
  void PostOrderMap(MapFunctor) override ; // Override PostOrderMappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from MutableMappableContainer)
  using typename MutableMappableContainer<Data>::MutableMapFunctor;
  void Map(const MutableMapFunctor&) const override ; // Override MutableMappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from MutablePreOrderMappableContainer)
  void PreOrderMap( MutableMapFunctor) override ; // Override MutablePreOrderMappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from MutablePostOrderMappableContainer)
  void PostOrderMap(MutableMapFunctor) override ; // Override MutablePostOrderMappableContainer member
  // EXIST
  bool Exists(const Data&) const noexcept override ;


};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
