
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

  using BinaryTree<Data>::size;
  

  struct NodeVec : virtual public MutableBinaryTree<Data>::MutableNode{ // Must extend MutableNode

  private:

    // ...

  protected:

    // ...

  public:

    Vector<NodeVec*> *vectorPointer = nullptr;
    Data element;
    ulong indexNode;


//------ aggiunti io---------
    inline NodeVec()= default;
    NodeVec(Data&, ulong, Vector<NodeVec*>*);
    virtual ~NodeVec() = default;


    inline const Data& Element() const noexcept override{ return element; }
    inline Data& Element() noexcept override{ return element; }

    NodeVec& LeftChild() const override;
    NodeVec& LeftChild() override;

    NodeVec& RightChild() const override;  
    NodeVec& RightChild() override;

    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;

//-----------------------------
  };

Vector<NodeVec*> *treevec = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const MappableContainer<Data>&) ; // A binary tree obtained from a MappableContainer
  BinaryTreeVec(MutableMappableContainer<Data>&&) noexcept; // A binary tree obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>&) ;

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec() ;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec<Data>& operator=(const BinaryTreeVec<Data>&) ;

  // Move assignment
  BinaryTreeVec<Data>& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&) const noexcept;
  bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  NodeVec& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void BreadthFold(const FoldFunctor, void*) const override; // Override BreadthFoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void BreadthMap( MapFunctor) const override; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableBreadthMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  void BreadthMap(MutableMapFunctor) override; // Override MutableBreadthMappableContainer member


//-----per non rendere la classe astratta-----------

void PreOrderFold(const FoldFunctor, void*) const override;
void PreOrderFold(const FoldFunctor, void*, NodeVec*) const ;

void PostOrderFold(const FoldFunctor, void*) const override;
void PostOrderFold(const FoldFunctor, void*, NodeVec*) const ;

void InOrderFold(const FoldFunctor, void*) const override;
void InOrderFold(const FoldFunctor, void*, NodeVec*) const ;

//--------------------------------------------------
//--------per evitare risultato inatteso in esec ---
inline void Fold(const FoldFunctor fun, void* acc) const override{PreOrderFold(fun,acc);}

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
