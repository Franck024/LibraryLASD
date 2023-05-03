
#include "zmytest/test.hpp"

#include "zlasdtest/test.hpp"

/* ************************************************************************** */

#include "container/container.hpp"
#include "container/dictionary.hpp"
#include "container/foldable.hpp"
#include "container/linear.hpp"
#include "container/mappable.hpp"
#include "container/testable.hpp"

#include "vector/vector.hpp"
#include "list/list.hpp"

#include "stack/vec/stackvec.hpp"
#include "stack/lst/stacklst.hpp"
#include "queue/lst/queuelst.hpp"
#include "queue/vec/queuevec.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2023" << std::endl;
  lasdtest(); // Call in the menu of your library test!
  return 0;
}
