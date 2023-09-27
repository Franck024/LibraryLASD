
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public ResizableContainer,
                virtual public SortableLinearContainer<Data>{
                // Must extend ResizableContainer,
                //             SortableLinearContainer<Data>

private:



protected:

  using Container::size;

  Data* elem = nullptr;

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const ulong) ; // A vector with a given initial dimension
  Vector(MappableContainer<Data>&) ; // A vector obtained from a MappableContainer
  Vector(MutableMappableContainer<Data>&&) ; // A vector obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data>&) ;

  // Move constructor
  Vector(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~Vector() ;

  /* ************************************************************************ */

  // Copy assignment
  Vector<Data>& operator=(const Vector<Data>&) ;

  // Move assignment
  Vector<Data>& operator=(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data>&) const noexcept;
  bool operator!=(const Vector<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(const ulong) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](const ulong) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const ulong) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() override; // Override SortableLinearContainer member

    //per non rendere la classe astratta vado ad implementare tutti i metodi virtual
  using typename FoldableContainer<Data>::FoldFunctor;
  inline void Fold(const FoldFunctor, void*)const override ; // Override FoldableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from PreOrderFoldableContainer)
  inline void  PreOrderFold(const FoldFunctor, void*) const override ; // Override PreOrderFoldableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from PostOrderFoldableContainer)
  inline void  PostOrderFold(const FoldFunctor, void*) const override; // Override PostOrderFoldableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFunctor;
  inline void Map( MapFunctor)const override ; // Override MappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from PreOrderMappableContainer)
  inline void PreOrderMap( MapFunctor)const override ; // Override PreOrderMappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from PostOrderMappableContainer)
  inline void PostOrderMap( MapFunctor)const override ; // Override PostOrderMappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from MutableMappableContainer)
  using typename MutableMappableContainer<Data>::MutableMapFunctor;
  inline void Map(MutableMapFunctor) override; // Override MutableMappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from MutablePreOrderMappableContainer)
  inline void PreOrderMap( MutableMapFunctor) override ; // Override MutablePreOrderMappableContainer member
  /* ************************************************************************ */
  // Specific member function (inherited from MutablePostOrderMappableContainer)
  inline void PostOrderMap(MutableMapFunctor) override ; // Override MutablePostOrderMappableContainer member

protected:

  // Auxiliary functions, if necessary!


  
};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
