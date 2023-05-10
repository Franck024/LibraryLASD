#include "test.hpp"
#include <iostream>
#include <string>
using namespace std;

template <typename Data>
void test(){
    uint struttura = 0, tipo = 0, capacita = 0;
    cout << "Cosa vuoi testare?"<< endl;
    cout << "   1. Vettore"<< endl;
    cout << "   2. Lista"<< endl;
    cout << "   3. Coda"<< endl;
    cout << "   4. Stack"<< endl;
    cout << endl; cout << endl;

    cin >> struttura;


    cout << "Inserisci il tipo"<< endl;
    cout << "   1. Interi"<< endl;
    cout << "   2. Float"<< endl;
    cout << "   3. Stringhe"<< endl;
    cout << endl; cout << endl;

    cin >> tipo;

    cout << "Inserisci la capacità della struttura"<< endl;
    cin >> capacita;

    if(struttura < 1 || struttura > 4 || 
        tipo < 1 || tipo > 3 || 
        capacita < 0 || capacita > 100 )
        throw "Qualche valore inserito non è corretto";
    
    switch (struttura)
    {
    case 1:
        // if(tipo == 1)
        //     lasd::Vector<int> v(capacita);
        // if(tipo == 2)
        //     lasd::Vector<float> v(capacita);
        // if(tipo == 3)
        //     lasd::Vector<string> v(capacita);
        lasd::Vector<Data> v(capacita);
        testVector(v);
        break;
    case 2:
//        testList();
        break;
    case 3: 
 //       testQueue();
        break;
    case 4:
  //      testStack();
    
    default:
        break;
    }

}

template <typename Data>
void testVector(lasd::Vector<Data> &vec){
    int choose = 0;
    do {
        cout << "Scegli una opzione: " << endl;
        cout << "1. Popola" << endl;
        cout << "2. Vedi elemento in posizione n" << endl;
        cout << "3. Mostra Front" << endl;
        cout << "4. Mosra Back" << endl;
        cout << "5. Esistenza elemento." << endl;
        cout << "6. Ordinamento" << endl;
        cout << "7. PreOrder" << endl;
        cout << "8. PostOrder" << endl;
        cout << "9. Pulisci" <<endl;
        cout << "0. Indietro." << endl;
        cout << "------------Scelga un'opzione------------" << endl;
        cout << endl;

        cin >> choose;

        switch (choose)
        {
        case 1:
            Data val;
            for(ulong i=0; i < vec.Size(); i++){
               cout << "Inserisci valore"<< endl; 
               cin >> val;
               vec[i] = val;
            }
            StampaVec(vec);
            break;
        case 2:
            cout << "Inserisci valore"<< endl;
            ulong val2;
            cin >> val2;
            cout << vec[val2];
            StampaVec(vec);
            break;
        case 3:
            cout << vec.Front();
            StampaVec(vec);
            break;
        case 4:
            cout << vec.Back();
            StampaVec(vec);
            break;
        case 5:
            cout << "Inserisci valore"<< endl;
            Data val3 ;
            cin >> val3;
            vec.Exists(val3) ? ("L'elemento esiste") : ("L'elemento non esiste");
            StampaVec(vec);
            break;
        case 6:
            vec.Sort();
            StampaVec(vec);
            break;
        case 7:
            vec.PreOrderFold();
            StampaVec(vec);
            break;
        case 8:
            vec.PostOrderFold();
            StampaVec(vec);
            break;
        case 9:
            vec.Clear();
            break;

        default:
            break;
        }
    } while (choose != 0);
    vec.Clear();
}

template <typename Data>
void StampaVec(lasd::Vector<Data> &vec){
    for(ulong i = 0; i < vec.Size(); i++){
        cout << vec[i] << " ";
    }
}