#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cassert>
using namespace std;


struct Dyn_arr{
    int cap;
    int size;
    int* values;
};

struct Node{
    char* name;
    int value;
    int unique_id;
    bool active_flag;
};

//RICORDA!!! OGNI VOLTA CHE C'è UN PUNTATORE VA ALLOCATO
//QUIDNI IN QUESTO CASO OGNI ALLOCAZIONE DI NODE VA ANCHE ALLOCATO IL PUNTATORE DI NAME: node.name = new char[ N ];
//SE SI PASSA UN NOME GIà INSERITO ALLORA SI PRENDE LA LUNGHEZZA DI TALE STRINGA +1 (/0 end stringa): node.name = new char[ strlen(name) +1];

struct RecordSet{
    int size;
    int capacity;
    Node* record;
};

//funzione che inizializza un recordset a nullptr
RecordSet init(){
    return {.size = 0, .capacity = 0, .record = nullptr};
}

//funzione che inizializza un recordset a una specifica capacity di base (OGNI PUNTATORE DI OGNI SINGOLO NODO DEVE ESSERE INIZIALIZZATO)
RecordSet default_init(){
    int base_cap = 10;
    RecordSet new_record_set = {.size = 0, .capacity = base_cap, .record = new Node[base_cap]};
    return new_record_set;
}

//oppure con inizializzazione diretta di ogni nodo:

RecordSet zero_init(){
    int base_cap = 10;
    RecordSet new_record_set = {.size = 0, .capacity = base_cap, .record = new Node[base_cap]};
    for(int i=0; i<base_cap; i++){
        new_record_set.record[i].name = nullptr;
        new_record_set.record[i].active_flag = false;
        new_record_set.record[i].unique_id = 0;
        new_record_set.record[i].value = 0;
    }
    return new_record_set;
}


//funzione che printa tutto
void print(const RecordSet& rs){
    for(int i=0; i<rs.size; i++){
        cout<<"Name: "<<rs.record[i].name << endl;
        cout<<"Value: "<<rs.record[i].value<<endl;
        cout<<"Id: "<<rs.record[i].unique_id<<endl;
        cout<<"Flag: "<<rs.record[i].active_flag<<endl;
        cout<<endl;
    }
}

//funzione che permette di poter inizializzare un singolo nodo
Node init_node(const char* name, const int value, const int id){
    Node new_node = {.active_flag = true, .name = new char[ strlen(name)+1 ], .value = value, .unique_id = id};
    strcpy( new_node.name, name );
    return new_node;
}

//per allocare direttamente posso anche fare: (UTILIZZO STRDUP --> ALLOCA E COPIA LA STRINGA)
//COME FARE: node.name = new int char[ strlen(name) + 1]; e subito dopo strcpy( node.name, name);

//ATTENZIONE: strdup UTILIZZA MALLCO ---> UTILIZZA FREE PER DEALLOCARE
Node create_node(const char* name, const int value, const int id){
    return {.name = strdup(name), .value = value, .unique_id = id, .active_flag = true};
}

//funzione drop del singolo nodo:
void drop_node(Node& node){
    node.active_flag = false;
    node.value = 0;
    node.unique_id = 0;
    delete[] node.name;
    node.name = nullptr;
}

//funzione drop del recordset
void drop(RecordSet& rs){
    for(int i=0; i<rs.size; i++){
        rs.record[i].active_flag = false;
        rs.record[i].unique_id = 0;
        rs.record[i].value = 0;
        delete[] rs.record[i].name;
        rs.record[i].name = nullptr;
    }
    delete[] rs.record;
    rs.size = 0;
    rs.capacity = 0;
}

//funzione drop del recordset che richiama la funzione drop del nodo:
void drop_all(RecordSet& rs){
    for(int i=0; i<rs.size; i++){
        drop_node(rs.record[i]);
    }
    delete[] rs.record;
    rs.size = 0;
    rs.capacity = 0;
}

//funzione che verifica se il recordset è vuoto o meno
bool rs_is_empty(const RecordSet& rs){
    if(rs.size == 0) return true;
    return false;
}

