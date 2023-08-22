
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

  // ...

protected:

  using BinaryTree<Data>::size;
  
  // ...

  struct NodeLnk : virtual public MutableBinaryTree<Data>::MutableNode{ // Must extend MutableNode

  private:



  protected:



  public:

    Data it;
    NodeLnk* rc = nullptr; // nodo destro
    NodeLnk* lc = nullptr; // nodo sx

//------ aggiunti io---------
    inline NodeLnk(){ rc = lc = nullptr; }
    inline NodeLnk(const Data& val) { NodeLnk(); it = val; }
    inline ~NodeLnk(){ delete rc; delete lc; };


    inline const Data& Element() const noexcept override{ return it; }
    inline Data& Element() noexcept override{ return it; }

    NodeLnk& LeftChild() const override;
    NodeLnk& LeftChild() override;

    NodeLnk& RightChild() const override;  
    NodeLnk& RightChild() override;

    inline bool HasLeftChild() const noexcept override{ return (lc == nullptr); };
    inline bool HasRightChild() const noexcept override{ return (rc == nullptr); };

//-----------------------------
  
  };

NodeLnk* root = nullptr;

void CopyNodes(NodeLnk*& , const NodeLnk* );

public:

  // Default constructor
  BinaryTreeLnk() = default ;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const MappableContainer<Data>&) ; // A binary tree obtained from a MappableContainer
  BinaryTreeLnk(MutableMappableContainer<Data>&&) ; // A binary tree obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&) ;

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk() ;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk<Data>& operator=(const BinaryTreeLnk<Data>&) ;

  // Move assignment
  BinaryTreeLnk<Data>& operator=(BinaryTreeLnk<Data>&&) noexcept;

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


//-----per non rendere la classe astratta-----------

using typename FoldableContainer<Data>::FoldFunctor;
void PreOrderFold(const FoldFunctor, void*) const override;
void PreOrderFold(const FoldFunctor, void*, NodeLnk*) const ;

void PostOrderFold(const FoldFunctor, void*) const override;
void PostOrderFold(const FoldFunctor, void*, NodeLnk*) const ;

void InOrderFold(const FoldFunctor, void*) const override;
void InOrderFold(const FoldFunctor, void*, NodeLnk*) const ;

void BreadthFold(const FoldFunctor, void*) const override;
void BreadthFold(const FoldFunctor, void*, NodeLnk*) const ;

//--------------------------------------------------
void funzioneCostruzione(const Data& , NodeLnk*& );
void funzioneCostruzione(Data&& , NodeLnk*& );

//--------per evitare risultato inatteso in esec ---
void Fold(const FoldFunctor, void*) const override;

using typename MappableContainer<Data>::MapFunctor;
void Map(MapFunctor) const override;

void PreOrderMap(MapFunctor) const override;
void PreOrderMap(MapFunctor, NodeLnk*) const ;
};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
