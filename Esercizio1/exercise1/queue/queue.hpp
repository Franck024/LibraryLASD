
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue : virtual public ClearableContainer{
              // Must extend ClearableContainer

private:



protected:

  // ...

public:

  // Destructo
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  Queue& operator=(const Queue&);

  // Move assignment
  Queue& operator=(Queue&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue&) const noexcept;
  bool operator!=(const Queue&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& Head() const = 0; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Head() = 0 ; // (mutable version; concrete function must throw std::length_error when empty)
  virtual void Dequeue() = 0 ; // (concrete function must throw std::length_error when empty)
  virtual Data& HeadNDequeue()  = 0; // (concrete function must throw std::length_error when empty)
  virtual void Enqueue(const Data&)  = 0; // Copy of the value
  virtual void Enqueue(Data&&) = 0; // Move of the value

};

/* ************************************************************************** */

}

#endif
