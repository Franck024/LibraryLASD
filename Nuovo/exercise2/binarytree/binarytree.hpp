
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../queue/vec/queuevec.hpp"

#include "../queue/lst/queuelst.hpp"
#include "../stack/lst/stacklst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderMappableContainer<Data>,
                   virtual public PostOrderMappableContainer<Data>,
                   virtual public InOrderMappableContainer<Data>,
                   virtual public BreadthMappableContainer<Data>{
                    // Must extend PreOrderMappableContainer<Data>,
                    //             PostOrderMappableContainer<Data>,
                    //             InOrderMappableContainer<Data>,
                    //             BreadthMappableContainer<Data>

private:

  // ...

protected:

  using InOrderMappableContainer<Data>::size;

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node&) const noexcept; // Comparison of abstract types is possible, but should not be visible.
    bool operator!=(const Node&) const noexcept; // Comparison of abstract types is possible, but should not be visible.

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    Node& operator=(Node&&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual inline bool IsLeaf() const noexcept { return !(HasLeftChild() || HasRightChild()); }; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree& operator=(const BinaryTree&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BinaryTree& operator=(BinaryTree&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree&) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree&) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(const FoldFunctor, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map( MapFunctor)const override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap( MapFunctor)const override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap( MapFunctor)const override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  void InOrderMap( MapFunctor) const override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  void BreadthMap( MapFunctor)const override; // Override BreadthMappableContainer member

protected:

  // Auxiliary member function (for PreOrderMappableContainer)
  void Fold(const FoldFunctor , void* , Node*  ) const; // aggiunto io!!!

  void PreOrderMap( MapFunctor, Node*)const ; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for PostOrderMappableContainer)

  void PostOrderMap( MapFunctor, Node*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for InOrderMappableContainer)

  void InOrderMap( MapFunctor, Node*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for BreadthMappableContainer)

  void BreadthMap( MapFunctor, Node*)const ; // Accessory function executing from one node of the tree

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer,
                          virtual public BinaryTree<Data>,
                          virtual public MutablePreOrderMappableContainer<Data>,
                          virtual public MutablePostOrderMappableContainer<Data>,
                          virtual public MutableInOrderMappableContainer<Data>,
                          virtual public MutableBreadthMappableContainer<Data>{
                          // Must extend ClearableContainer,
                          //             BinaryTree<Data>,
                          //             MutablePreOrderMappableContainer<Data>,
                          //             MutablePostOrderMappableContainer<Data>,
                          //             MutableInOrderMappableContainer<Data>,
                          //             MutableBreadthMappableContainer<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

public:

  struct MutableNode : virtual public BinaryTree<Data>::Node{
                        // Must extend Node

    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode& operator=(const MutableNode&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    MutableNode& operator=(MutableNode&&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)

    virtual MutableNode& LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree& operator=(const MutableBinaryTree&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MutableBinaryTree& operator=(MutableBinaryTree&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual MutableNode& Root() = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  void Map(MutableMapFunctor) override; // Override MutableMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)

  void PreOrderMap(MutableMapFunctor) override; // Override MutablePreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)

  void PostOrderMap(MutableMapFunctor) override; // Override MutablePostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutableInOrderMappableContainer)

  void InOrderMap(MutableMapFunctor) override; // Override MutableInOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBreadthMappableContainer)

  void BreadthMap(MutableMapFunctor) override; // Override MutableBreadthMappableContainer member

protected:

  // Auxiliary member function (for MutablePreOrderMappableContainer)

  void PreOrderMap(MutableMapFunctor, MutableNode*) ; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for MutablePostOrderMappableContainer)

  void PostOrderMap(MutableMapFunctor, MutableNode*) ; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for MutableInOrderMappableContainer)

  void InOrderMap(MutableMapFunctor, MutableNode*) ; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for MutableBreadthMappableContainer)

  void BreadthMap(MutableMapFunctor, MutableNode*) ; // Accessory function executing from one node of the tree

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data>{
                           // Must extend ForwardIterator<Data>,
                           //             ResettableIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* curr = nullptr;
  StackLst<struct BinaryTree<Data>::Node*> stk;

public:
BTPreOrderIterator() = default; // aggiunto io

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&) ; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator&) ;

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator&) ;

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator&) const noexcept;
  bool operator!=(const BTPreOrderIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
                                  virtual public BTPreOrderIterator<Data>{
                                  // Must extend MutableIterator<Data>,
                                  //             BTPreOrderIterator<Data>

private:

  // ...

protected:

  struct MutableBinaryTree<Data>::MutableNode* curr = nullptr;
  StackLst<struct MutableBinaryTree<Data>::MutableNode*> stk;

public:

  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data>&) ; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator&) ;

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator&) ;

  // Move assignment
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator&) const noexcept;
  bool operator!=(const BTPreOrderMutableIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ResettableIterator<Data>,
                            virtual public ForwardIterator<Data>{
                            // Must extend ForwardIterator<Data>,
                            //             ResettableIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* curr = nullptr;
  struct BinaryTree<Data>::Node* last = nullptr;
  StackLst<struct BinaryTree<Data>::Node*> stk;

public:
BTPostOrderIterator() = default; // aggiunto io

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>&) ; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator&) ;

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator& operator=(const BTPostOrderIterator&) ;

  // Move assignment
  BTPostOrderIterator& operator=(BTPostOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator&) const noexcept;
  bool operator!=(const BTPostOrderIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>,
                                    virtual public BTPostOrderIterator<Data>{
                                  // Must extend MutableIterator<Data>,
                                  //             BTPostOrderIterator<Data>

private:

  // ...

protected:

  struct MutableBinaryTree<Data>::MutableNode* curr = nullptr;
  struct MutableBinaryTree<Data>::MutableNode* last = nullptr;
  StackLst<struct MutableBinaryTree<Data>::MutableNode*> stk;

public:

  // Specific constructors
  BTPostOrderMutableIterator(const MutableBinaryTree<Data>&) ; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator&) ;

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderMutableIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator&) ;

  // Move assignment
  BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator&) const noexcept;
  bool operator!=(const BTPostOrderMutableIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data>{
                          // Must extend ForwardIterator<Data>,
                          //             ResettableIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* curr = nullptr;
  StackLst<struct BinaryTree<Data>::Node*> stk;

public:
BTInOrderIterator() = default; // aggiunto io


  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&) ; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator<Data>&) ;

  // Move constructor
  BTInOrderIterator(BTInOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator<Data>& operator=(const BTInOrderIterator<Data>&) ;

  // Move assignment
  BTInOrderIterator<Data>& operator=(BTInOrderIterator<Data>&&) const noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTInOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
                                  virtual public BTInOrderIterator<Data>{
                                  // Must extend MutableIterator<Data>,
                                  //             BTInOrderIterator<Data>

private:

  // ...

protected:

  struct MutableBinaryTree<Data>::MutableNode* curr = nullptr;
  StackLst<struct MutableBinaryTree<Data>::MutableNode*> stk;

public:

  // Specific constructors
  BTInOrderMutableIterator(const MutableBinaryTree<Data>&) ; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>&) ;

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderMutableIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator<Data>& operator=(const BTInOrderMutableIterator<Data>&) ;

  // Move assignment
  BTInOrderMutableIterator<Data>& operator=(BTInOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTInOrderMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data>{
                          // Must extend ForwardIterator<Data>,
                          //             ResettableIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* curr = nullptr;
  QueueLst<struct BinaryTree<Data>::Node*> que;

public:
BTBreadthIterator() = default; // aggiunto io


  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&) ; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator<Data>&) ;

  // Move constructor
  BTBreadthIterator(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator<Data>& operator=(const BTBreadthIterator<Data>&) ;

  // Move assignment
  BTBreadthIterator<Data>& operator=(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
                                  virtual public BTBreadthIterator<Data>{
                                  // Must extend MutableIterator<Data>,
                                  //             BTBreadthIterator<Data>

private:

  // ...

protected:

  struct MutableBinaryTree<Data>::MutableNode* curr = nullptr;
  QueueLst<struct MutableBinaryTree<Data>::MutableNode*> que;

public:

  // Specific constructors
  BTBreadthMutableIterator(const MutableBinaryTree<Data>&) ; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>&) ;

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthMutableIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator<Data>& operator=(const BTBreadthMutableIterator<Data>&) ;

  // Move assignment
  BTBreadthMutableIterator<Data>& operator=(BTBreadthMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
