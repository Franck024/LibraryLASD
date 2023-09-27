#include "test.hpp"

#include <iostream>
#include <random>
#include <string>


using namespace std;

/* ************************************************************************** */

std::string GenerateRandomString(std::size_t length) {
    static const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<std::size_t> distribution(0, characters.size() - 1);

    std::string random_string;
    random_string.reserve(length);

    for (std::size_t i = 0; i < length; ++i) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}

template <typename Data>
void testVector(int tipo, lasd::Vector<Data>& v1){
    int i = 0;
    (tipo == 0 ? cout <<"(" << i++ << ") Creazione di un vettore di interi vuoto" << endl 
    : cout <<"(" << i++ << ") Creazione di un vettore di double vuoto" << endl);


    cout <<"(" << i++ << ") Inserimento di 10 elementi nel vettore" << endl;

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

    if(tipo == 0)      
        for(int j = 0; j < 10; j++){
            v1[j] = distxI(generator);
        }
    else 
        for(int j = 0; j < 10; j++){
            v1[j] = distxD(generator);
        }     

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Inserimento in front" << endl;
    (tipo == 0 ?  v1.Front() = distxI(generator) : v1.Front() = distxD(generator));

    cout <<"(" << i++ << ") Inserimento in back" << endl;
    (tipo == 0 ?  v1.Back() = distxI(generator) : v1.Back() = distxD(generator));

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    (tipo == 0 ?  v1.Front() = distxI(generator) : v1.Front() = distxD(generator));

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    (tipo == 0 ?  v1.Back() = distxI(generator) : v1.Back() = distxD(generator));

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Ordinamento" << endl;
    v1.Sort();

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa del vettore con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa del vettore con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    v1.Resize(15);
    cout <<"(" << i++ << ") Inserimento nuovi 15 elementi" << endl;
    if(tipo == 0)      
        for(int j = 0; j < 15; j++){
            v1[j] = distxI(generator);
        }
    else 
        for(int j = 0; j < 15; j++){
            v1[j] = distxD(generator);
        }    


    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Nuovo vettore con copy costructor" << endl;
    lasd::Vector<Data> v2(v1);

    cout <<"(" << i++ << ") I due vettori sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo vettore con move costructor" << endl;
    lasd::Vector<Data> v3(std::move(v1));

    cout <<"(" << i++ << ") I due vettori sono uguali?   ";
    cout << (v1 == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo vettore con copy assignment" << endl;
    lasd::Vector<Data> v4 = v2;

    cout <<"(" << i++ << ") I due vettori sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo vettore con move assignment" << endl;
    lasd::Vector<Data> v5 = std::move(v2);

    cout <<"(" << i++ << ") I due vettori sono uguali?   ";
    cout << (v2 == v5 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    int sum = 0;
    v3.Fold([](const Data& x, void* y){*(Data*)y += x;}, &sum);
    cout << sum << endl;

}

//*****************************************************************************************


void testVector(){
    int i = 0;
    cout <<"(" << i++ << ") Creazione di un vettore di stringhe vuoto" << endl;
    lasd::Vector<std::string> v1(10);

    cout <<"(" << i++ << ") Inserimento di 10 elementi nel vettore" << endl;

    std::default_random_engine generator(std::random_device{}());

    for(int j = 0; j < 10; j++){
        v1[j] = GenerateRandomString(3);
    }
    

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Inserimento in front" << endl;
    v1.Front() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Inserimento in back" << endl;
    v1.Back() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    v1.Front() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    v1.Back() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Ordinamento" << endl;
    v1.Sort();

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa del vettore con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa del vettore con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    v1.Resize(15);
    cout <<"(" << i++ << ") Inserimento nuovi 15 elementi" << endl;
    for(int j = 0; j < 15; j++){
        v1[j] = GenerateRandomString(3);
    }

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Nuovo vettore con copy costructor" << endl;
    lasd::Vector<std::string> v2(v1);

    cout <<"(" << i++ << ") I due vettori sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo vettore con move costructor" << endl;
    lasd::Vector<std::string> v3(std::move(v1));

    cout <<"(" << i++ << ") I due vettori sono uguali?   ";
    cout << (v1 == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo vettore con copy assignment" << endl;
    lasd::Vector<std::string> v4 = v2;

    cout <<"(" << i++ << ") I due vettori sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo vettore con move assignment" << endl;
    lasd::Vector<std::string> v5 = std::move(v2);

    cout <<"(" << i++ << ") I due vettori sono uguali?   ";
    cout << (v2 == v5 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold per concatenare:   ";
    std::string conc = "";
    v3.Fold([](const std::string& x, void* y){*(std::string*)y += x;}, &conc);
    cout << conc << endl;

}

//********************************** LISTE ************************************************


template <typename Data>
void testList(int tipo, lasd::List<Data>& v1, lasd::Vector<Data>& v){
    int i = 0;
    (tipo == 0 ? cout <<"(" << i++ << ") Creazione di una lista di interi vuoto" << endl 
    : cout <<"(" << i++ << ") Creazione di una lista di double vuoto" << endl);


    cout <<"(" << i++ << ") Inserimento di 10 elementi nel vettore" << endl;

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

    if(tipo == 0)      
        for(int j = 0; j < 10; j++){
            v1.InsertAtFront(distxI(generator));
        }
    else 
        for(int j = 0; j < 10; j++){
            v1.InsertAtFront(distxD(generator));
        }     

    cout <<"(" << i++ << ") Stampa della lista:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Inserimento in front" << endl;
    (tipo == 0 ?  v1.InsertAtFront(distxI(generator)) : v1.InsertAtFront(distxD(generator)));

    cout <<"(" << i++ << ") Inserimento in back" << endl;
    (tipo == 0 ?  v1.InsertAtBack(distxI(generator)) : v1.InsertAtBack(distxD(generator)));

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    (tipo == 0 ?  v1.Front() = distxI(generator) : v1.Front() = distxD(generator));

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    (tipo == 0 ?  v1.Back() = distxI(generator) : v1.Back() = distxD(generator));

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Stampa della lista:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa del vettore con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa del vettore con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Inserimento nuovi 15 elementi" << endl;
    if(tipo == 0)      
        for(int j = 0; j < 10; j++){
            v1.InsertAtFront(distxI(generator));
        }
    else 
        for(int j = 0; j < 10; j++){
            v1.InsertAtFront(distxD(generator));
        }     


    cout <<"(" << i++ << ") Stampa della lista:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Nuova lista con copy costructor" << endl;
    lasd::List<Data> v2(v1);

    cout <<"(" << i++ << ") Le due liste sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuova lista con move costructor" << endl;
    lasd::List<Data> v3(std::move(v1));

    cout <<"(" << i++ << ") Le due liste sono uguali?   ";
    cout << (v1 == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuova lista con copy assignment" << endl;
    lasd::List<Data> v4 = v2;

    cout <<"(" << i++ << ") Le due liste sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuova lista con move assignment" << endl;
    lasd::List<Data> v5 = std::move(v2);

    cout <<"(" << i++ << ") Le due liste sono uguali?   ";
    cout << (v2 == v5 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    int sum = 0;
    v3.Fold([](const Data& x, void* y){*(Data*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Utilizzo insertAll con count 2:   ";
    (v3.InsertSome(v, 2) == 0 ? cout << "No" : cout << "Si") << endl;

    cout <<"(" << i++ << ") Stampa della lista:   ";
    v3.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Pulizia" << endl;
    v3.Clear();

    cout <<"(" << i++ << ") Utilizzo insertAll :   ";
    (v3.InsertAll(v) == 0 ? cout << "No" : cout << "Si") << endl;

    cout <<"(" << i++ << ") Stampa della lista:   ";
    v3.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") FrontNRemove:  ";
    cout << v3.FrontNRemove() << endl;

}

void testList(lasd::Vector<std::string>& v){
    int i = 0;
    cout <<"(" << i++ << ") Creazione di una lista di stringhe vuoto" << endl; 
    lasd::List<std::string> v1;

    cout <<"(" << i++ << ") Inserimento di 10 elementi nel vettore" << endl;

    std::default_random_engine generator(std::random_device{}());

    for(int j = 0; j < 10; j++){
        v1.InsertAtFront(GenerateRandomString(3));
    }    

    cout <<"(" << i++ << ") Stampa della lista:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Inserimento in front" << endl;
    v1.InsertAtFront(GenerateRandomString(3));

    cout <<"(" << i++ << ") Inserimento in back" << endl;
    v1.InsertAtBack(GenerateRandomString(3));

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    v1.Front() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    v1.Back() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Stampa della lista:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa del vettore con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa del vettore con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Inserimento nuovi 15 elementi" << endl;
    v1.InsertAtFront(GenerateRandomString(3));   


    cout <<"(" << i++ << ") Stampa della lista:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Nuova lista con copy costructor" << endl;
    lasd::List<std::string> v2(v1);

    cout <<"(" << i++ << ") Le due liste sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuova lista con move costructor" << endl;
    lasd::List<std::string> v3(std::move(v1));

    cout <<"(" << i++ << ") Le due liste sono uguali?   ";
    cout << (v1 == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuova lista con copy assignment" << endl;
    lasd::List<std::string> v4 = v2;

    cout <<"(" << i++ << ") Le due liste sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuova lista con move assignment" << endl;
    lasd::List<std::string> v5 = std::move(v2);

    cout <<"(" << i++ << ") Le due liste sono uguali?   ";
    cout << (v2 == v5 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    std::string sum = "";
    v3.Fold([](const std::string& x, void* y){*(std::string*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Utilizzo insertAll con count 2:   ";
    (v3.InsertSome(v, 2) == 0 ? cout << "No" : cout << "Si") << endl;

    cout <<"(" << i++ << ") Stampa della lista:   ";
    v3.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Pulizia" << endl;
    v3.Clear();

    cout <<"(" << i++ << ") Utilizzo insertAll :   ";
    (v3.InsertAll(v) == 0 ? cout << "No" : cout << "Si") << endl;

    cout <<"(" << i++ << ") Stampa della lista:   ";
    v3.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") FrontNRemove:  ";
    cout << v3.FrontNRemove() << endl;

}

//*****************************************************************************************


void mytest(){    
  cout << endl << "~*~#~*~ Test dello studente ~*~#~*~ " << endl;
  cout << endl << "~*~#~*~ Cozzolino Francesco ~*~#~*~ " << endl;
  cout << endl << "~*~#~*~ N86002831 ~*~#~*~ " << endl << endl << endl;

  lasd::Vector<int> v1(10);
  lasd::Vector<int> v2(10);

    cout << endl << "--- Vettori di interi" << endl << endl;
    testVector(0, v1);

    cout << endl << "--- Vettori di double" << endl << endl;
    testVector(1, v2);
    
    cout << endl << "--- Vettori di stringhe" << endl << endl;
    testVector();


  lasd::List<int> l1;
  lasd::List<double> l2;
  lasd::Vector<int> v3(5);
    for(int i = 0; i < 5; i++){
        v3[i] = (i+7)*7;
    }
  lasd::Vector<double> v4(5);
    for(int i = 0; i < 5; i++){
        v4[i] = (i+7)*7.0;
    }
  lasd::Vector<std::string> v5(5);
    for(int i = 0; i < 5; i++){
        v5[i] = GenerateRandomString(3);
    }


    cout << endl << "--- Liste di interi" << endl << endl;
    testList(0, l1, v3);

    cout << endl << "--- Liste di double" << endl << endl;
    testList(1, l2, v4);

    cout << endl << "--- Liste di stringhe" << endl << endl;
    testList(v5);
   
}

/* ************************************************************************** */


