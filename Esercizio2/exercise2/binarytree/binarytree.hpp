
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

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

    virtual Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept; // (concrete function should not throw exceptions)
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
  BinaryTree& operator=(const BinaryTree<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BinaryTree& operator=(BinaryTree<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(const FoldFunctor&, void*) const override ; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(const MapFunctor&) const override ; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFunctor) const override ; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFunctor) const override ;// Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  void InOrderMap(const MapFunctor) const override ; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  void BreadthMap(const MapFunctor) const override ; // Override BreadthMappableContainer member

protected:

  // Auxiliary member function (for PreOrderMappableContainer)

  void PreOrderMap(MapFunctor, Node*) const ;// Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for PostOrderMappableContainer)

  void PostOrderMap(MapFunctor, Node*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for InOrderMappableContainer)

  void InOrderMap(const MapFunctor, Node*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for BreadthMappableContainer)

  void BreadthMap(const MapFunctor, Node*) const;// Accessory function executing from one node of the tree

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

  // ...

public:

  struct MutableNode : virtual public BinaryTree<Data>::Node{
                        // Must extend Node

    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = delete;

    /* ********************************************************************** */

    // Copy assignment
    bool operator=(const MutableNode&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    bool operator=(MutableNode&&) = delete; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)

    virtual MutableNode& LeftChild() const = 0 ; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = delete;

  /* ************************************************************************ */

  // Copy assignment
  bool operator=(const MutableBinaryTree<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  bool operator=(MutableBinaryTree<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual MutableNode& Root() = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  void Map(const MutableMapFunctor&) const override ; // Override MutableMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)

  void PreOrderMap(MutableMapFunctor) const override ; // Override MutablePreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)

  void PostOrderMap(MutableMapFunctor) const override ; // Override MutablePostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutableInOrderMappableContainer)

  void InOrderMap(const MutableMapFunctor) const override ; // Override MutableInOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBreadthMappableContainer)

  void BreadthMap(const MutableMapFunctor) const override ; // Override MutableBreadthMappableContainer member

protected:

  // Auxiliary member function (for MutablePreOrderMappableContainer)

  void PreOrderMap(MutableMapFunctor, MutableNode*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for MutablePostOrderMappableContainer)

  void PostOrderMap(MutableMapFunctor, MutableNode*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for MutableInOrderMappableContainer)

  void InOrderMap(const MutableMapFunctor, MutableNode*) const ; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for MutableBreadthMappableContainer)

  void BreadthMap(const MutableMapFunctor, MutableNode*) const; // Accessory function executing from one node of the tree

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

  struct BinaryTree<Data>::Node* current = nullptr;
  StackLst<struct BinaryTree<Data>::Node*> stk;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data>&);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator<Data>&);

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPreOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() const noexcept override; // (should not throw exceptions)

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


public:

  // Specific constructors
  BTPreOrderMutableIterator(const MutableBinaryTree<Data>&) ; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>&) ;

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator<Data>&) ;

  // Move assignment
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTPreOrderMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data>{
                            // Must extend ForwardIterator<Data>,
                            //             ResettableIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* current = nullptr;
  struct BinaryTree<Data>::Node* last = nullptr;
  StackLst<struct BinaryTree<Data>::Node*> stk;

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>&) ; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator<Data>&) ;

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator& operator=(const BTPostOrderIterator<Data>&);

  // Move assignment
  BTPostOrderIterator& operator=(BTPostOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPostOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() const noexcept; // (should not throw exceptions)

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


public:

  // Specific constructors
  BTPostOrderMutableIterator(const MutableBinaryTree<Data>&) ; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data>&) ;

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator<Data>&) ;

  // Move assignment
  BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTPostOrderMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

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

  struct BinaryTree<Data>::Node* current = nullptr;
  StackLst<struct BinaryTree<Data>::Node*> stk;

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&) ; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator<Data>&) ;

  // Move constructor
  BTInOrderIterator(BTInOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator& operator=(const BTInOrderIterator<Data>&);

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTInOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() const noexcept override; // (should not throw exceptions)

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
  virtual ~BTInOrderMutableIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator<Data>&) ;

  // Move assignment
  BTInOrderMutableIterator& operator=(BTInOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTInOrderMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

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

  struct BinaryTree<Data>::Node* current = nullptr;
  QueueLst<struct BinaryTree<Data>::Node*> que;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&) ; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator<Data>&) ;

  // Move constructor
  BTBreadthIterator(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() ;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator& operator=(const BTBreadthIterator<Data>&);

  // Move assignment
  BTBreadthIterator& operator=(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() const noexcept; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual MutableIterator<Data>,
                                  virtual public BTBreadthIterator<Data>{
                                  // Must extend MutableIterator<Data>,
                                  //             BTBreadthIterator<Data>

private:

  // ...

protected:


public:

  // Specific constructors
  BTBreadthMutableIterator(const MutableBinaryTree<Data>&); // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>&);

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator();

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator<Data>&);

  // Move assignment
  BTBreadthMutableIterator& operator=(BTBreadthMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
