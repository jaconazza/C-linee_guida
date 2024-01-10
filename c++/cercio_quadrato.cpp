#include <iostream>
using namespace std;


float generate_single_point(){
    return (static_cast<float>(rand()/static_cast<float>(RAND_MAX))*2.0)-1.0;
}

bool is_in_circle( float x, float y){
    return ( ((x*x)+(y*y)) <= 1.0 );
}

/*
bool is_in_square(int x, int y){
    if( x<=2 && x>=-2 ){
        if(y<=2 && y>=2){
            return true;
        }
        return false;
    }
    return false;
}*/

int main(void){
    float x = 0;
    float y = 0;

    int tries = 0;
    int count_circle = 0;

    srand(time(NULL));

    cout <<" Tries: "<< endl;
    cin>> tries;


    for(int i=0; i<tries; i++){
        x = generate_single_point();
        y = generate_single_point();

        if(is_in_circle(x,y)) count_circle++;
        
    }


    float result = 4.0*(count_circle/static_cast<float>(tries));

    cout<<"pi: "<< result << endl;

    return 0;
}