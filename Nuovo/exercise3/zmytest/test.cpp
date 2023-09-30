#include "test.hpp"
#include <iostream>
#include <iomanip>
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

/* ************************************************************************** */
/* **************************** TEST HT OPN********************************** */

template <typename Data>
void testHTOpn(int tipo, lasd::Vector<Data>& vec){
    int i = 0;

try{
    cout << "(" << i++ << ") Creo una HashTableOpnAdr di ";
    if(tipo == 0 ? cout << "interi" : (tipo == 1 ? cout << "double" : cout << "string"));
    cout << " di grandezza 40" << endl;
    lasd::HashTableOpnAdr<Data> ht(40);

    for(int j = 0; j < vec.Size(); j++){
        cout << "(" << i++ << ") Inserisco nell'hashtable il valore " << vec[j] << endl;
        ht.Insert(vec[j]);
    }

    for(int j = 0; j < 10; j++){
        cout << "(" << i++ << ") Il valore " << vec[j] <<" esiste?   ";
        ((ht.Exists(vec[j])) == true ? cout << "Sì" : cout << "No") << endl;
    }

    for(int j = 0; j < 5; j++){
        cout << "(" << i++ << ") Rimuovo il valore " << vec[j] << endl;
        ht.Remove(vec[j]);
    }

    for(int j = 0; j < 5; j++){
        cout << "(" << i++ << ") Il valore " << vec[j] <<" esiste?   ";
        ((ht.Exists(vec[j])) == true ? cout << "Sì" : cout << "No") << endl;
    }

    cout << "(" << i++ << ") Creo una copia dell'hashtable" << endl;
    lasd::HashTableOpnAdr<Data> copia(ht);

    cout << "(" << i++ << ") I due Hashtable sono uguali?   ";
    ((ht == copia) == true ? cout << "Sì" : cout << "No") << endl;

    for(int j = 0; j < 5; j++){
        cout << "(" << i++ << ") Inserisco il valore " << vec[j] << " nella copia" << endl;
        ht.Insert(vec[j]);
    } 

    cout << "(" << i++ << ") I due Hashtable sono uguali?   ";
    ((ht == copia) == true ? cout << "Sì" : cout << "No") << endl;

    cout << "(" << i++ << ") Creo un nuovo hashtable come move della copia" << endl;
    lasd::HashTableOpnAdr<Data> move(std::move(copia));

    cout << "(" << i++ << ") I due Hashtable sono uguali?   ";
    ((ht == move) == true ? cout << "Sì" : cout << "No") << endl;

    cout << "(" << i++ << ") Svuoto ht creato con move" << endl;
    move.Clear();

    cout << "(" << i++ << ") Size di move:   " << move.Size() << endl;

    cout << "(" << i++ << ") Size di copia:   " << copia.Size() << endl;  

    cout << "(" << i++ << ") Size di ht:   " << ht.Size() << endl;

    cout << "(" << i++ << ") I due Hashtable (copia e move) sono uguali?   ";
    ((move == copia) == true ? cout << "Sì" : cout << "No") << endl;

}catch(...){
    cout << endl << "Gli elementi generati randomicamente non sono sufficienti per testare tutte le funzioni" << endl
        << "Riprovare a eseguire il test" << endl;
}
}

/* ************************************************************************** */
/* **************************** TEST HT CLS********************************** */

