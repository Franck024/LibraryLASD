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
    if(tipo == 0 ? cout << "interi" : (tipo == 1 ? cout << "double" : cout << "string"));

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

    cout << "(" << i++ << ")Size del primo albero: " << tree.Size() << endl;
}

/* ************************************************************************** */
/* **************************BINARYTREEVEC*********************************** */

template <typename Data>
void testBinaryTreeLnk(int tipo, lasd::Vector<Data>& vettore){
    int i = 0, sum = 0;
    double sum2 = 0;
    std::string sum3 = "";
    cout <<"(" << i++ << ") Creazione BinaryTreeLnk di " ;
    if(tipo == 0 ? cout << "interi" : (tipo == 1 ? cout << "double" : cout << "string"));

    lasd::BinaryTreeLnk<Data> tree(vettore);

    cout << endl << "(" << i++ << ")Stampa dell'albero in PreOrder: ";
    tree.PreOrderMap([](const Data& a){cout << a << " ";});

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
    lasd::BinaryTreeLnk<Data> tree2(tree);

    cout << "(" << i++ << ")Stampa dell'albero in PreOrder: ";
    tree2.PreOrderMap([](const Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")I due alberi sono uguali?   ";
    (tree == tree2 ? cout << "Si" : cout << "No") << endl;

    cout << "(" << i++ << ")Size del primo albero: " << tree.Size() << endl;
}
//*****************************************************************************************
//**************************************BST************************************************

template <typename Data>
void testBST(int tipo, lasd::Vector<Data>& vettore, lasd::List<Data>& lista){
    int i = 0, sum = 0;
    double sum2 = 0;
    std::string sum3 = "";
try{
    cout <<"(" << i++ << ") Creazione BST di " ;
    if(tipo == 0 ? cout << "interi" : (tipo == 1 ? cout << "double" : cout << "string"));

    lasd::BST<Data> bst(vettore);

    cout << endl << "(" << i++ << ")Stampa dell'albero in PreOrder: ";
    bst.PreOrderMap([](const Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")Stampa dell'albero in InOrder: ";
    bst.InOrderMap([](Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")Stampa dell'albero in Breadth: ";
    bst.BreadthMap([](Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")Stampa dell'albero in PreOrder con FoldPreOrder: ";
    if(tipo == 0){
        bst.PreOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum);
        cout << sum << endl;
        sum = 0;       
    }else if(tipo == 1){
        bst.PreOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum2);
        cout << sum2 << endl;
        sum2 = 0;
    }else{
        bst.PreOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum3);
        cout << sum3 << endl;
        sum3 = "";
    }


    cout << "(" << i++ << ")Stampa dell'albero in PreOrder con InOrderFold: ";
    if(tipo == 0){
        bst.InOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum);
        cout << sum << endl;
        sum = 0;       
    }else if(tipo == 1){
        bst.InOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum2);
        cout << sum2 << endl;
        sum2 = 0;
    }else{
        bst.InOrderFold([](const Data& a, void* b){*(Data*)b += a;}, &sum3);
        cout << sum3 << endl;
        sum3 = "";
    }

    cout << "(" << i++ << ")Stampa dell'albero in PreOrder con BreadthOrderFold: ";
     if(tipo == 0){
        bst.BreadthFold([](const Data& a, void* b){*(Data*)b += a;}, &sum);
        cout << sum << endl;
        sum = 0;       
    }else if(tipo == 1){
        bst.BreadthFold([](const Data& a, void* b){*(Data*)b += a;}, &sum2);
        cout << sum2 << endl;
        sum2 = 0;
    }else{
        bst.BreadthFold([](const Data& a, void* b){*(Data*)b += a;}, &sum3);
        cout << sum3 << endl;
        sum3 = "";
    }

    cout << "(" << i++ << ")Stampa root: " << bst.Root().Element() << endl;

    cout << "(" << i++ << ")Stampo size: " << bst.Size() << endl;

    cout << "(" << i++ << ")Root ha figli? ";
    (bst.Root().IsLeaf() ? cout << "No" : cout << "Si") << endl;

    cout <<"(" << i++ << ")Stampa figlio destro di root: ";
    cout << bst.Root().RightChild().Element() ;

    cout << endl << "(" << i++ << ")Stampa figlio sinistro di root: ";
    cout << bst.Root().LeftChild().Element() ;

    cout << endl << "(" << i++ << ")Creo nuovo albero con il copy costructor" << endl;
    lasd::BST<Data> bst2(bst);

    cout << "(" << i++ << ")Stampa dell'albero in PreOrder: ";
    bst2.PreOrderMap([](const Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")I due alberi sono uguali?   ";
    (bst == bst2 ? cout << "Si" : cout << "No") << endl;

    cout << "(" << i++ << ")Size del primo albero: " << bst.Size() << endl;

    cout << "(" << i++ << ")Stampo il min:   ";
    cout << bst.Min() << endl;

    cout << "(" << i++ << ")Stampo il max:   ";
    cout << bst.Max() << endl;

    cout << "(" << i++ << ")Rimuovo il min" << endl;
    bst.RemoveMin();

    cout << "(" << i++ << ")Stampo il min:   ";
    cout << bst.Min() << endl;

    cout << "(" << i++ << ")Rimuovo il max" << endl;
    bst.RemoveMax();

    cout << "(" << i++ << ")Stampo il max:   ";
    cout << bst.Max() << endl;

    cout << "(" << i++ << ")Utilizzio MinNRemove:   ";
    cout << bst.MinNRemove() << endl;

    cout << "(" << i++ << ")Utilizzio MaxNRemove:   ";
    cout << bst.MaxNRemove() << endl;

    cout << "(" << i++ << ")Stampo size: " << bst.Size() << endl;

    cout << "(" << i++ << ")Stampo in PreOrder:   " << endl;
    bst.PreOrderMap([](const Data& a){cout << a << " ";});

    cout << "(" << i++ << ")Inserisco 10 nuovi elementi" << endl;
    for(int j = 0; j < 10; j++){
        bst.Insert(lista[j]);
    }

    cout << "(" << i++ << ")Stampo size: " << bst.Size() << endl;

    cout << "(" << i++ << ")Stampo in PreOrder:   " << endl;
    bst.PreOrderMap([](const Data& a){cout << a << " ";});

    cout << endl << "(" << i++ << ")Stampo Predecessor di root:   ";
    cout << bst.Predecessor(bst.Root().Element()) << endl;

    cout << "(" << i++ << ")Stampo Successor di root:   ";
    cout << bst.Successor(bst.Root().Element()) << endl;

    cout << "(" << i++ << ")Utilizzo PredecessorNRemove:   ";
    cout << bst.PredecessorNRemove(bst.Root().Element()) << endl;

    cout << "(" << i++ << ")Utilizzo SuccessorNRemove:   ";
    cout << bst.SuccessorNRemove(bst.Root().Element()) << endl;

    cout << "(" << i++ << ")Stampo size: " << bst.Size() << endl;

    cout << "(" << i++ << ")Stampo in PreOrder:   " << endl;
    bst.PreOrderMap([](const Data& a){cout << a << " ";});

}catch(...){
    cout << endl << "Gli elementi generati randomicamente non sono sufficienti per testare tutte le funzioni" << endl
        << "Riprovare a eseguire il test" << endl;
}
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

    cout << endl << "--- BinaryTreeLnk di interi" << endl << endl;
    testBinaryTreeLnk(0, vettore);

    cout << endl << "--- BinaryTreeLnk di double" << endl << endl;
    testBinaryTreeLnk(1, vettore2);

    cout << endl << "--- BinaryTreeLnk di string" << endl << endl;
    testBinaryTreeLnk(2, vettore3);


    lasd::List<int> list1;
    lasd::List<double> list2;
    lasd::List<std::string> list3;
    lasd::Vector<int> vec(10);
    lasd::Vector<double> vec2(10);
    lasd::Vector<std::string> vec3(10);

    for(int i = 0; i < 10; i++){
      list1.InsertAtBack(distxI(generator));
      vec[i] = distxI(generator);
        
    // Genera un numero double con due decimali
    double randomDouble = distxD(generator);
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << randomDouble;
    list2.InsertAtBack(std::stod(stream.str())); // Converti la stringa formattata in double
    vec2[i] = std::stod(stream.str());
    
      list3.InsertAtBack(GenerateRandomString(3));
      vec3[i] = GenerateRandomString(3);
    }

    cout << endl << "--- BST di interi" << endl << endl;
    testBST(0, vec, list1);

    cout << endl << "--- BST di double" << endl << endl;
    testBST(1, vec2, list2);

    cout << endl << "--- BST di string" << endl << endl;
    testBST(2, vec3, list3);

}

/* ************************************************************************** */