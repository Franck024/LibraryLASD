
#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() { 
  int scelta;

  std::cout << "Lasd Libraries 2023" << std::endl;

  do {
      // Mostra il menu
      std::cout <<std::endl << "Menu:" << std::endl;
      std::cout << "1. Test del professore" << std::endl;
      std::cout << "2. Test dello studente" << std::endl;
      std::cout << "3. Chiudi il programma" << std::endl;
      std::cout << "Inserisci la tua scelta: ";
      std::cin >> scelta;

      // Effettua la scelta dell'utente
      switch (scelta) {
          case 1:
              lasdtest();
              break;
          case 2:
              mytest();
              break;
          case 3:
              std::cout << "Chiusura del programma." << std::endl;
              break;
          default:
              std::cout << "Scelta non valida. Riprova." << std::endl;
              break;
      }
  } while (scelta != 3); 

  return 0;
}
