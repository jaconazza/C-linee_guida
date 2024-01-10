#include <iostream> 
#include <fstream>
using namespace std;

struct Sequence{
    int len;
    int* seq;
    int max; 
};

void max_value(Sequence &obj){
    int max_val = obj.seq[0];
    for(int i=1; i<obj.len; i++){
        if(max_val < obj.seq[i]) max_val = obj.seq[i];
    }
    obj.max = max_val;
}

Sequence reinizializza_valori(int number){
    Sequence obj = {.len = number, .seq = new int[number], .max=0};
    int value = 0;
    for(int i=0; i<number; i++){
        cout<<"Insert a value"<<endl;
        cin>>value;
        obj.seq[i] = value;
    }
    max_value(obj);
    return obj;
}


void create_rows(Sequence obj, int max_char){
    double sep = ( (double) obj.max ) / max_char;
    int value = 0;
    for(int i=0; i<obj.len; i++){
        value = obj.seq[i];
        cout<<"Row of "<< value <<":   ";
        while(value>=sep){
            value-=sep;
            cout<<"#";
        }
        cout<<endl;
    }
    cout<<endl;
}

void create_col(Sequence obj, int max_char, int index){
    double sep = ( (double) obj.max) / max_char;
    int num_chars = 0;
    int value = obj.seq[index];
    cout<<"Column of "<<obj.seq[index]<<": "<<endl;
    while (value>=sep){
        value-=sep;
        num_chars++;
    }
    for(int i=0; i<max_char-num_chars; i++) cout<<endl;
    for(int i=0; i<num_chars; i++) cout<<"#"<<endl;
}

/* oppure:

void create_col(Sequence obj, int max_char, int index){
    for(int i = max_char; i > 0; i--){
        if( close_approc() >= i )
        ...
    }
}
*/

Sequence create_sub_sequence(Sequence obj, int start, int end){
    Sequence new_sq = {.len = (end-start)+1, .max = 0, .seq = new int[(end-start)+1]};
    int j = 0;
    for(int i=start; i<=end; i++){
        new_sq.seq[j] = obj.seq[i];
        j++;
    }
    max_value(new_sq);
    return new_sq;
}



//da rifare 
void range_sequence(int max_char, Sequence obj, int first_index, int last_index){
    Sequence sub_sequence = create_sub_sequence(obj, first_index, last_index);
    double sep = ( (double) sub_sequence.max) / max_char;
    int num_chars = 0;
    int value = 0;

    for(int i=0; i<sub_sequence.len; i++){
        num_chars = 0;
        value = sub_sequence.seq[i];
        while(value>=sep){ 
            value-=sep;
            num_chars++;
        }
        for(int i=0; i<max_char-num_chars; i++) cout<<endl;
        for(int i=0; i<num_chars; i++) cout<<"#"<<endl;
    }

}

int main(){
    int N = 5;
    int max = 5;
    Sequence seq = reinizializza_valori(N);
    create_rows(seq, max);
    create_col(seq, max, 3);
    range_sequence(max, seq, 1, 3);

    return 0;
}