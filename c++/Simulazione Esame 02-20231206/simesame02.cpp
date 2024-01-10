// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct GameWorld {
  int* cells;
  int rows;
  int columns;
};

// FUNZIONI --------------------------------------------------------------------

/*
void print(const GameWorld& gw) {
  printf("GameWorld %d x %d\n", gw.rows, gw.columns);
  for (int i = 0; i < gw.rows; i++) {
    for (int j = 0; j < gw.columns; j++) {
      printf("%d ", get(gw, i, j));
    }
    printf("\n");
  }
  printf("\n");
}*/

void print_world( const GameWorld& gw){
  for(int i=0; i<gw.rows; i++ ){
    for(int j=0; j<gw.columns; j++){
      cout<<gw.cells[i * gw.columns + j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}



GameWorld init(int n, int m, int* cells) { 
  GameWorld new_world = { .cells = new int[n * m], .rows = n, .columns = m};
  
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if( cells == nullptr) new_world.cells[ i * new_world.columns + j] = 0;
      else new_world.cells[ i * new_world.columns + j ] = cells[ i * m + j ];
    }      
  }

  return new_world;
}

void drop(GameWorld& gw) {
  gw.columns = 0;
  gw.rows = 0;
  delete [] gw.cells;
}

int get(const GameWorld& gw, int i, int j) { 
  if( (i<0 || i>= gw.rows) || (j<0 || j >= gw.columns) ) return 0;
  else return gw.cells[ i * gw.columns + j];
}

void set(GameWorld& gw, int i, int j, int value) {
  if( (i<0 || i>= gw.rows) || (j<0 || j >= gw.columns) ) return ;
  gw.cells[i * gw.columns + j] = value;
}

int count(GameWorld& gw, int i, int j) { 
  int count = 0;

  for(int r = -1; r<=1; r++){
    for(int k = -1; k<=1; k++){
      if( r!= 0 || k!= 0)  if( get(gw, (i+r), (j+k) ) == 1 )  count++;
    }
  }

  return count;
}

GameWorld copy(const GameWorld& gw) { 
  return init(gw.rows, gw.columns, gw.cells); 
}

void step(GameWorld& gw) {
  int count_near = 0;
  GameWorld new_step = copy(gw);

  for(int i=0; i<gw.rows; i++){
    for(int j=0; j<gw.columns; j++){
      count_near = count(gw, i, j);
      if( get(gw, i, j) == 0){
        if( count_near == 3) set(new_step, i, j, 1);
      }else{
        if( count_near<2 || count_near>3 ) set(new_step, i, j, 0); 
      }
    }
  }

  drop(gw);
  gw = copy(new_step);
}

//wrapped count --> i lati sono coungiunti a destra e a sinistra
int wrapped_count( GameWorld& gw, int i, int j){
  int count = 0;

  for(int r = -1; r<=1; r++){
    for(int k = -1; k<=1; k++){
      if( j+k < 0 ){ 
        if( get(gw, (i+r), (j+k+gw.columns) ) == 1){
          count++;
        } 
      }else if( j+k >= gw.columns ){ 
        if( get(gw, (i+r), (j+k-gw.columns) ) == 1){
          count++;
        } 
      }else{ 
        if(k!=0|| r!= 0) if(get(gw, (i+r), (j+k)) == 1) count ++;
      }
    }
  }

  return count;
}


void wrapprd_step(GameWorld& gw) {
  int count_near = 0;
  GameWorld new_step = copy(gw);

  for(int i=0; i<gw.rows; i++){
    for(int j=0; j<gw.columns; j++){
      count_near = wrapped_count(gw, i, j);
      if( get(gw, i, j) == 0){
        if( count_near == 3) set(new_step, i, j, 1);
      }else{
        if( count_near<2 || count_near>3 ) set(new_step, i, j, 0); 
      }
    }
  }

  print_world(new_step);

  drop(gw);
  gw = copy(new_step);
}

GameWorld load(const char* filename) { 
  ifstream file(filename);
  if(!file) return init(0, 0, nullptr);

  int rows = 0;
  int columns = 0;
  file >> rows;
  file >> columns;

  GameWorld laod_gw = init(rows, columns, nullptr);
  int single_cell = 0;
  for(int i=0; i<rows; i++){
    for(int j=0; j<columns; j++){
      file >> single_cell;
      set(laod_gw, i, j, single_cell);
    }
  }
  return laod_gw; 
}

int save(const GameWorld& gw, const char* filename) { 
  ofstream file(filename);
  if(!file) return -1;

  file << gw.rows << " " << gw.columns << endl;
  for(int i=0; i<gw.rows; i++){
    for(int j=0; j<gw.columns; j++){
      file << gw.cells[ i* gw.columns +j] << " ";
    }
    file << endl;
  }

  return 0; 
}



#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
