
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  Iterator& operator=(const Iterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Iterator& operator=(Iterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator*() const = 0; // (non-mutable version; concrete function must throw std::out_of_range when terminated)

  virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class MutableIterator : virtual public Iterator<Data>{
                        // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~MutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableIterator& operator=(const MutableIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MutableIterator& operator=(MutableIterator<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutableIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MutableIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator*() = 0; // (mutable version; concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data>{
                        // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ForwardIterator& operator=(const ForwardIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  ForwardIterator& operator=(ForwardIterator<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const ForwardIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual ForwardIterator& operator++() = 0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BackwardIterator : virtual public Iterator<Data>{
                          // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BackwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BackwardIterator& operator=(const BackwardIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BackwardIterator& operator=(BackwardIterator<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BackwardIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BackwardIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual BackwardIterator& operator--() = 0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BidirectionalIterator : virtual public ForwardIterator<Data>,
                              virtual public BackwardIterator<Data>{
                              // Must extend ForwardIterator<Data>,
                              //             BackwardIterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BidirectionalIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BidirectionalIterator& operator=(const BidirectionalIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BidirectionalIterator& operator=(BidirectionalIterator<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BidirectionalIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BidirectionalIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Terminated() const noexcept override = 0; // Override Iterator member

  virtual bool ForwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)

  virtual bool BackwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator : virtual public Iterator<Data>{
                            // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResettableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResettableIterator& operator=(const ResettableIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  ResettableIterator& operator=(ResettableIterator<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResettableIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const ResettableIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Reset() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
