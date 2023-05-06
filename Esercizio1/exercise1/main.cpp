
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
  int choise;
  std::cout << "Lasd Libraries 2023" << std::endl;
  std::cout << std::endl;
  std::cout << "Cozzolino Francesco  N86002831" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  do{
    std::cout << "Digitare il comando:" << std::endl;
    std::cout << "   1. Eseguire il SimpleTest (test del professore)" << std::endl;
    std::cout << "   2. Eseguire il test dello studente" << std::endl;
    std::cout << "   3. Chiudere il programma" << std::endl;

    std::cin >> choise;

    while(choise < 1 || choise > 3){
      std::cout << "Scelta non corretta. Riprova:" << std::endl;
      std::cin >> choise;
    }

    if (choise == 1) {
      std::cout << "Hai scelto l'opzione 1.\n";
      lasdtest(); // Call in the menu of your library test!
    if (choise == 2){
      std::cout << "Hai scelto l'opzione 2.\n";
    }
          
    if (choise == 3)
      std::cout << "Chiusura programma \n";
      break;
    }
  }while(true);
  
  return 0;
}


