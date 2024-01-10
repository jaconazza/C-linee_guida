// HEADERS ---------------------------------------------------------------------
#include <string.h>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record {
  char name[128];
  int value;
};

struct RecordSet {
  Record* records;
  int size;
  int capacity;

};

// FUNZIONI --------------------------------------------------------------------

RecordSet init() {
  int base_capacity = 10; 
  return {.records = new Record[base_capacity], .size = 0, .capacity = base_capacity}; 
}

void drop(RecordSet& rs) {
  rs.size = 0;
  rs.capacity = 0;
  delete[] rs.records;
  rs.records = nullptr;
}

bool isFull(RecordSet& rs){
  return rs.size == rs.capacity;
}

RecordSet extendRecord(RecordSet rs){
  RecordSet new_set = {.records = new Record[rs.capacity*2], .size = 0, .capacity = rs.capacity*2};
  for(int i=0; i<rs.size; i++){
    strcpy( new_set.records[i].name, rs.records[i].name );
    new_set.records[i].value = rs.records[i].value;
    new_set.size+=1;
  }
  delete[] rs.records;
  return new_set;
}

bool isEmpty(RecordSet& rs){
  return rs.size == 0;
}

int search(RecordSet& rs, const char* name) { 
  for(int i=0; i<rs.size; i++){
    if(strcmp(rs.records[i].name, name) == 0){
      return i;
    }
  }
  return -1; 
}



int insert(RecordSet& rs,  const char* name, int value) {
  if( isEmpty(rs) ){
    strcpy(rs.records[rs.size].name, name);
    rs.records[rs.size].value = value;
    rs.size+=1;

    return rs.size-1;
    
  }else{
    int index = search(rs, name);
    if(index != -1){
      return -1;
    }else{
      if( isFull(rs) ){
        rs = extendRecord(rs);
        /*
        auto old = rs.record;
        auto new_cap = rs.capacity * 2;
        rs.record = new Records[new_capacity];
        for(int i=0; i<rs.size; i++) rs.record[i] = old[i];
        */
      }

      strcpy(rs.records[rs.size].name, name);
      rs.records[rs.size].value = value;
      rs.size+=1;

      

      return rs.size-1;
    }
  }
}



int remove(RecordSet& rs, const char* name) { 
  int index = search(rs, name);
  if(index == -1){
    return -1;
  }else{
    for(int i=index; i<rs.size-1; i++){
      strcpy( rs.records[i].name, rs.records[i+1].name );
      rs.records[i].value = rs.records[i+1].value;
    }
    rs.size-=1;
    return index;
  }
  
}

int update(RecordSet& rs, const char* name, int value) { 
  int index = search(rs, name);
  if(index == -2){
    return -1;
  }else{
    rs.records[index].value = value;
    return index;
  }
}

void copy(RecordSet& dest, RecordSet source){
  dest.capacity = source.capacity;
  dest.size = source.size;
  delete[] dest.records;
  dest.records = new Record[source.size];
  for(int i=0; i<source.size; i++){
    strcpy( dest.records[i].name, source.records[i].name );
    dest.records[i].value = source.records[i].value;
  }
}

int load(RecordSet& rs, const char* filename) { 
  ifstream file("simload01.txt");
  if(!file){
    return -2;
  }
  int file_size = 0;
  file >>  file_size;  
  
  RecordSet new_set = init();
  int i = 0;
  string file_line;


  while( file >> file_line){
    strcpy(new_set.records[new_set.size].name, file_line.c_str());

    file >> file_line;
    int value =  stoi(file_line);

    new_set.records[new_set.size].value = value;
    new_set.size+=1;
  }

  copy(rs, new_set);

  file.close();

  return new_set.size;


}

int save(RecordSet& rs, const char* filename) { 
  ofstream file("simsave01.txt");

  if(!file ){
    return -2;
  }

  file << rs.size << endl;

  if(isEmpty(rs)){
    file.close();
    return 0;

  }else{
    for(int i=0; i<rs.size; i++){
      file<<rs.records[i].name<<" "<< rs.records[i].value<<endl;
    }
    file.close();
    return rs.size;
  }
}

#ifndef __TESTS__

int main() {
  return 0;
}

#endif