//funzione che cerca all'interno di un record set in base all'id: RITORNA INDEX O -1 SE NON TROVATO
int search_id(const RecordSet& rs, const int id){
    if( !rs_is_empty(rs) ){
        for(int i=0; i<rs.size; i++){
            if( rs.record[i].unique_id == id ) return i;
        }
        return -1;
    }
    return -1;
}

//funzione che cerca LA PRIMA RICORRENZA PER NOME
int search_name(const RecordSet& rs, const char* name){
    if( !rs_is_empty(rs) ){
        for(int i=0; i<rs.size; i++){
            if( strcasecmp(rs.record[i].name, name) == 0) return i;
        }
        return -1;
    }
    return -1;
}

//funzione che permette la piena deallocazione e completa copia da source a destination
void complete_copy(const RecordSet& source, RecordSet& destination){
    drop(destination);
    destination.capacity = source.capacity;
    destination.size = source.size;
    destination.record = new Node[ destination.capacity ];

    for(int i=0; i<source.size; i++){
        destination.record[i].name = new char[ strlen(source.record[i].name) + 1];
        strcpy( destination.record[i].name, source.record[i].name);
        destination.record[i].value = source.record[i].value;
        destination.record[i].unique_id = source.record[i].unique_id;
        destination.record[i].active_flag = source.record[i].active_flag;
    }
}

//funzione che copia e basta (usa solo se si è sicuri dei recordset o CON DESTINATION SOLO ALLOCATO SU RECORD E NON SUI SINGOLI) (DESTINATION PULTIO)
void simple_copy( const RecordSet& source, RecordSet& destination){
    for(int i=0; i<source.size; i++){
        destination.record[i].name = new char[strlen(source.record[i].name ) + 1];
        strcpy( destination.record[i].name, source.record[i].name);
        destination.record[i].value = source.record[i].value;
        destination.record[i].unique_id = source.record[i].unique_id;
        destination.record[i].active_flag = source.record[i].active_flag;
    }
}

//funzione copia che copia da source a destination (IL NOME VIENE RIALLOCATO COME NUOVO)
void copy( const RecordSet& source, RecordSet& destination){
    if( destination.capacity >= source.capacity ){
        if( destination.size != 0 ){
            for(int i=0; i<destination.size; i++){
                delete[] destination.record[i].name;
                destination.record[i].active_flag = false;
                destination.record[i].unique_id = 0;
                destination.record[i].value = 0;
                destination.record[i].name = nullptr;
            }
        }

        for(int i=0; i<source.size; i++){
            destination.record[i].name = new char[strlen(source.record[i].name) + 1];
            strcpy(destination.record[i].name, source.record[i].name);
            destination.record[i].value = source.record[i].value;
            destination.record[i].unique_id = source.record[i].unique_id;
            destination.record[i].active_flag = source.record[i].active_flag;
        }
    }
    return;
}

//funzione copia con redefinizione della grandezza:
void redef_copy(const RecordSet& source, RecordSet& destination){
    if( destination.capacity < source.size){
        drop(destination);
        destination.size = source.size;
        destination.capacity = source.capacity;
        destination.record = new Node[ source.capacity ];
    }

    for(int i=0; i<source.size; i++){
        destination.record[i].name = new char[ strlen( source.record[i].name ) + 1];
        strcpy( destination.record[i].name, source.record[i].name);
        destination.record[i].value = source.record[i].value;
        destination.record[i].unique_id = source.record[i].unique_id;
        destination.record[i].active_flag = source.record[i].active_flag;
    }
}

//funzione che permette di poter copiare un'array da una source ad una destination
void copy_no_realloc(const RecordSet& source, RecordSet& destination){
    if( destination.capacity >= source.capacity){
        for(int i=0; i<source.size; i++){
            destination.record[i].active_flag = source.record[i].active_flag;
            strcpy( destination.record[i].name, source.record[i].name);
            destination.record[i].value = source.record[i].value;
            destination.record[i].unique_id = source.record[i].unique_id;
        }
    }
    return;
}

//funzione che espande la capacità di un recordset
void expand( RecordSet& rs){
    RecordSet new_set = {.size = 0, .capacity = rs.capacity*2, .record = new Node[rs.capacity*2]};
    copy(rs, new_set); //va bene anche simple_copy
    new_set.size = rs.size;
    drop(rs);
    rs.capacity = new_set.capacity;
    copy(new_set, rs); //va bene anche simple_copy
    rs.size = new_set.size;
    drop(new_set);
    print(rs);
}



