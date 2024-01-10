#include <iostream> 
using namespace std;

struct Changes_Sequence{
    int len;
    int capacity;
    int* sequence;
};

Changes_Sequence init(){
    return {.len = 0, .sequence = new int[0], .capacity = 0};
}

Changes_Sequence init(int cap){
    return {.len = 0, .sequence = new int[cap], .capacity = cap};
}

void set(int value, int index, Changes_Sequence& seq){
    seq.sequence[index] = value;
}

void copy(Changes_Sequence& source, Changes_Sequence& destination){
    for(int i=0; i<source.len; i++){
        destination.sequence[i] = source.sequence[i];
    }
    destination.len = source.len;
}

Changes_Sequence resize(Changes_Sequence& seq){
    Changes_Sequence new_seq = init(seq.capacity*2);
    copy(seq, new_seq);
    return new_seq;
}

int get_value(Changes_Sequence seq, int index){
    return seq.sequence[index];
}

void append(int value, Changes_Sequence& seq){
    if(seq.len == seq.capacity){
        seq = resize(seq);
    }
    seq.sequence[seq.len] = value;
    seq.len++;
}

Changes_Sequence execute_control(int& start, int delta){
    Changes_Sequence operations = init(1);
    append(start, operations);
    while(start!=0){
        if(start>0){
            start-=delta;
            delta+=1;
        }else if(start<0){
            start+=delta;
            delta-=1;
        }
        append(start, operations);
    }
    return operations;
}

Changes_Sequence execute_control(int& start, int tries, int delta){
    Changes_Sequence seq = init(tries+1);
    append(start, seq);
    for(int i=0; i<tries; i++){
        if(start>0){
            start -= delta;
        }else if (start<0)
        {
            start+=delta;
        }
        append(start, seq);
    }

    return seq;
}


void print_sequence( const Changes_Sequence & seq){
    for(int i=0; i<seq.len; i++){
        cout<<get_value(seq, i)<<" ";
    }
    cout<<endl;
}

int main(void){
    int starting_difference = 0;
    cout<<"Insert the starting difference: "<<endl;
    cin>> starting_difference;

    int delta = 0;
    do{
        cout<<"Insert delta"<<endl;
        cin>>delta;
    }while(delta<0);

    int tries = 0;
    do{
        cout<<"Insert n. of tries "<<endl;
        cin>> tries;
    }while(tries<=0);

    Changes_Sequence values = execute_control(starting_difference, delta );
    cout<<"Result: "<<endl;
    print_sequence(values);


    return 0;
}