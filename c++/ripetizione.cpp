#include <iostream>
using namespace std;


int main(void){
    int b = 0, a = 0;
    int counter = 0;
    int divisore = 10;
    int digit = 0;

    cin>>b;

    while(b<0 || b>=10){
        cin>>b;
    }

    cin>>a;
    a = a<0? -1*a:a; //oppure nel controllo utilizza il valore assoluto per togliere il segno 


    do{
        digit = a % 10; //prendo la prima cifra dell'unità. se digit == b --> counter++
        if(digit == b){counter++;}
        a /= 10; //sfrutto il fatto che siano int per poter portare la seconda cifra alle unità
    }while(a!=0);
    
    cout<<"Counter: "<< counter<< endl;


    return 0;
}