void expand_rs(RecordSet& rs) {
    // Creazione di un nuovo RecordSet con doppia capacità
    RecordSet new_set = {.size = 0, .capacity = rs.capacity * 2, .record = new Node[rs.capacity * 2]};

    // Copia profonda dei dati da rs a new_set
    for (int i = 0; i < rs.size; i++) {
        new_set.record[i].name = new char[strlen(rs.record[i].name) + 1];
        strcpy(new_set.record[i].name, rs.record[i].name);
        new_set.record[i].value = rs.record[i].value;
        new_set.record[i].unique_id = rs.record[i].unique_id;
        new_set.record[i].active_flag = rs.record[i].active_flag;
        new_set.size++;
    }

    // Liberazione della memoria occupata da rs
    drop(rs);

    // Aggiornamento delle informazioni di rs con quelle di new_set
    rs.capacity = new_set.capacity;
    rs.size = new_set.size;
    rs.record = new_set.record;

    // Il RecordSet new_set verrà distrutto automaticamente quando esce dallo scope
}


//funzione che inserisce un nodo all'interno del recordset
int insert(RecordSet& rs, const char* name, const int value, const int id ){
    if( rs.capacity == rs.size ) expand_rs( rs );
    int index = search_id( rs, id);
    if( index == -1 ){
        rs.record[ rs.size ].name = new char[ strlen(name) + 1 ];
        strcpy( rs.record[rs.size].name, name );
        rs.record[ rs.size ].active_flag = true;
        rs.record[ rs.size ].unique_id = id;
        rs.record[ rs.size ].value = value;
        rs.size++;

        return rs.size-1;
    }else return -1; // già esistente
}

//funzione che ritorna un sottorecord set con solo quelli con active_flag = true
RecordSet group_active( const RecordSet& rs){
    if( !rs_is_empty(rs) ){
        RecordSet active_nodes = {.capacity = rs.size, .size = 0, .record = new Node[rs.size]};
        for(int i=0; i<rs.size; i++){
            if( rs.record[i].active_flag ){
                //insert(active_nodes, rs.record[i].name, rs.record[i].value, rs.record[i].unique_id);
                active_nodes.record[i].name = new char[ strlen(rs.record[i].name ) + 1];
                strcpy( active_nodes.record[i].name , rs.record[i].name);
                active_nodes.record[i].unique_id = rs.record[i].unique_id;
                active_nodes.record[i].value = rs.record[i].value;
                active_nodes.record[i].active_flag = rs.record[i].active_flag;

                active_nodes.size++;
            }
        }
        return active_nodes;
    }
    return {.size = 0, .capacity = 0, .record = nullptr};
} 

//funzione che ritorna un array con gli indici dei nodi con un certo nome
Dyn_arr search_all_name(const RecordSet& rs, const char* name){
    if(!rs_is_empty(rs)){
        Dyn_arr indexes = {.size = 0, .cap = rs.size, .values = new int[rs.size]};
        for(int i=0; i<rs.size; i++){
            if( strcmp( rs.record[i].name, name) == 0){
                indexes.values[ indexes.size ] = i;
                indexes.size++;
            }
        }
        return indexes;
    }
    return {.size = 0, .cap = 0, .values = nullptr};  
}

//funzione che riordina in base al value
void sort_value(RecordSet& rs){
    if(!rs_is_empty(rs)){
        bool rerun = true;
        while(rerun){
            rerun = false;
            for(int i=0; i<rs.size-1; i++){
                if( rs.record[i].value > rs.record[i+1].value){
                    //oppure std::swap( rs.record[i], rs.record[i+1]);
                    Node temp = rs.record[i];
                    rs.record[i] = rs.record[i+1];
                    rs.record[i+1] = temp;
                    rerun = true;
                }
            }
        }
    }
}

