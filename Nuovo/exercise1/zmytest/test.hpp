
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../vector/vector.hpp"


/* ************************************************************************** */

void mytest();

template <typename Data>
void testVector(int, lasd::Vector<Data>&);

void testVector();

std::string GenerateRandomString(std::size_t );
/* ************************************************************************** */

#endif
