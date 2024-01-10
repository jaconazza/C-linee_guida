#include <iostream>
using namespace std;

int rnd(long long int value, long int seed,  long int sum_value,  long int modular){
    return (value*seed+sum_value)%modular;
}

int rnd(long int seed){
    return rnd(43, seed, 2, 1231);
}

int main(void){
    int seed = time(NULL);

    int random = rnd(seed);
    return 0;
}