//funzione che riordina in base al nome
void sort_names(RecordSet& rs){
    if(!rs_is_empty(rs)){
        bool rerun = true;
        while(rerun){
            rerun = false;
            for(int i=0; i<rs.size-1; i++){
                if( strcmp(rs.record[i].name, rs.record[i+1].name) > 0 ){
                    //oppure std::swap( rs.record[i], rs.record[i+1]);
                    Node temp = rs.record[i];
                    rs.record[i] = rs.record[i+1];
                    rs.record[i+1] = temp;
                    rerun = true;
                }
            }
        }
    }
}


//funzione che rimuove un elemento in base all'id, ritorna indice
int remove_id(RecordSet& rs, const int id){
    if(!rs_is_empty(rs)){
        int index = search_id( rs, id);
        if( index == -1 ) return -1;

        for(int i=index; i<rs.size-1; i++){
            delete[] rs.record[i].name;
            rs.record[i].name = new char[ strlen(rs.record[i].name) + 1];
            strcpy( rs.record[i].name, rs.record[i+1].name);
            rs.record[i].value = rs.record[i+1].value;
            rs.record[i].unique_id = rs.record[i+1].unique_id;
            rs.record[i].active_flag = rs.record[i+1].active_flag;
            
        }
        
        delete[] rs.record[rs.size-1].name;
        rs.record[rs.size-1].name = nullptr;
        rs.record[rs.size-1].value = 0;
        rs.record[rs.size-1].unique_id = 0;
        rs.record[rs.size-1].active_flag = false;

        rs.size-=1;
        return index;
    }
    return -1;
}


//funzione che fa l'update del value di uno specifico nodo, dato l'id ( può cambiare  anche altro) ritorna l'indice
int update_id(RecordSet& rs, const int id, const int value){
    if(!rs_is_empty(rs)){
        int index = search_id(rs, id);
        if( index == -1 ) return -1;

        rs.record[ index ].value = value;
        return index;
    }
    return -1;
}


//funzione che carica da file 
RecordSet load(const char* filename){
    ifstream file(filename);
    if(!file) return {.size = 0, .capacity = 0, .record = nullptr};
    int size = 0;
    file >> size;
    RecordSet rs = {.size = size, .capacity = size*2, .record = new Node[size*2]};

    char* name = nullptr;
    int value = 0;
    int id = 0;
    bool flag = 0;

    for(int i=0; i<size; i++){
        name = new char[128];

        file >> name >> value >> id >> flag;
        rs.record[i].name = new char[strlen(name) + 1];
        strcpy(rs.record[i].name, name);
        rs.record[i].value = value;
        rs.record[i].active_flag = flag;
        rs.record[i].unique_id = id;
        delete[] name;
        name = nullptr;
    }

    return rs;
}

//load completo con anche controlli di ciò che è definito su file
RecordSet complete_load(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return {.size = 0, .capacity = 0, .record = nullptr};
    }

    int size = 0;
    file >> size;
    if (size <= 0) {
        return {.size = 0, .capacity = 0, .record = nullptr};
    }

    RecordSet rs = {.size = size, .capacity = size * 2, .record = new Node[size * 2]};

    char* name = nullptr;
    int value = 0;
    int id = 0;
    bool flag = 0;

    for (int i = 0; i < size; i++) {
        name = new char[128];

        if (!(file >> name >> value >> id >> flag)) {
            // Deallocazione della memoria prima di uscire
            delete[] name;
            for (int j = 0; j < i; j++) {
                delete[] rs.record[j].name;
            }
            delete[] rs.record;
            return {.size = 0, .capacity = 0, .record = nullptr};
        }

        rs.record[i].name = new char[strlen(name) + 1];
        strcpy(rs.record[i].name, name);
        rs.record[i].value = value;
        rs.record[i].active_flag = flag;
        rs.record[i].unique_id = id;
        delete[] name;
        name = nullptr;
    }

    return rs;
}


//funzione che salva un record su file
void save(const RecordSet& rs, const char* filename){
    ofstream file(filename);
    if(!file) return;
    
    file<<rs.size<<endl;
    for(int i=0; i<rs.size; i++){
        file<< rs.record[i].name << " " << rs.record[i].value << " " << rs.record[i].unique_id << " " << rs.record[i].active_flag << endl;
    }
    file.close();
}

