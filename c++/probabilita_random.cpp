#include <iostream>
using namespace std;


int main(void){
    srand(time(NULL));
    int tries = 1000;
    int num = 0;
    int counter_zero = 0;
    int counter_nn = 0;

    for(int i=0; i<tries; i++){
        num = rand() % RAND_MAX;
        cout<<num<<endl;
        if(num%100 == 0) counter_zero++;
        if(num%100 == 99) counter_nn++;
    }

    cout <<"Probabilità zero: "<< (counter_zero/tries)*100 << endl;
    cout <<"Probabilità 99: "<< (counter_nn/tries)*100 << endl;

    return 0;
}