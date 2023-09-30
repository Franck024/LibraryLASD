
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
#include "../iterator/iterator.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../bst/bst.hpp"
#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"


/* ************************************************************************** */

void mytest();

std::string GenerateRandomString(std::size_t );

// test HT con indirizzamento aperto

template <typename Data>
void testHTOpn(int, lasd::Vector<Data>&);

// test HT con indirizzo chiuso

template <typename Data>
void testHTCls(int, lasd::Vector<Data>&);

/* ************************************************************************** */

#endif