//funzione che salva su file, completo
void complete_save(const RecordSet& rs, const char* filename) {
    ofstream file(filename, ios::out);
    if (!file.is_open()) {
        cerr << "Errore durante l'apertura del file." << endl;
        return;
    }

    file << rs.size << endl;
    for (int i = 0; i < rs.size; i++) {
        file << rs.record[i].name << " " << rs.record[i].value << " " << rs.record[i].unique_id << " " << rs.record[i].active_flag << endl;
    }

    file.close();
}





int main(){
    RecordSet rs_init = init();
    assert(rs_init.size == 0 && rs_init.capacity == 0 && rs_init.record == nullptr);

    // Tester per la funzione di inizializzazione predefinita
    RecordSet rs_default_init = default_init();
    assert(rs_default_init.size == 0 && rs_default_init.capacity == 10 && rs_default_init.record != nullptr);

    // ... Altri tester ...

    // Tester per la funzione di ricerca per ID
    RecordSet rs_search = default_init();
    insert(rs_search, "John", 25, 1);
    insert(rs_search, "Alice", 30, 2);

    int search_result = search_id(rs_search, 1);
    assert(search_result == 0);

    search_result = search_id(rs_search, 3);
    assert(search_result == -1);

    // Tester per la funzione di inserimento
    RecordSet rs_insert = default_init();
    int index = insert(rs_insert, "Bob", 22, 3);
    assert(index == 0 && rs_insert.size == 1);

    // ... Altri tester ...

    // Tester per la funzione di salvataggio
    RecordSet rs_save = default_init();
    insert(rs_save, "Sam", 28, 4);
    save(rs_save, "test_save.txt");

    // Tester per la funzione di caricamento
    RecordSet rs_load = load("test_save.txt");
    assert(rs_load.size == 1 && rs_load.record[0].value == 28);

    // Tester per la funzione di eliminazione per ID
    RecordSet rs_remove = default_init();
    insert(rs_remove, "Charlie", 35, 5);
    insert(rs_remove, "Emily", 40, 6);

    int remove_index = remove_id(rs_remove, 5);
    assert(remove_index == 0 && rs_remove.size == 1);

    // ... Altri tester ...

    // Tester per la funzione di aggiornamento per ID
    RecordSet rs_update = default_init();
    insert(rs_update, "Tom", 50, 7);
    int update_index = update_id(rs_update, 7, 55);
    assert(update_index == 0 && rs_update.record[0].value == 55);

    // ... Altri tester ...

    // Output di un messaggio di successo
    std::cout << "Tester eseguiti con successo!" << std::endl;


    RecordSet source = {.size = 2, .capacity = 2, .record = new Node[2]};
    source.record[0] = init_node("Element1", 42, 1);
    source.record[1] = init_node("Element2", 35, 2);

    // Creare un recordset destinazione vuoto
    RecordSet destination = init();

    print(source);

    // Eseguire la copia
    complete_copy(source, destination);

    // Verificare che la copia sia stata eseguita correttamente
    assert(destination.size == 2);
    assert(search_id(destination, 1) == 0);
    assert(search_id(destination, 2) == 1);

    // Libera la memoria allocata
    drop(source);
    drop(destination);

    std::cout << "Test copy passed." << std::endl;

    RecordSet s = {.size = 0, .capacity = 1, .record = new Node[1]};
    insert(s, "Jacopo", 30, 54);
    
    insert(s, "Tobia", 30, 7);
    

    RecordSet rs = zero_init();
    insert(rs, "Alice", 25, 1);
    insert(rs, "Bob", 30, 2);
    insert(rs, "Charlie", 35, 3);

    // Capacità iniziale del RecordSet
    int initial_capacity = rs.capacity;

    // Chiamata alla funzione expand
    expand_rs(rs);

    // Verifica che la capacità sia raddoppiata
    assert(rs.capacity == initial_capacity * 2);

    // Verifica che i dati siano correttamente copiati nel nuovo RecordSet
    for (int i = 0; i < rs.size; i++) {
        assert(rs.record[i].name != nullptr);
        assert(rs.record[i].value != 0);
        assert(rs.record[i].unique_id != 0);
        assert(rs.record[i].active_flag);
    }

    // Deallocazione del RecordSet
    drop_all(rs);

    std::cout << "Test passato: expand" << std::endl;

    return 0;
}