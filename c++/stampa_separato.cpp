#include <iostream>
#include <cmath>

using namespace std;

int calcNumberOfDigits(int value){
    int number = 1;
    int div = 10;
    while(value/div!=0){
        number++;
        div*=10;
    }
    return number;
}

void print_digit(int a, bool first){
    if((!first) && (a == 0))
        return;
    print_digit(a / 10, false);
    cout << abs(a % 10);
}

int subdivide(int a, int divisore, int numberofdigits){
    if(numberofdigits>0){
        numberofdigits--;
        cout<<(a - ( a%divisore))/divisore<<" "<<subdivide((a-(a - ( a%divisore))), pow(10, numberofdigits), numberofdigits);
    }else{
        cout<<(a - ( a%divisore))/divisore<<endl;
    }
    
    return (a - ( a%divisore))/divisore;
}


int main(void){
    int digit = 0;
    int a = 0;
    int result = 0;
    int divisore = 0;

    cout<<"Insert a value"<<endl;
    cin>>a;
    a = a<0? -1*a:a;

    int numberOfDigits = calcNumberOfDigits(a);


/*
    do{
        divisore = pow(10, numberOfDigits-1);
        result = (a - ( a%divisore));
        digit = result/divisore;
        a -= result;
        cout<<digit<<" ";
        numberOfDigits--;
    }while (numberOfDigits>0);
    cout<<endl;*/

    int x = subdivide(a, pow(10, numberOfDigits-1), numberOfDigits-1);

    return 0;
}

