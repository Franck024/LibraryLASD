
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

    // di mia iniziativa
      struct ListNode {
        Data data;
        ListNode* next;
        ListNode(const Data& d, ListNode* n = nullptr) : data{d}, next{n} {}
        ListNode(Data&& d, ListNode* n = nullptr) : data{std::move(d)}, next{n} {}
    };
    ListNode* head;
    ListNode* tail;

protected:

  // ...

public:

  // Destructo
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Queue&);

  // Move assignment
  Vector& operator=(Queue&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue&) const noexcept;
  bool operator!=(const Queue&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& Head() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Head() ; // (mutable version; concrete function must throw std::length_error when empty)
  virtual void Dequeue() ; // (concrete function must throw std::length_error when empty)
  virtual Data& HeadNDequeue() ; // (concrete function must throw std::length_error when empty)
  virtual void Enqueue(const Data&) ; // Copy of the value
  virtual void Enqueue(Data&&); // Move of the value

};

/* ************************************************************************** */

}

#endif
