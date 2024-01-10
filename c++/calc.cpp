#include <iostream>
using namespace std;


auto somma(int primo, int secondo) -> int{
    return (primo+secondo);
}

auto sottrazione(int primo, int secondo) -> int{
    return(primo-secondo);
}

auto moltiplicazione(int primo, int secondo) -> int{
    return(primo*secondo);
}

auto divisione(int primo, int secondo) -> double{
    return (double(primo)/secondo);
}

auto potenza(int primo, int secondo) -> int {
    auto result = 1;
    for(int i=0; i<secondo; i++){
        result*=primo;
    }
    return result;
}

void menu(int primo, int secondo){
    auto risposta = 0;
    bool ripeti = true;
    while(ripeti){
        cout<<"1: somma"<<endl;
        cout<<"2: sottrazione"<<endl;
        cout<<"3: moltiplicazione"<<endl;
        cout<<"4: divisione"<<endl;
        cout<<"5: potenza"<<endl;
        cout<<"other:: exit"<<endl<<endl;
        cin>>risposta;

        switch (risposta)
        {
            case 1:
                cout<<"Somma:"<< somma(primo, secondo) << endl;
                break;

            case 2:
                cout<<"Sottrazione"<< sottrazione(primo, secondo) <<endl;
                break;

            case 3:
                cout<<"Moltiplicazione"<< moltiplicazione(primo, secondo)<< endl;
                break;

            case 4:
                if(secondo != 0){ cout<<"Divisione"<< divisione(primo,secondo)<<endl; }
                else{ cout<<"non si divide per 0"<<endl; }
                break;
            
            case 5:
                cout<<"Potenza"<< potenza(primo, secondo)<<endl;
                break;
        
            default:
                cout<<"exit"<<endl;
                ripeti=false;
            break;
        }
        cout<<""<<endl;
    }
}


int main(){
    auto primo = 0;
    auto secondo = 0;

    cout<<"Inserisci il primo:" <<endl;
    cin>>primo;
    cout<<"Inserisci il secondo:"<<endl;
    cin>>secondo;

    menu(primo, secondo);
    return 0;
}