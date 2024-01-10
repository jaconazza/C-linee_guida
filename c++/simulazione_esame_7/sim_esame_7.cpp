#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


struct Animal{
    char* name;
    char* species;
    int age;
    int happiness;
};

struct Zoo{
    Animal* record;
    int len;
    int cap;
};

Zoo init(){
    int base_cap = 10;
    return {.cap = base_cap, .len = 0, .record = new Animal[base_cap]};
}

void drop(Zoo& zoo){
    for(int i=0; i<zoo.len; i++){
        delete[] zoo.record[i].name;
        delete[] zoo.record[i].species;
    }
    delete[] zoo.record;
    zoo.len = 0;
    zoo.cap = 0;
}

int search(const Zoo& zoo, const char* name){
    for(int i=0; i<zoo.len; i++){
        if( strcmp(zoo.record[i].name, name) == 0) return i;
    }
    return -1;
}

void copy(const Zoo& source, Zoo& destination){
    for(int i=0; i<source.len; i++){
        strcpy(destination.record[i].name, source.record[i].name);
        strcpy(destination.record[i].species, source.record[i].species);
        destination.record[i].age = source.record[i].age;
        destination.record[i].happiness = source.record[i].happiness;
    }
}


void expand(Zoo& zoo){
    Zoo new_zoo = {.cap = zoo.cap*2, .len = zoo.len, .record = new Animal[zoo.cap*2]};
    copy(zoo, new_zoo);
    drop(zoo);
    zoo.cap = new_zoo.cap;
    zoo.len = new_zoo.len;
    copy(new_zoo, zoo);
}

int insert(Zoo& zoo, const char* name, const char* species, const int age, const int happiness){
    int index = 0;
    index = search(zoo, name);
    if( index != -1 ) return -1;

    if( zoo.len == zoo.cap ) expand(zoo);
    zoo.record[zoo.len].name = new char[strlen(name) +1 ];
    zoo.record[zoo.len].species = new char[strlen(species) +1 ];
    strcpy( zoo.record[zoo.len].name, name);
    strcpy( zoo.record[zoo.len].species, species);
    zoo.record[zoo.len].age = age;
    zoo.record[zoo.len].happiness = happiness;
    zoo.len+=1;

    return zoo.len-1;
}

int modify(Zoo& zoo, const char* name, int age){
    int index = search(zoo, name);
    if( index == -1 ) return -1;

    zoo.record[index].age = age;
    return index;
}

int increaseHappiness(Zoo& zoo, const char* name, int amount){
    int index = search(zoo, name);
    if( index == -1 ) return -1;

    zoo.record[index].happiness+=amount;
    return index;
}

int calculateTotalHappiness(const Zoo& zoo){
    int total = 0;
    for(int i=0; i<zoo.len; i++){
        total += zoo.record[i].happiness;
    }
    return total;
}

Zoo load(const char* filename){
    ifstream file(filename);
    if( !file ) return init();

    int len = 0;
    int age = 0;
    int happiness = 0;
    file >> len;

    Zoo zoo = {.cap = len*2, .len = len, .record = new Animal[len*2]};
    for(int i=0; i<len; i++){
        char* name = new char[128];
        char* species = new char[128];
        file >> name >> species >> age >> happiness;
        insert(zoo, name, species, age, happiness);

        delete[] name;
        delete[] species;
    }

    file.close();
    return zoo;
}

void save(const Zoo& zoo, const char* filename){
    ofstream file(filename);
    if( !file ) return;

    file<< zoo.len << endl;

    for(int i=0; i<zoo.len; i++){
        file<< zoo.record[i].name << " " 
            << zoo.record[i].species << " " 
            << zoo.record[i].age << " " 
            << zoo.record[i].happiness << endl;
    }

    file.close();
    return;
}


int main(){

    return 0;
}