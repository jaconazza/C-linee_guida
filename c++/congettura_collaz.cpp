#include <iostream>
using namespace std;

bool congettura(int x){
    cout<<x<<" ";
    if(x==1){
        return true;
    }else{
        if(x%2==0){
            cout<<"Pari"<<endl;
            return congettura(x/2);
        }else{
            cout<<"Dispari"<<endl;
            return congettura(((3*x)+1));
        }
    }
}


int main(){
    int value = 0;

    cout<<"Insert value"<<endl;
    cin>>value;
    bool result = congettura(value);
    cout<<endl;
    
    cout<<"Ritorno congettura: "<< result << endl;
    return 0;
}