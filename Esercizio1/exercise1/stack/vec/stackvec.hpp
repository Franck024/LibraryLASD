
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>,
                 virtual public Vector<Data>{
                  // Must extend Stack<Data>,
                  //             Vector<Data>

private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::capacity;
  using Vector<Data>::Elements;

  using Vector<Data>::Resize;

public:

  // Default constructor
   StackVec() : Vector<Data>() {};

  /* ************************************************************************ */

  // Specific constructor
   StackVec(const MappableContainer<Data>&) ; // A stack obtained from a MappableContainer
   StackVec(const MutableMappableContainer<Data>&) ; // A stack obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec&);

  // Move constructor
  StackVec(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec&);

  // Move assignment
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec<Data>&) const noexcept;
	bool operator!=(const StackVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data& Top()  override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  void Pop()  override; // Override Stack member (must throw std::length_error when empty)
  Data& TopNPop()  override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

   bool Empty() const noexcept override; // Override Container member

   ulong Size() const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

   void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary member functions

   void Expand(const ulong) ;
   void Reduce(const ulong) ;

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
