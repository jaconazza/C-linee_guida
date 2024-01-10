#include <iostream>
using namespace std;


auto superiore(int divisore, int dividendo) -> int {
    if( (divisore%dividendo)!=0 ){
        return int((divisore/dividendo)+1);
    }else{
        return int(divisore/dividendo);
    }
}

auto vicino(int divisore, int dividendo) -> int {
    int result = dividendo/divisore;
    if((dividendo%divisore)>(divisore/2)){
        return result+1;
    }else{
        return result;
    }
}

int main(){
    auto dividendo = 5, divisore = 4;

    superiore(dividendo, divisore);
    vicino(dividendo, divisore);


    return 0;
}