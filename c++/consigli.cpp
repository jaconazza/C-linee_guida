#include <iostream>
using namespace std;

int main(void){
    //volatile è la parola chiave che viene utilizzata per poter evitare lottimizzazione di tale variabile
    //ovvero la variabile viene utilizzata completamente manualmente dal programmatore (evita la distruzione automatica)
    volatile int x = 0;

    //per creare un blocco di linguaggio assembly:
    volatile asm (
        "ldr x0, [x0, #0]"
        , :: :: //registri usati
    )

    //ma è una cosa quasi completamente inutile a livello specifico ma per ottimizzare al massimo l'esecuzione del codice
    //dal compilatore. 
    //Non funzione la portabilità del programma con questa metodologia

    
    return 0;
}