#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


struct Book{
    char* title;
    char* auth;
    int pages;
};

struct RecordSet{
    Book* record;
    int len;
    int cap;
};

RecordSet init(){
    const int base_capacity = 10;
    RecordSet new_set = {.cap = base_capacity, .len = 0, .record = new Book[base_capacity] };
    return new_set;
}

void drop(RecordSet set){
    for(int i=0; i<set.len; i++){
        delete[] set.record[i].auth;
        delete[] set.record[i].title;
    }
    delete[] set.record;
    return; 
}

void copy(RecordSet source, RecordSet& dest){
    for(int i=0; i<source.len; i++){
        strcpy(dest.record[i].auth, source.record[i].auth);
        strcpy(dest.record[i].title, source.record[i].title);
        dest.record[i].pages = source.record[i].pages;
    }
}

void extends( RecordSet& set ){
    RecordSet new_set = {.cap = set.cap*2, .len = set.len, .record = new Book[set.cap*2]};
    copy(set, new_set);
    delete[] set.record;
    set.len = new_set.len;
    set.cap = new_set.cap;
    copy(new_set, set);
}

bool isEmpty(RecordSet set){
    return set.len == 0;
}

int search( RecordSet set, char* title, char* auth){
    if( isEmpty(set) ) return -1;
    for(int i=0; i<set.len; i++){
        if( strcmp( set.record[i].title, title) == 0 && strcmp( set.record[i].auth, auth) == 0 ) return i;
    }
    return -1;
}

int push(RecordSet set, char* title, char* auth, int pages){
    if( set.len == set.cap ) extends(set);

    if( search(set, title, auth) == -1 ){
        set.record[set.len].title = new char[strlen(title)+1];
        set.record[set.len].auth = new char[strlen(auth)+1];
        strcpy(set.record[set.len].title, title);
        strcpy(set.record[set.len].auth, auth);
        set.record[set.len ].pages = pages;
        set.len ++;

        return set.len-1;
    }else{
        return -1;
    }

}

int modify(RecordSet set, char* title, char* auth, int pages){
    int index = search(set, title, auth);
    if(  index == -1 ) return -1;

    set.record[index].pages = pages;
    return index;
}

int remove(RecordSet set, char* title, char* auth){
    int index = search(set, title, auth);
    if(index == -1) return -1;

    for(int i=index; i<set.len-1; i++){
        strcpy( set.record[i].title, set.record[i+1].title );
        strcpy( set.record[i].auth, set.record[i+1].auth);
        set.record[i].pages = set.record[i+1].pages;
    }

    set.len-=1;

    return index;
}


void pagesSort(RecordSet& set){
    bool ripeti = true;
    while(ripeti ){
        ripeti = false;
        for(int i=0; i<set.len; i++){
            if(set.record[i].pages > set.record[i+1].pages ){
                Book temp = set.record[i];
                set.record[i] = set.record[i+1];
                set.record[i+1] = temp;
                ripeti = true;
            }
        }
    }
}

int load(char* filename ){
    ifstream file( filename);
    if( !file ) return -1;
    int len = 0;
    char* title = nullptr;
    char* auth = nullptr;
    int pages = 0;

    file >> len;

    RecordSet new_set = init();
    new_set.len = len;
    for(int i=0; i<len; i++){
        file >> title >> auth >> pages;
        push(new_set, title, auth, pages);
    }

    file.close();
    return len;
}

int save(RecordSet set, char* filename ){
    ofstream file(filename);
    if(!file ) return -1;
    file<<set.len<<endl;
    for(int i=0; i<set.len; i++){
        file<<set.record[i].title<< " "<<set.record[i].auth<<" "<<set.record[i].pages<<endl;
    }
    file.close();

    return set.len;
}

int main( ){
    int totalScore = 0;
    // Test 1: Inizializzazione e inserimento
    RecordSet mySet = init();
    cout<<"Ciao"<<endl;
    totalScore += 2; // Punteggio iniziale per l'inizializzazione
    if (push(mySet, "Libro1", "Autore1", 100) != -1) {
        totalScore += 5; // Punteggio per l'inserimento
    }
    if (push(mySet, "Libro2", "Autore2", 150) != -1) {
        totalScore += 5; // Punteggio per l'inserimento
    }
    if (push(mySet, "Libro3", "Autore3", 120) != -1) {
        totalScore += 5; // Punteggio per l'inserimento
    }

    // Test 2: Modifica del numero di pagine
    if (modify(mySet, "Libro2", "Autore2", 200) != -1) {
        totalScore += 5; // Punteggio per la modifica
    }

    // Test 3: Rimozione di un libro
    if (remove(mySet, "Libro1", "Autore1") != -1) {
        totalScore += 5; // Punteggio per la rimozione
    }

    // Test 4: Ordinamento per numero di pagine
    pagesSort(mySet);
    if (mySet.record[0].pages <= mySet.record[1].pages && mySet.record[1].pages <= mySet.record[2].pages) {
        totalScore += 5; // Punteggio per l'ordinamento
    }

    // Test 5: Salvataggio e caricamento da file
    if (save(mySet, "output.txt") != -1) {
        totalScore += 5; // Punteggio per il salvataggio
    }

    RecordSet loadedSet = init();
    if (load("output.txt") != -1) {
        totalScore += 5; // Punteggio per il caricamento
    }

    // Stampa il punteggio totale
    cout << "Punteggio totale: " << totalScore << " / X" << endl;

    // Dealloca la memoria
    drop(mySet);
    drop(loadedSet);

    return 0;
}