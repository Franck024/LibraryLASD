
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data>{
                      // Must extend MutableBinaryTree<Data>

private:



protected:

  using BinaryTree<Data>::size;



  struct NodeLnk : virtual public MutableBinaryTree<Data>::MutableNode{ // Must extend MutableNode

  private:

    // ...

  protected:

    

  public:

    Data element;
    NodeLnk* leftChild = nullptr;
    NodeLnk* rightChild = nullptr;

    //****** credo
    NodeLnk(const Data&) ;
    virtual ~NodeLnk();
    Data& Element() noexcept override;
    bool HasLeftChild() const noexcept override; 
    bool HasRightChild() const noexcept override; 
    NodeLnk& LeftChild() const override; 
    NodeLnk& RightChild() const override;
    ///***** fine
  };

  NodeLnk* root = nullptr;
  NodeLnk* copyTree(const NodeLnk*);
  void clearTree(NodeLnk*);
  bool equals(const NodeLnk*, const NodeLnk*) const;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const MappableContainer<Data>&) ; // A binary tree obtained from a MappableContainer
  BinaryTreeLnk(MutableMappableContainer<Data>&&) noexcept; // A binary tree obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&) ;

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk() ;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk<Data> operator=(const BinaryTreeLnk<Data>&);

  // Move assignment
  BinaryTreeLnk<Data> operator=(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk<Data>&) const noexcept;
  bool operator!=(const BinaryTreeLnk<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  NodeLnk& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
