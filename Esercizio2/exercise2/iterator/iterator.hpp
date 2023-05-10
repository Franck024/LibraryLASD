
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
  virtual operator=(const Iterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual operator=(Iterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual operator==(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  virtual operator!=(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual operator*() const = 0; // (non-mutable version; concrete function must throw std::out_of_range when terminated)

  virtual Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

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
  virtual operator=(const MutableIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual operator=(const MutableIterator<Data>&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual operator==(const MutableIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  virtual operator!=(const MutableIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual operator*() = 0; // (mutable version; concrete function must throw std::out_of_range when terminated)

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
  virtual operator=(const ForwardIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual operator=(ForwardIterator<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual operator==(const ForwardIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  virtual operator!=(const ForwardIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual operator++() = 0; // (concrete function must throw std::out_of_range when terminated)

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
  virtual operator=(const BackwardIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual operator=(const BackwardIterator<Data>&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual operator==(const BackwardIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  virtual operator!=(const BackwardIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual operator--() = 0; // (concrete function must throw std::out_of_range when terminated)

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
  virtual operator=(const BidirectionalIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual operator=(const BidirectionalIterator<Data>&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual operator==(const BidirectionalIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  virtual operator!=(const BidirectionalIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Terminated() const noexcept override; // Override Iterator member

  virtual ForwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)

  virtual BackwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)

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
  virtual operator=(const ResettableIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual operator=(const ResettableIterator<Data>&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual operator==(const ResettableIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  virtual operator!=(const ResettableIterator<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Reset() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
