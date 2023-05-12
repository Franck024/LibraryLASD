
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data>{
                      // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  MutableBinaryTree<Data>::size;

  struct NodeVec : virtual public MutableBinaryTree<Data>::MutableNode{ // Must extend MutableNode

  private:

    // ...

  protected:


  public:

    Vector<NodeVec*> *vectoreNode = nullptr;
    Data element;
    ulong iNode;

//****** credo
    NodeVec() = default;
    NodeVec(Vector<NodeVec*>*, Data&, ulong);
    virtual ~NodeVec() = default;
    Data& Element() noexcept override;
    bool HasLeftChild() const noexcept override; 
    bool HasRightChild() const noexcept override; 
    Node& LeftChild() const override; 
    Node& RightChild() const override;
///***** fine
  };
  
  Vector<NodeVec*> *treevec = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const MappableContainer<Data>&); // A binary tree obtained from a MappableContainer
  BinaryTreeVec(MutableMappableContainer<Data>&&); // A binary tree obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec<Data>& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec<Data>& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&) const noexcept;
  bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

  /* ************************************************************************ */

 // Specific member functions (inherited from BinaryTree)

  Node& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  MutableNode& Root() const override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  void BreadthFold(const FoldFunctor, void*) const override;// Override BreadthFoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  void BreadthMap(const MapFunctor) override; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableBreadthMappableContainer)

  void BreadthMap(MutableMapFunctor) override; // Override MutableBreadthMappableContainer member


};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