template <typename Data>
void testHTCls(int tipo, lasd::Vector<Data>& vec){
    int i = 0;

try{
    cout << "(" << i++ << ") Creo una HashTableClsAdr di grandezza 40" << endl;
    lasd::HashTableClsAdr<Data> ht(40);

    for(int j = 0; j < vec.Size(); j++){
        cout << "(" << i++ << ") Inserisco nell'hashtable il valore " << vec[j] << endl;
        ht.Insert(vec[j]);
    }

    for(int j = 0; j < 10; j++){
        cout << "(" << i++ << ") Il valore " << vec[j] <<" esiste?   ";
        ((ht.Exists(vec[j])) == true ? cout << "Sì" : cout << "No") << endl;
    }

    for(int j = 0; j < 5; j++){
        cout << "(" << i++ << ") Rimuovo il valore " << vec[j] << endl;
        ht.Remove(vec[j]);
    }

    for(int j = 0; j < 5; j++){
        cout << "(" << i++ << ") Il valore " << vec[j] <<" esiste?   ";
        ((ht.Exists(vec[j])) == true ? cout << "Sì" : cout << "No") << endl;
    }

    cout << "(" << i++ << ") Creo una copia dell'hashtable" << endl;
    lasd::HashTableClsAdr<Data> copia(ht);

    cout << "(" << i++ << ") I due Hashtable sono uguali?   ";
    ((ht == copia) == true ? cout << "Sì" : cout << "No") << endl;

    for(int j = 0; j < 5; j++){
        cout << "(" << i++ << ") Inserisco il valore " << vec[j] << " nella copia" << endl;
        ht.Insert(vec[j]);
    } 

    cout << "(" << i++ << ") I due Hashtable sono uguali?   ";
    ((ht == copia) == true ? cout << "Sì" : cout << "No") << endl;

    cout << "(" << i++ << ") Creo un nuovo hashtable come move della copia" << endl;
    lasd::HashTableClsAdr<Data> move(std::move(copia));

    cout << "(" << i++ << ") I due Hashtable sono uguali?   ";
    ((ht == move) == true ? cout << "Sì" : cout << "No") << endl;

    cout << "(" << i++ << ") Svuoto ht creato con move" << endl;
    move.Clear();

    cout << "(" << i++ << ") Size di move:   " << move.Size() << endl;

    cout << "(" << i++ << ") Size di copia:   " << copia.Size() << endl;  

    cout << "(" << i++ << ") Size di ht:   " << ht.Size() << endl;

    cout << "(" << i++ << ") I due Hashtable (copia e move) sono uguali?   ";
    ((move == copia) == true ? cout << "Sì" : cout << "No") << endl;

}catch(...){
    cout << endl << "Gli elementi generati randomicamente non sono sufficienti per testare tutte le funzioni" << endl
        << "Riprovare a eseguire il test" << endl;
}
}
/* ************************************************************************** */

void mytest(){    
  cout << endl << "~*~#~*~ Test dello studente ~*~#~*~ " << endl;
  cout << endl << "~*~#~*~ Cozzolino Francesco ~*~#~*~ " << endl;
  cout << endl << "~*~#~*~ N86002831 ~*~#~*~ " << endl << endl << endl;

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

    lasd::Vector<int> vettore(20), copVec(10);
    lasd::Vector<double> vettore2(20), copVec2(10);
    lasd::Vector<std::string> vettore3(20), copVec3(10);

    for(int i = 0; i < 20; i++){
      vettore[i] = distxI(generator);
        
    // Genera un numero double con due decimali
    double randomDouble = distxD(generator);
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << randomDouble;
    vettore2[i] = std::stod(stream.str()); // Converti la stringa formattata in double
    
      vettore3[i] = GenerateRandomString(3);
    }

    cout << endl << "--- HashTableOpn di interi" << endl << endl;
    testHTOpn(0, vettore);

    cout << endl << "--- HashTableOpn di double" << endl << endl;
    testHTOpn(1, vettore2);

    cout << endl << "--- HashTableOpn di stringhe" << endl << endl;
    testHTOpn(2, vettore3);

    cout << endl << "--- HashTableCls di interi" << endl << endl;
    testHTCls(0, vettore);

    cout << endl << "--- HashTableCls di double" << endl << endl;
    testHTCls(1, vettore2);

    cout << endl << "--- HashTableCls di stringhe" << endl << endl;
    testHTCls(2, vettore3);
}

/* ************************************************************************** */