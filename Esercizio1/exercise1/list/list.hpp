
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
class List :virtual public ClearableContainer,
            virtual public DictionaryContainer<Data>,
            virtual public LinearContainer<Data>{
              // Must extend ClearableContainer,
              //             DictionaryContainer<Data>,
              //             LinearContainer<Data>

private:

  // ...

protected:

  using Container::size;

  struct Node {

    Data valore_nodo;
    Node* next = nullptr;


    /* ********************************************************************** */

    // Specific constructors
    Node(const Data&);
    Node(Data&&);   // aggiunto io

    /* ********************************************************************** */

    // Copy constructor
    Node& operator=(const Node&);

    // Move constructor
    Node& operator=(Node&&);

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
  List() ;

  /* ************************************************************************ */

  // Specific constructor
  List(const MappableContainer<Data>&) ; // A list obtained from a MappableContainer
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
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List<Data>&) const noexcept;
	bool operator!=(const List<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&) noexcept; // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&) noexcept; // Copy of the value
  void InsertAtBack(Data&&) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  bool Insert(const Data&) override; // Copy of the value
  bool Insert(Data&&) override; // Move of the value
  bool Remove(const Data&) override;

  /////// credo///
  // non viene chiesto di implementare i seguenti metodi ma
  // dato che si cerca di ereditare da una classe astratta,
  // tutti i metodi devono essere implementati. 
  // Li dichiaro = delete perchè non mi servono
  // bool InsertAll(const MappableContainer<Data>&) noexcept override = delete;
  // bool InsertAll(MutableMappableContainer<Data>&&) noexcept override = delete;
  // bool RemoveAll(const MappableContainer<Data>&) override = delete;
  // bool InsertSome(const MappableContainer<Data>&, const Data&) noexcept override = delete;
  // bool InsertSome(MutableMapFunctor<Data>&&, const Data&) noexcept override = delete;
  // bool RemoveSome(const MappableContainer<Data>&, const Data&) override = delete;

  ////////////////

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](const ulong) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](ulong) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(const FoldFunctor&, void*)const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderFoldableContainer)

  void  PreOrderFold(const FoldFunctor, void*) const override; // Override PreOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderFoldableContainer)

  void  PostOrderFold(const FoldFunctor, void*) const override; // Override PostOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(const MapFunctor&) const override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFunctor) override; // Override PreOrderMappableContainer member
  

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFunctor) override; // Override PostOrderMappableContainer member
  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  void Map(const MutableMapFunctor&) const override; // Override MutableMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)

  void PreOrderMap( MutableMapFunctor) override; // Override MutablePreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)

  void PostOrderMap(MutableMapFunctor) override; // Override MutablePostOrderMappableContainer member

protected:

  // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

  void PreOrderFold(const FoldFunctor, void*, Node*) const; // Accessory function executing from one point of the list onwards
  void PostOrderFold(const FoldFunctor, void*, Node*) const; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)

  void PreOrderMap(MapFunctor, Node*) ; // Accessory function executing from one point of the list onwards
  void PostOrderMap(MapFunctor, Node*) ; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for MutablePreOrderMappableContainer & MutablePostOrderMappableContainer)

  void PreOrderMap(MutableMapFunctor, Node*) ; // Accessory function executing from one point of the list onwards
  void PostOrderMap(MutableMapFunctor, Node*) ; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  //per non rendere la classe astratta vado ad implementare tutti i metodi virtual
  // EXIST
  bool Exists(const Data&) const noexcept override;
};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
