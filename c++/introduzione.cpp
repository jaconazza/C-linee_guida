#include <iostream> //Permette di poter includere all'interno del programma i principali elementi 
using namespace std; //Definisco che tutte le variabili sono sotto il namespace std


auto somma(int x, int y) -> int{ //creo una funzione somma che, passati dua parametri in int peremette di far ritornare la somma
    return (x+y);
}

int main(){  // funzione main che viene chiamata alla compilazione del programma in cpp    //per formattare: clang format
    auto x = 10; //dichiaro e inizializzo una varaibile x come 10
    cin >> x; // permette di poter prendere in input un numero da tastiera
    cout<<" Ciao Mondo "<< endl; //string litteral, endl a capo
    cout << "Valore di x: " << x << endl;


    //Consiglio: inizializza sempre, anche a 0, però a volte potrebbe generare errore a causa di valori casuali assegnati
    // alle varaibili non inizializzate
    auto y = 10, z = 15; //permette di poter dichiarare ed inizializzare più variabili dello stesso tipo in maniera consecutiva 
    cout << "Somma " << somma(x,y) << endl; 
    return 0;
}