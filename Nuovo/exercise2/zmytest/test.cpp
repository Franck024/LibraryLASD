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
/* **************************BINARYTREEVEC*********************************** */

template <typename Data>
void testBinaryTreeVec(int tipo, lasd::Vector<Data>& vettore){
    int i = 0, sum = 0;
    double sum2 = 0;
    std::string sum3 = "";
    cout <<"(" << i++ << ") Creazione BinaryTreeVec di " ;
    if(tipo == 0 ? cout << "interi" : cout << "double");

    lasd::BinaryTreeVec<Data> tree(vettore);

    cout << endl << "(" << i++ << ")Stampa dell'albero in PreOrder: ";
    tree.PreOrderMap([](Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")Stampa dell'albero in InOrder: ";
    tree.InOrderMap([](Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")Stampa dell'albero in Breadth: ";
    tree.BreadthMap([](Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")Stampa dell'albero in PreOrder con FoldPreOrder: ";
    if(tipo == 0){
        tree.PreOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum);
        cout << sum << endl;
        sum = 0;       
    }else if(tipo == 1){
        tree.PreOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum2);
        cout << sum2 << endl;
        sum2 = 0;
    }else{
        tree.PreOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum3);
        cout << sum3 << endl;
        sum3 = "";
    }


    cout << "(" << i++ << ")Stampa dell'albero in PreOrder con InOrderFold: ";
    if(tipo == 0){
        tree.InOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum);
        cout << sum << endl;
        sum = 0;       
    }else if(tipo == 1){
        tree.InOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum2);
        cout << sum2 << endl;
        sum2 = 0;
    }else{
        tree.InOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum3);
        cout << sum3 << endl;
        sum3 = "";
    }

    cout << "(" << i++ << ")Stampa dell'albero in PreOrder con BreadthOrderFold: ";
     if(tipo == 0){
        tree.BreadthFold([](const Data& a, void* b){*(Data*)b += a;}, &sum);
        cout << sum << endl;
        sum = 0;       
    }else if(tipo == 1){
        tree.BreadthFold([](const Data& a, void* b){*(Data*)b += a;}, &sum2);
        cout << sum2 << endl;
        sum2 = 0;
    }else{
        tree.BreadthFold([](const Data& a, void* b){*(Data*)b += a;}, &sum3);
        cout << sum3 << endl;
        sum3 = "";
    }

    cout << "(" << i++ << ")Stampa root: " << tree.Root().Element() << endl;

    cout << "(" << i++ << ")Stampo size: " << tree.Size() << endl;

    cout << "(" << i++ << ")Root ha figli? ";
    (tree.Root().IsLeaf() ? cout << "No" : cout << "Si") << endl;

    cout <<"(" << i++ << ")Stampa figlio destro di root: ";
    cout << tree.Root().RightChild().Element() ;

    cout << endl << "(" << i++ << ")Stampa figlio sinistro di root: ";
    cout << tree.Root().LeftChild().Element() ;

    cout << endl << "(" << i++ << ")Creo nuovo albero con il copy costructor" << endl;
    lasd::BinaryTreeVec<Data> tree2(tree);

    cout << "(" << i++ << ")Stampa dell'albero in PreOrder: ";
    tree2.PreOrderMap([](Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")I due alberi sono uguali?   ";
    (tree == tree2 ? cout << "Si" : cout << "No") << endl;

    // cout << "(" << i++ << ")Creo nuovo albero con il move costructor" << endl;
    // lasd::BinaryTreeVec<Data> tree3(std::move(tree2));

    // cout << "(" << i++ << ")Stampa dell'albero in PreOrder: ";
    // tree3.PreOrderMap([](Data& a){cout << a << " ";});

    // cout << endl << "(" << i++ << ")I due alberi sono uguali?   ";
    // (tree2 == tree3 ? cout << "Si" : cout << "No") << endl; 

    cout << "(" << i++ << ")Size del primo albero: " << tree.Size() << endl;


}

//*****************************************************************************************

void mytest(){    
  cout << endl << "~*~#~*~ Test dello studente ~*~#~*~ " << endl;
  cout << endl << "~*~#~*~ Cozzolino Francesco ~*~#~*~ " << endl;
  cout << endl << "~*~#~*~ N86002831 ~*~#~*~ " << endl << endl << endl;

    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distxI(0, 100);
    std::uniform_real_distribution<double> distxD(0.0, 100.0);

    lasd::Vector<int> vettore(5);
    lasd::Vector<double> vettore2(5);
    lasd::Vector<std::string> vettore3(5);

    for(int i = 0; i < 5; i++){
      vettore[i] = distxI(generator);
        
    // Genera un numero double con due decimali
    double randomDouble = distxD(generator);
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << randomDouble;
    vettore2[i] = std::stod(stream.str()); // Converti la stringa formattata in double
    
      vettore3[i] = GenerateRandomString(3);
    }

    cout << endl << "--- BinaryTreeVec di interi" << endl << endl;
    testBinaryTreeVec(0, vettore);

    cout << endl << "--- BinaryTreeVec di double" << endl << endl;
    testBinaryTreeVec(1, vettore2);

    cout << endl << "--- BinaryTreeVec di string" << endl << endl;
    testBinaryTreeVec(2, vettore3);

}

/* ************************************************************************** */