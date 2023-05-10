
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../container/container.hpp"
#include "../list/list.hpp"
#include "../vector/vector.hpp"
#include "../stack/stack.hpp"
#include "../queue/queue.hpp" 

/* ************************************************************************** */

void test();

template<typename Data>
void testVector(lasd::Vector<Data> &);

template<typename Data>
void StampaVec(lasd::Vector<Data> &);

/* ************************************************************************** */

#endif
