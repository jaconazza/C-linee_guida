
// HEADERS ---------------------------------------------------------------------
#include <string.h>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record {
  char* name;
  int grade;
};

struct RecordSet {
  Record* records;
  int size;
};

// FUNZIONI --------------------------------------------------------------------


void printRS( RecordSet& rs){
  for(int i=0; i<rs.size; i++){
    cout<<rs.records[i].name << " "<< rs.records[i].grade<<endl;
  }
}

RecordSet init(int size) { 
  RecordSet set = {};
  set.size = size;
  set.records = new Record[size];
  for(int i=0; i<size; i++){
    set.records[i].name = nullptr;
    set.records[i].grade = -2;
  }
  return set;
}

void drop(RecordSet& rs) {
  rs.size = 0;
  delete [] rs.records;
}

int EmptySpace(RecordSet& rs ){
  for(int i=0; i<rs.size; i++){
    if(rs.records[i].grade == -2 ) return i;
  }
  return -1;
}


int search(const RecordSet& rs, const char* name) { 
  for(int i=0; i<rs.size; i++){
    if( rs.records[i].name != nullptr && strcmp(rs.records[i].name, name) == 0) return i;
  }
  return -1;
}

int insert(RecordSet& rs, const char* name, int grade) { 
  int index_empty = EmptySpace(rs);
  if(index_empty != -1){
    if( search(rs, name) == -1){
      rs.records[index_empty].name = new char[strlen(name) + 1];
      strcpy( rs.records[index_empty].name, name);
      rs.records[index_empty].grade = grade;
      return index_empty;
    }
    return -1;
  }
  return -1;
}

int update(RecordSet& rs, const char* name, int grade) { 
  int index = search(rs, name);
  if(index != -1 ){
    rs.records[index].grade = grade;
    return index;
  }
  return -1;

}

int remove(RecordSet& rs, const char* name) { 
  int index = search(rs, name);
  if(index != 0){
    delete[] rs.records[index].name;
    rs.records[index].name = nullptr;
    rs.records[index].name = new char(strlen(name) +1);
    strcpy( rs.records[index].name, name);
    rs.records[index].grade = -2;
    return index;
  }
  return -1;
}



RecordSet load(const char* filename) {  
  ifstream file(filename);
  int size = 0;
  file >> size;
  RecordSet new_set = init(size);

  int grade = 0;
  string name = "";

  for(int i=0; i<size; i++){
    
    file >> name;
    if( strcmp(name.c_str(), "CANCELLATO") == 0){
      new_set.records[i].name = nullptr;
      new_set.records[i].grade = -2;
    }else{
      new_set.records[i].name = new char[strlen(name.c_str()) +1];
      strcpy(new_set.records[i].name, name.c_str());
    }
  
    
    file >> grade;
    new_set.records[i].grade = grade;
  }
  file.close();
  return new_set;
}

int save( RecordSet& rs, const char* filename) {
  printRS(rs); 
  ofstream file(filename);
  if(!file) return -1;
  file << rs.size << endl;
  for(int i=0; i<rs.size; i++){
    file<<rs.records[i].name << " " << rs.records[i].grade << endl;
  }
  return 0;
}

#ifndef __TESTS__

int main() {
  RecordSet rs = init(3);
  int voto_insert = 0;
  if (insert(rs, "Pippo", 18) == 0) voto_insert += 2;
  if (insert(rs, "Pluto", 15) == 1) voto_insert += 1;
  if (insert(rs, "Paperino", 31) == 2) voto_insert += 1;
  if (insert(rs, "Minni", 31) == -1) voto_insert += 1;
  cout << "Voto per insert: " << voto_insert << endl;
  return 0;
}

#endif
