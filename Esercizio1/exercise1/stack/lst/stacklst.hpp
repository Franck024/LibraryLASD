
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>,
                 virtual public List<Data>{
                  // Must extend Stack<Data>,
                  //             List<Data>

private:

  // ...

protected:

  using List<Data>::size;

  struct Node {

    Data valore_nodo;
    Node* next;


    /* ********************************************************************** */

    // Specific constructors
    Node(const Data&);

    /* ********************************************************************** */

    // Copy constructor
    Node& operator=(const Node&);

    // Move constructor
    Node& operator=(Node&&);

    /* ********************************************************************** */

    // Destructor
    ~Node(){delete next;};

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
		bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions
    // ...

  };
  Node* top;

public:

  // Default constructor
  StackLst(){}

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const MappableContainer<Data>&) ; // A stack obtained from a MappableContainer
  StackLst(const MutableMappableContainer<Data>&) ; // A stack obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst&);

  // Move constructor
  StackLst(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~StackLst() ;

  /* ************************************************************************ */

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst&);

  // Move assignment
  StackLst& operator=(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst<Data>&) const noexcept;
	bool operator!=(const StackLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data& TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) const override; // Override Stack member (copy of the value)
  void Push(Data&&) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
