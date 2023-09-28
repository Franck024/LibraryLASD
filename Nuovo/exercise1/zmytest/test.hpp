
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../stack/stack.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/queue.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"


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

void testList(lasd::Vector<std::string>&);

// StackVec

template <typename Data>
void testStackVec(int, lasd::StackVec<Data>&);

void testStackVec(lasd::Vector<std::string>&);

// StackLst

template <typename Data>
void testStackList(int, lasd::StackLst<Data>&);

void testStackList(lasd::StackLst<std::string>&);

// QueueVec

template <typename Data>
void testQueueVec(int, lasd::QueueVec<Data>&);

void testQueueVec(lasd::QueueVec<std::string>&);

// QueueLst

template <typename Data>
void testQueueList(int, lasd::QueueLst<Data>&);

void testQueueList(lasd::QueueLst<std::string>&);

/* ************************************************************************** */

#endif
