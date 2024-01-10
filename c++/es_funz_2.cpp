#include <iostream>
using namespace std;

bool first(int value){
    cout<<"Ciao "<< value << endl; 
    bool result = value%2==0? false:true; 
    return result;  //oppure direttamente --> return value%2==0;
}

bool second(int value){
    cout<<"Salve "<< value <<endl;
    bool result = value>20? true:false;
    return result;
}

int main(void){
    int value = 0;
    cout<<"Inserisci un valore"<<endl;
    cin>> value;
    while(!second(value) || !first(value)){
        cout<<"Inserisci un altro numero"<<endl;
        cin>> value;
    }

    return 0;
}