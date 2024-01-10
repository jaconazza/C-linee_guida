#include <iostream> 
using namespace std;


const int NUM = 10;

struct Vector{
    int len;
    int buffer[NUM];
};


Vector initv(){ return {.len = 0}; }

void Push(Vector& v, int value){
    v.buffer[v.len] = value;
    v.len++;
}

int LenV(const Vector& v){ return v.len;}

int Pop(Vector&v){
    int value = v.buffer[v.len-1];
    v.buffer[v.len-1] = 0;
    v.len--;
    return value;
}

void Clear(Vector& v){ v.len = 0; } 

void Set(Vector& v, int value, int index){
    v.buffer[index] = value;
}

int Get(const Vector& v, int index){ return v.buffer[index]; }


Vector intivValues(int lenValues, int values[] ){
    Vector vet = initv();
    for(int i=0; i<lenValues; i++){
        Push(vet, values[i]);
    }

    return vet;
    //return {.len= lenValues, .buffer= values[NUM]};
}



//inizializzo l'array soltanto con i numeri positivi con initivPos
Vector initvPos(Vector& v){
    Vector pos = initv();
    for(int i=0; i<LenV(v); i++){
        if(Get(v, i) >= 0){
            Push(pos, Get(v, i));
        }
    }
    return pos;
}

void Scan(const Vector& v){
    for(int i=0; i<LenV(v); i++){
        cout<<Get(v, i)<<" "<<endl;
    }
}

int main(void){
    int array[] = { -1 , 2, -3, 4, -5, 6, -7, 8, -9};
    Vector values = intivValues( 9, array );
    //Scan(values);
    Vector positivi = initvPos(values);
    Scan(positivi);
    
    return 0;
}