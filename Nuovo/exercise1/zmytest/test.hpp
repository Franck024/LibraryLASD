
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../vector/vector.hpp"
#include "../list/list.hpp"


/* ************************************************************************** */

void mytest();


std::string GenerateRandomString(std::size_t );

// Vector

template <typename Data>
void testVector(int, lasd::Vector<Data>&);

void testVector();

// Liste

template <typename Data>
void testList(int, lasd::List<Data>&, lasd::Vector<Data>&);

void testList(lasd::Vector<int>&);

void testList();

/* ************************************************************************** */

#endif
