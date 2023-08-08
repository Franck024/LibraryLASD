
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer,
              virtual public DictionaryContainer<Data>,
              virtual public LinearContainer<Data>{
              // Must extend ClearableContainer,
              //             DictionaryContainer<Data>,
              //             LinearContainer<Data>

private:

// per non rendere la classe astratta-----------------------------------------------------
  inline bool InsertAll(const MappableContainer<Data>& x){return false;} // Copy of the value; From MappableContainer; True if all are inserted
  inline bool InsertAll(MappableContainer<Data>&& x) noexcept{return false;} // Move of the value; From MutableMappableContainer; True if all are inserted
  inline bool RemoveAll(const MappableContainer<Data>& x) {return false;} // From MappableContainer; True if all are removed

  inline bool InsertSome(const MappableContainer<Data>& x)  {return false;} // Copy of the value; From MappableContainer; True if some is inserted
  inline bool InsertSome(MappableContainer<Data>&& x) noexcept {return false;} // Move of the value; From MutableMappableContainer; True if some is inserted
  inline bool RemoveSome(const MappableContainer<Data>& x){return false;} // From MappableContainer; True if some is removed
///----------------------------------------------------------------------------------------

protected:

  using Container::size;

  struct Node {

    Data valore;
    Node* next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node() = default;
    Node(const Data&);
    Node(Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node&);

    // Move constructor
    Node(Node&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  Node* head = nullptr;
  Node* tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(MappableContainer<Data>&) ; // A list obtained from a MappableContainer
  List(MutableMappableContainer<Data>&&) ; // A list obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List&) ;

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
   ~List() ;

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&) ;

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&) noexcept; // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value
  void RemoveFromFront() ; // (must throw std::length_error when empty)
  Data FrontNRemove() ; // (must throw std::length_error when empty)

  void InsertAtBack(const Data&) noexcept; // Copy of the value
  void InsertAtBack(Data&&) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) ; // Copy of the value
  bool Insert(Data&& ) noexcept; // Move of the value
  bool Remove(const Data& ) ;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](const ulong) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const ulong) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(const FoldFunctor, void *) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderFoldableContainer)

  void PreOrderFold(const FoldFunctor, void*) const override; // Override PreOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderFoldableContainer)

  void PostOrderFold(const FoldFunctor, void*) const override; // Override PostOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(const MapFunctor) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(const MapFunctor) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(const MapFunctor)  override; // Override PostOrderMappableContainer member

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

protected:

  // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

  void PreOrderFold(const FoldFunctor, void*, Node*) const; // Accessory function executing from one point of the list onwards
  void PostOrderFold(const FoldFunctor, void*, Node*) const;  // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)

  void PreOrderMap(const MapFunctor, Node*) ; // Accessory function executing from one point of the list onwards
  void PostOrderMap(const MapFunctor, Node*) ; // Accessory function executing from one point of the list onward

  /* ************************************************************************ */

  // Auxiliary member functions (for MutablePreOrderMappableContainer & MutablePostOrderMappableContainer)

  void PreOrderMap(MutableMapFunctor, Node*) ; // Accessory function executing from one point of the list onwards
  void PostOrderMap(MutableMapFunctor, Node*); // Accessory function executing from one point of the list onward

  /* ************************************************************************ */

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
