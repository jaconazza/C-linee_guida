#include <iostream>
using namespace std;



struct Node{
    int value;
    Node* ptr_next;
    Node* ptr_prev;
};



//si può anche utilizzare un for per semplificare l'iterazione sulla lista attraverso l'utilizzo di un nodo di scroll 
Node* searchFor( Node* head, int searched_value ){
    for(Node* scroll = head; scroll != head; scroll = scroll->ptr_next){
        if(scroll->value == searched_value){
            return scroll;
        }
    }
    return nullptr;
}

void add(Node* head, int new_value){
    Node* scroll = head->ptr_next;
    Node* prev = head;
    Node* add_node = new Node{.value = new_value, .ptr_next = scroll, .ptr_prev = prev};
    prev->ptr_next = add_node;
    scroll->ptr_prev = add_node;
}

void delete_node(Node* node){
    // se non è una lista vuota (ovvero con solo l'elemento sentinella)
    if(node->ptr_next != node){
        Node* prev = node->ptr_prev;
        Node* next = node->ptr_next;
        prev->ptr_next = next;
        next->ptr_prev = prev;
        delete node;
    }else{
        cout<<"Emtpy list" <<endl;
    }
    
}

Node* search( Node* head , int searched_value ){
    Node* scroll = head->ptr_next;
    while( scroll != head ){
        if(scroll->value == searched_value ){
            return scroll;
        }
    }
    return nullptr;
}

int ListLen( Node* head){
    int len = 0;
    Node* scroll = head->ptr_next;
    while(scroll != head ){
        len+=1;
        scroll = scroll->ptr_next;
    }
    
    // oppure: while(scroll->ptr_next != head) len++ scroll = scroll->ptr_next; se: Node* scroll = head;
    return len;
}

//una list aè vuota quando la testa della lista punta a se stessa con entrmbi i puntatori dati
//il primo elemento della lista (head) è solamente un elemento fittizzio che serve per avere sempre una lista non vuota


Node* init(){ //creo un nodo sulla head che punt a se stesso
    Node* head = new Node{.value = 0, .ptr_next = head, .ptr_prev = head};
    return head;
}

int main(void){
    Node* head = init();


    return 0;
}