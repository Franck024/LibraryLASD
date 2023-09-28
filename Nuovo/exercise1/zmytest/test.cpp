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

//********************************** VECTOR ************************************************

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

//********************************** STACKVEC ************************************************

template <typename Data>
void testStackVec(int tipo, lasd::StackVec<Data>& v1){
    int i = 0;
    (tipo == 0 ? cout <<"(" << i++ << ") Creazione di uno stackVec di interi vuoto" << endl 
    : cout <<"(" << i++ << ") Creazione di uno stackVec di double vuoto" << endl);

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

    cout <<"(" << i++ << ") Stampa del lo stackVec:   ";
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

    cout << endl <<"(" << i++ << ") Stampa dello stackVec con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa dello stackVec con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") ;

    cout << endl <<"(" << i++ << ") Nuovo stackVec con copy costructor" << endl;
    lasd::StackVec<Data> v2(v1);

    cout <<"(" << i++ << ") I due stackVec sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackVec con list" << endl;
    lasd::List<Data> l;
    for(int j = 0; j < 5; j++){
        (tipo == 0 ?  l.InsertAtFront(distxI(generator)) : l.InsertAtFront(distxD(generator)));
    }
    lasd::StackVec<Data> vN(l);

    cout <<"(" << i++ << ") Stampa del nuovo stackVec:   ";
    vN.Map([](const Data& x){cout << x << " ";});


    cout << std::endl <<"(" << i++ << ") Nuovo stackVec con move costructor" << endl;
    lasd::StackVec<Data> v3(std::move(vN));

    cout <<"(" << i++ << ") I due stackVec sono uguali?   ";
    cout << (vN == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackVec con copy assignment" << endl;
    lasd::StackVec<Data> v4 = v2;

    cout <<"(" << i++ << ") I due stackVec sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackVec con move assignment" << endl;
    lasd::StackVec<Data> v5 = std::move(v2);

    cout <<"(" << i++ << ") I due stackVec sono uguali?   ";
    cout << (v2 == v5 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    int sum = 0;
    v3.Fold([](const Data& x, void* y){*(Data*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Stampo Top:   ";
    cout << v3.Top() << endl;

    cout <<"(" << i++ << ") Utilizzo Pop   " << endl;
    v3.Pop();

    cout <<"(" << i++ << ") Stampo TopNPop:   ";
    cout << v3.TopNPop() << endl;

    cout <<"(" << i++ << ") Utilizzo Push:   ";
    (tipo == 0 ?  v3.Push(distxI(generator)) : v3.Push(distxD(generator)));

    cout <<std::endl <<"(" << i++ << ") Stampo stackVec:   ";
    v3.Map([](const Data& x){cout << x << " ";});

}

//*****************************************************************************************


void testStackVec(lasd::StackVec<std::string>& v1){
    int i = 0;
    cout <<"(" << i++ << ") Creazione di uno stackVec di stringhe vuoto" << endl;

    std::default_random_engine generator(std::random_device{}());

    cout <<"(" << i++ << ") Stampa del lo stackVec:   ";
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

    cout << endl <<"(" << i++ << ") Stampa dello stackVec con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa dello stackVec con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") ;

    cout << endl <<"(" << i++ << ") Nuovo stackVec con copy costructor" << endl;
    lasd::StackVec<std::string> v2(v1);

    cout <<"(" << i++ << ") I due stackVec sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackVec con list" << endl;
    lasd::List<std::string> l;
    for(int j = 0; j < 5; j++){
        l.InsertAtFront(GenerateRandomString(3));
    }
    lasd::StackVec<std::string> vN(l);

    cout <<"(" << i++ << ") Stampa del nuovo stackVec:   ";
    vN.Map([](const std::string& x){cout << x << " ";});


    cout << std::endl <<"(" << i++ << ") Nuovo stackVec con move costructor" << endl;
    lasd::StackVec<std::string> v3(std::move(vN));

    cout <<"(" << i++ << ") I due stackVec sono uguali?   ";
    cout << (vN == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackVec con copy assignment" << endl;
    lasd::StackVec<std::string> v4 = v2;

    cout <<"(" << i++ << ") I due stackVec sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackVec con move assignment" << endl;
    lasd::StackVec<std::string> v5 = std::move(v2);

    cout <<"(" << i++ << ") I due stackVec sono uguali?   ";
    cout << (v2 == v5 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    std::string sum = "";
    v3.Fold([](const std::string& x, void* y){*(std::string*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Stampo Top:   ";
    cout << v3.Top() << endl;

    cout <<"(" << i++ << ") Utilizzo Pop   " << endl;
    v3.Pop();

    cout <<"(" << i++ << ") Stampo TopNPop:   ";
    cout << v3.TopNPop() << endl;

    cout <<"(" << i++ << ") Utilizzo Push:   ";
    v3.Push(GenerateRandomString(3));

    cout <<std::endl <<"(" << i++ << ") Stampo stackVec:   ";
    v3.Map([](const std::string& x){cout << x << " ";});

}

//*****************************************************************************************

//********************************** STACKLST ************************************************

template <typename Data>
void testStackList(int tipo, lasd::StackLst<Data>& v1){
    int i = 0;
    (tipo == 0 ? cout <<"(" << i++ << ") Creazione di uno stackList di interi" << endl 
    : cout <<"(" << i++ << ") Creazione di uno stackList di double " << endl);

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

    cout <<"(" << i++ << ") Stampa del lo stackList:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    (tipo == 0 ?  v1.Front() = distxI(generator) : v1.Front() = distxD(generator));

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    (tipo == 0 ?  v1.Back() = distxI(generator) : v1.Back() = distxD(generator));

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa dello stackList con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa dello stackList con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") ;

    cout << endl <<"(" << i++ << ") Nuovo stackList con copy costructor" << endl;
    lasd::StackLst<Data> v2(v1);

    cout <<"(" << i++ << ") I due stackList sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackList con list" << endl;
    lasd::List<Data> l;
    for(int j = 0; j < 5; j++){
        (tipo == 0 ?  l.InsertAtFront(distxI(generator)) : l.InsertAtFront(distxD(generator)));
    }
    lasd::StackLst<Data> vN(l);

    cout <<"(" << i++ << ") Stampa del nuovo stackList:   ";
    vN.Map([](const Data& x){cout << x << " ";});


    cout << std::endl <<"(" << i++ << ") Nuovo stackList con move costructor" << endl;
    lasd::StackLst<Data> v3(std::move(vN));

    cout <<"(" << i++ << ") I due stackList sono uguali?   ";
    cout << (vN == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackList con copy assignment" << endl;
    lasd::StackLst<Data> v4 = v2;

    cout <<"(" << i++ << ") I due stackList sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackList con move assignment" << endl;
    lasd::StackLst<Data> v5 = std::move(v2);

    cout <<"(" << i++ << ") I due stackList sono uguali?   ";
    cout << (v2 == v5 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    int sum = 0;
    v3.Fold([](const Data& x, void* y){*(Data*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Stampo Top:   ";
    cout << v3.Top() << endl;

    cout <<"(" << i++ << ") Utilizzo Pop   " << endl;
    v3.Pop();

    cout <<"(" << i++ << ") Stampo TopNPop:   ";
    cout << v3.TopNPop() << endl;

    cout <<"(" << i++ << ") Utilizzo Push:   ";
    (tipo == 0 ?  v3.Push(distxI(generator)) : v3.Push(distxD(generator)));

    cout <<std::endl <<"(" << i++ << ") Stampo stackList:   ";
    v3.Map([](const Data& x){cout << x << " ";});

}

//*****************************************************************************************


void testStackList(lasd::StackLst<std::string>& v1){
    int i = 0;
    cout <<"(" << i++ << ") Creazione di uno stackList di stringhe vuoto" << endl;

    std::default_random_engine generator(std::random_device{}());

    cout <<"(" << i++ << ") Stampa del lo stackList:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    v1.Front() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    v1.Back() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa dello stackList con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa dello stackList con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") ;

    cout << endl <<"(" << i++ << ") Nuovo stackList con copy costructor" << endl;
    lasd::StackLst<std::string> v2(v1);

    cout <<"(" << i++ << ") I due stackList sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackList con list" << endl;
    lasd::List<std::string> l;
    for(int j = 0; j < 5; j++){
        l.InsertAtFront(GenerateRandomString(3));
    }
    lasd::StackLst<std::string> vN(l);

    cout <<"(" << i++ << ") Stampa del nuovo stackList:   ";
    vN.Map([](const std::string& x){cout << x << " ";});


    cout << std::endl <<"(" << i++ << ") Nuovo stackList con move costructor" << endl;
    lasd::StackLst<std::string> v3(std::move(vN));

    cout <<"(" << i++ << ") I due stackList sono uguali?   ";
    cout << (vN == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackList con copy assignment" << endl;
    lasd::StackLst<std::string> v4 = v2;

    cout <<"(" << i++ << ") I due stackList sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo stackList con move assignment" << endl;
    lasd::StackLst<std::string> v5 = std::move(v2);

    cout <<"(" << i++ << ") I due stackList sono uguali?   ";
    cout << (v2 == v5 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    std::string sum = "";
    v3.Fold([](const std::string& x, void* y){*(std::string*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Stampo Top:   ";
    cout << v3.Top() << endl;

    cout <<"(" << i++ << ") Utilizzo Pop   " << endl;
    v3.Pop();

    cout <<"(" << i++ << ") Stampo TopNPop:   ";
    cout << v3.TopNPop() << endl;

    cout <<"(" << i++ << ") Utilizzo Push:   ";
    v3.Push(GenerateRandomString(3));

    cout <<std::endl <<"(" << i++ << ") Stampo stackList:   ";
    v3.Map([](const std::string& x){cout << x << " ";});

}

//*****************************************************************************************

//********************************** QUEUEVEC ************************************************

template <typename Data>
void testQueueVec(int tipo, lasd::QueueVec<Data>& v1){
    int i = 0;
    (tipo == 0 ? cout <<"(" << i++ << ") Creazione di uno QueueVec di interi" << endl 
    : cout <<"(" << i++ << ") Creazione di uno QueueVec di double " << endl);

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

    cout <<"(" << i++ << ") Stampa dello QueueVec:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    (tipo == 0 ?  v1.Front() = distxI(generator) : v1.Front() = distxD(generator));

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    (tipo == 0 ?  v1.Back() = distxI(generator) : v1.Back() = distxD(generator));

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Stampa del QueueVec:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa dello QueueVec con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa dello QueueVec con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") ;

    cout << endl <<"(" << i++ << ") Nuovo QueueVec con copy costructor" << endl;
    lasd::QueueVec<Data> v2(v1);

    cout <<"(" << i++ << ") I due QueueVec sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo QueueVec con list" << endl;
    lasd::List<Data> l;
    for(int j = 0; j < 5; j++){
        (tipo == 0 ?  l.InsertAtFront(distxI(generator)) : l.InsertAtFront(distxD(generator)));
    }
    lasd::QueueVec<Data> vN(l);

    cout <<"(" << i++ << ") Stampa del nuovo QueueVec:   ";
    vN.Map([](const Data& x){cout << x << " ";});


    cout << std::endl <<"(" << i++ << ") Nuovo QueueVec con move costructor" << endl;
    lasd::QueueVec<Data> v3(std::move(vN));

    cout <<"(" << i++ << ") I due QueueVec sono uguali?   ";
    cout << (vN == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo QueueVec con copy assignment" << endl;
    lasd::QueueVec<Data> v4 = v2;

    cout <<"(" << i++ << ") I due QueueVec sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    int sum = 0;
    v3.Fold([](const Data& x, void* y){*(Data*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Stampo Head:   ";
    cout << v3.Head() << endl;

    cout <<"(" << i++ << ") Utilizzo Dequeue   " << endl;
    v3.Dequeue();

    cout <<"(" << i++ << ") Stampo HeadNDequeue:   ";
    cout << v3.HeadNDequeue() << endl;

    cout <<"(" << i++ << ") Utilizzo Enqueue:   ";
    (tipo == 0 ?  v3.Enqueue(distxI(generator)) : v3.Enqueue(distxD(generator)));

    cout <<std::endl <<"(" << i++ << ") Stampo QueueVec:   ";
    v3.Map([](const Data& x){cout << x << " ";});

}

//*****************************************************************************************


void testQueueVec(lasd::QueueVec<std::string>& v1){
    int i = 0;
    cout <<"(" << i++ << ") Creazione di uno QueueVec di stringhe " << endl;

    std::default_random_engine generator(std::random_device{}());

    cout <<"(" << i++ << ") Stampa del lo QueueVec:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    v1.Front() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    v1.Back() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa dello QueueVec con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa dello QueueVec con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") ;

    cout << endl <<"(" << i++ << ") Nuovo QueueVec con copy costructor" << endl;
    lasd::QueueVec<std::string> v2(v1);

    cout <<"(" << i++ << ") I due QueueVec sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo QueueVec con list" << endl;
    lasd::List<std::string> l;
    for(int j = 0; j < 5; j++){
        l.InsertAtFront(GenerateRandomString(3));
    }
    lasd::QueueVec<std::string> vN(l);

    cout <<"(" << i++ << ") Stampa del nuovo QueueVec:   ";
    vN.Map([](const std::string& x){cout << x << " ";});


    cout << std::endl <<"(" << i++ << ") Nuovo QueueVec con move costructor" << endl;
    lasd::QueueVec<std::string> v3(std::move(vN));

    cout <<"(" << i++ << ") I due QueueVec sono uguali?   ";
    cout << (vN == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo QueueVec con copy assignment" << endl;
    lasd::QueueVec<std::string> v4 = v2;

    cout <<"(" << i++ << ") I due QueueVec sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    std::string sum = "";
    v3.Fold([](const std::string& x, void* y){*(std::string*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Stampo Head:   ";
    cout << v3.Head() << endl;

    cout <<"(" << i++ << ") Utilizzo Dequeue   " << endl;
    v3.Dequeue();

    cout <<"(" << i++ << ") Stampo HeadNDequeue:   ";
    cout << v3.HeadNDequeue() << endl;

    cout <<"(" << i++ << ") Utilizzo Enqueue:   ";
    v3.Enqueue(GenerateRandomString(3));

    cout <<std::endl <<"(" << i++ << ") Stampo QueueVec:   ";
    v3.Map([](const std::string& x){cout << x << " ";});

}

//*****************************************************************************************

//********************************** QUEUELST ************************************************

template <typename Data>
void testQueueLst(int tipo, lasd::QueueLst<Data>& v1){
    int i = 0;
    (tipo == 0 ? cout <<"(" << i++ << ") Creazione di uno testQueueLst di interi" << endl 
    : cout <<"(" << i++ << ") Creazione di uno testQueueLst di double " << endl);

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

    cout <<"(" << i++ << ") Stampa dello QueueLst:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    (tipo == 0 ?  v1.Front() = distxI(generator) : v1.Front() = distxD(generator));

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    (tipo == 0 ?  v1.Back() = distxI(generator) : v1.Back() = distxD(generator));

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Stampa del QueueLst:   ";
    v1.Map([](const Data& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa dello QueueLst con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa dello QueueLst con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") ;

    cout << endl <<"(" << i++ << ") Nuovo QueueLst con copy costructor" << endl;
    lasd::QueueLst<Data> v2(v1);

    cout <<"(" << i++ << ") I due QueueLst sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo QueueLst con list" << endl;
    lasd::List<Data> l;
    for(int j = 0; j < 5; j++){
        (tipo == 0 ?  l.InsertAtFront(distxI(generator)) : l.InsertAtFront(distxD(generator)));
    }
    lasd::QueueLst<Data> vN(l);

    cout <<"(" << i++ << ") Stampa del nuovo QueueLst:   ";
    vN.Map([](const Data& x){cout << x << " ";});


    cout << std::endl <<"(" << i++ << ") Nuovo QueueLst con move costructor" << endl;
    lasd::QueueLst<Data> v3(std::move(vN));

    cout <<"(" << i++ << ") I due QueueLst sono uguali?   ";
    cout << (vN == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo QueueLst con copy assignment" << endl;
    lasd::QueueLst<Data> v4 = v2;

    cout <<"(" << i++ << ") I due QueueLst sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    int sum = 0;
    v3.Fold([](const Data& x, void* y){*(Data*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Stampo Head:   ";
    cout << v3.Head() << endl;

    cout <<"(" << i++ << ") Utilizzo Dequeue   " << endl;
    v3.Dequeue();

    cout <<"(" << i++ << ") Stampo HeadNDequeue:   ";
    cout << v3.HeadNDequeue() << endl;

    cout <<"(" << i++ << ") Utilizzo Enqueue:   ";
    (tipo == 0 ?  v3.Enqueue(distxI(generator)) : v3.Enqueue(distxD(generator)));

    cout <<std::endl <<"(" << i++ << ") Stampo QueueLst:   ";
    v3.Map([](const Data& x){cout << x << " ";});

}

//*****************************************************************************************


void testQueueLst(lasd::QueueLst<std::string>& v1){
    int i = 0;
    cout <<"(" << i++ << ") Creazione di uno QueueLst di stringhe " << endl;

    std::default_random_engine generator(std::random_device{}());

    cout <<"(" << i++ << ") Stampa del lo QueueLst:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Cambio valore in front" << endl;
    v1.Front() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Cambio valore in back" << endl;
    v1.Back() = GenerateRandomString(3);

    cout <<"(" << i++ << ") Stampa Front:  ";
    cout << v1.Front() << endl;

    cout << "(" << i++ << ") Stampa Back:  ";
    cout << v1.Back() << endl;

    cout <<"(" << i++ << ") Stampa del vettore:   ";
    v1.Map([](const std::string& x){cout << x << " ";});

    cout << endl <<"(" << i++ << ") Stampa dello QueueLst con indice 3:   ";
    cout << v1[3] << endl;

    cout <<"(" << i++ << ") Stampa dello QueueLst con indice 5:   ";
    cout << v1[5] << endl;

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") << endl;

    cout <<"(" << i++ << ") Lunghezza:   ";
    cout << v1.Size() << endl;

    cout <<"(" << i++ << ") Pulizia" << endl;
    v1.Clear();

    cout <<"(" << i++ << ") Vuoto?  ";
    cout << (v1.Empty() == 0 ? "No" : "Si") ;

    cout << endl <<"(" << i++ << ") Nuovo QueueLst con copy costructor" << endl;
    lasd::QueueLst<std::string> v2(v1);

    cout <<"(" << i++ << ") I due QueueLst sono uguali?   ";
    cout << (v1 == v2 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo QueueLst con list" << endl;
    lasd::List<std::string> l;
    for(int j = 0; j < 5; j++){
        l.InsertAtFront(GenerateRandomString(3));
    }
    lasd::QueueLst<std::string> vN(l);

    cout <<"(" << i++ << ") Stampa del nuovo QueueLst:   ";
    vN.Map([](const std::string& x){cout << x << " ";});


    cout << std::endl <<"(" << i++ << ") Nuovo QueueLst con move costructor" << endl;
    lasd::QueueLst<std::string> v3(std::move(vN));

    cout <<"(" << i++ << ") I due QueueLst sono uguali?   ";
    cout << (vN == v3 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Nuovo QueueLst con copy assignment" << endl;
    lasd::QueueLst<std::string> v4 = v2;

    cout <<"(" << i++ << ") I due QueueLst sono uguali?   ";
    cout << (v2 == v4 ? "Si" : "No") << endl;

    cout <<"(" << i++ << ") Utilizzo operatore Fold:   ";
    std::string sum = "";
    v3.Fold([](const std::string& x, void* y){*(std::string*)y += x;}, &sum);
    cout << sum << endl;

    cout <<"(" << i++ << ") Stampo Head:   ";
    cout << v3.Head() << endl;

    cout <<"(" << i++ << ") Utilizzo Dequeue   " << endl;
    v3.Dequeue();

    cout <<"(" << i++ << ") Stampo HeadNDequeue:   ";
    cout << v3.HeadNDequeue() << endl;

    cout <<"(" << i++ << ") Utilizzo Enqueue:   ";
    v3.Enqueue(GenerateRandomString(3));

    cout <<std::endl <<"(" << i++ << ") Stampo QueueLst:   ";
    v3.Map([](const std::string& x){cout << x << " ";});

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


    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

  lasd::List<int> l1;
  lasd::List<double> l2;
  lasd::Vector<int> v3(7);
    for(int i = 0; i < 7; i++){
        v3[i] = distxI(generator);
    }
  lasd::Vector<double> v4(7);
    for(int i = 0; i < 7; i++){
        v4[i] = distxD(generator);
    }
  lasd::Vector<std::string> v5(7);
    for(int i = 0; i < 7; i++){
        v5[i] = GenerateRandomString(3);
    }


    cout << endl << "--- Liste di interi" << endl << endl;
    testList(0, l1, v3);

    cout << endl << "--- Liste di double" << endl << endl;
    testList(1, l2, v4);

    cout << endl << "--- Liste di stringhe" << endl << endl;
    testList(v5);

  lasd::StackVec<int> sv1(v3);
  lasd::StackVec<double> sv2(v4);
  lasd::StackVec<std::string> sv3(v5);
    cout << endl << "--- StackVec di interi" << endl << endl;
    testStackVec(0, sv1);

    cout << endl << "--- StackVec di double" << endl << endl;
    testStackVec(1, sv2);

    cout << endl << "--- StackVec di stringhe" << endl << endl;
    testStackVec(sv3);

  lasd::StackLst<int> sl1(v3);
  lasd::StackLst<double> sl2(v4);
  lasd::StackLst<std::string> sl3(v5);

    cout << endl << "--- StackList di interi" << endl << endl;
    testStackList(0, sl1);

    cout << endl << "--- StackList di double" << endl << endl;
    testStackList(1, sl2);

    cout << endl << "--- StackList di stringhe" << endl << endl;
    testStackList(sl3);

  lasd::QueueVec<int> qv1(v3);
  lasd::QueueVec<double> qv2(v4);
  lasd::QueueVec<std::string> qv3(v5);

    cout << endl << "--- QueueVec di interi" << endl << endl;
    testQueueVec(0, qv1);

    cout << endl << "--- QueueVec di double" << endl << endl;
    testQueueVec(1, qv2);

    cout << endl << "--- QueueVec di stringhe" << endl << endl;
    testQueueVec(qv3);

  lasd::QueueLst<int> ql1(v3);
  lasd::QueueLst<double> ql2(v4);
  lasd::QueueLst<std::string> ql3(v5);

    cout << endl << "--- QueueLst di interi" << endl << endl;
    testQueueLst(0, ql1);

    cout << endl << "--- QueueLst di double" << endl << endl;
    testQueueLst(1, ql2);

    cout << endl << "--- QueueLst di stringhe" << endl << endl;
    testQueueLst(ql3);
}

/* ************************************************************************** */


