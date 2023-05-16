
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearContainer,
            virtual public DictionaryContainer<Data>,
            virtual public BinaryTree<Data>,
            virtual public BinaryTreeLnk<Data>{
            // Must extend ClearableContainer,
            //             DictionaryContainer<Data>,
            //             BinaryTree<Data>,
            //             BinaryTreeLnk<Data>

private:

  // ...

protected:

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

  // ...

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const MutableContainer<Data>&); // A bst obtained from a MutableContainer
  BST(MappableMutableContainer<Data>&&) noexcept; // A bst obtained from a MappableMutableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data>&) ;

  // Move constructor
  BST(BST<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST<Data>&) ;

  // Move assignment
  BST& operator=(BST<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST<Data>&) const noexcept;
  bool operator!=(const BST<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data& MinNRemove() ; // (concrete function must throw std::length_error when empty)
  void RemoveMin() ; // (concrete function must throw std::length_error when empty)

  Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data& MaxNRemove() ; // (concrete function must throw std::length_error when empty)
  void RemoveMax() ; // (concrete function must throw std::length_error when empty)

  Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data& PredecessorNRemove(const Data&) ; // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) ; // (concrete function must throw std::length_error when not found)

  Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data& SuccessorNRemove(const Data&) ; // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) ; // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) noexcept override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary member functions

  Data DataNDelete(struct BST<Data>::NodeLnk*) ;

  struct BST<Data>::NodeLnk* Detach(struct BST<Data>::NodeLnk*&) noexcept;

  struct BST<Data>::NodeLnk* DetachMin(struct BST<Data>::NodeLnk*&) noexcept;
  struct BST<Data>::NodeLnk* DetachMax(struct BST<Data>::NodeLnk*&) noexcept;

  struct BST<Data>:NodeLnk* Skip2Left(struct BST<Data>::NodeLnk*&) noexcept;
  struct BST<Data>:NodeLnk* Skip2Right(struct BST<Data>::NodeLnk*&) noexcept;

  struct BST<Data>::NodeLnk*& FindPointerToMin(struct BST<Data>::NodeLnk*&) noexcept;
  struct BST<Data>::NodeLnk* const& FindPointerToMin(struct BST<Data>::NodeLnk* const&) const noexcept;
  struct BST<Data>::NodeLnk*& FindPointerToMax(struct BST<Data>::NodeLnk*&) noexcept;   
  struct BST<Data>::NodeLnk* const& FindPointerToMax(struct BST<Data>::NodeLnk* const&) const noexcept;

  struct BST<Data>::NodeLnk*& FindPointerTo(struct BST<Data>::NodeLnk*&, const Data&) noexcept;
  struct BST<Data>::NodeLnk* const& FindPointerTo(struct BST<Data>::NodeLnk* const&, const Data&) const noexcept;

  struct BST<Data>::NodeLnk*& FindPointerToPredecessor(struct BST<Data>::NodeLnk*&, const Data&) noexcept;
  struct BST<Data>::NodeLnk* const& FindPointerToPredecessor(struct BST<Data>::NodeLnk* const&, const Data&) const noexcept;
  struct BST<Data>::NodeLnk*& FindPointerToSuccessor(struct BST<Data>::NodeLnk*&, const Data&) noexcept;
  struct BST<Data>::NodeLnk* const& FindPointerToSuccessor(struct BST<Data>::NodeLnk* const&, const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
