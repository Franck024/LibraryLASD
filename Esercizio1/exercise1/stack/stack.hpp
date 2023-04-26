
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack : virtual public ClearableContainer{
              // Must extend ClearableContainer

private:

  // ...

protected:


public:

  // Destructor
  virtual ~Stack() = 0;

  // Copy assignment
  virtual Stack& operator=(const Stack&) = 0;

  // Move assignment
  virtual Stack& operator=(Stack&&) noexcept = 0;

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const Stack&) const noexcept = 0;
  virtual bool operator!=(const Stack&) const noexcept = 0;

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& Top() const = 0; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Top() = 0 ; // (mutable version; concrete function must throw std::length_error when empty)
  virtual void Pop() = 0 ; // (concrete function must throw std::length_error when empty)
  virtual Data& TopNPop()  = 0; // (concrete function must throw std::length_error when empty)
  virtual void Push(const Data&) const = 0; // Copy of the value
  virtual void Push(Data&&) = 0; // Move of the value

};

/* ************************************************************************** */

}

#endif
