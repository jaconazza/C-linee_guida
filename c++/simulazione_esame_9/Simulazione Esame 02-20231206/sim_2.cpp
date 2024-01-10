#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct GameWorld {
  int* cells;
  int rows;
  int columns;
};



GameWorld init(int n, int m, int* cells){
    GameWorld new_world = {.rows = n, .columns = m, .cells = new int[n*m] };
    for(int i=0; i<new_world.rows; i++){
        for(int j=0; j<new_world.columns; j++){
            new_world.cells[i * new_world.columns + j] = cells[ i * n + j];
        }
    }
    return new_world;
}

void drop(GameWorld& gw){
    delete[] gw.cells;
    gw.columns = 0;
    gw.rows = 0;
}

int get(const GameWorld& gw, int i, int j){
    if( i<0 || i>=gw.rows) return 0;
    if( j<0 || j>=gw.columns ) return 0;
    return gw.cells[i*gw.columns + j];
}

void set(GameWorld& gw, int i, int j, int value){
    if( i<0 || i>=gw.rows) return ;
    if( j<0 || j>=gw.columns ) return ;
    gw.cells[i*gw.columns + j ] = value;
}

int count(GameWorld& gw, int i, int j){
    int counter = 0;
    for(int k=0; k<=2; k++){
        if( get(gw, i-1, (j-1)+k) == 1) counter++;
        if( get(gw, i, (j-1)+k) == 1 && (j-1)+k != j) counter++;
        if( get(gw, i+1, (j-1)+k) == 1) counter++;
    }
    return counter;
}

GameWorld copy(const GameWorld& gw){
    return init(gw.rows, gw.columns, gw.cells);
}

void print_world( const GameWorld& gw){
  for(int i=0; i<gw.rows; i++ ){
    for(int j=0; j<gw.columns; j++){
      cout<<gw.cells[i * gw.columns + j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}


void step(GameWorld& gw){
    GameWorld old_version = copy(gw);
    int counter = 0;
    for(int i=0; i<old_version.rows; i++){
        for(int j=0; j<old_version.columns; j++){
            counter = 0;
            counter = count(old_version, i, j);
            if(get(old_version, i, j) == 1 && (counter!=2 && counter != 3)) set(gw,i,j, 0);
            if(get(old_version, i, j) == 0 && counter==3) set(gw,i,j,1);
        }
    }
    
    print_world(gw);
}

GameWorld load(const char* filename){
    ifstream file(filename);
    if(!file) return {.rows = 0, .columns = 0, .cells = nullptr};
    int rows = 0;
    int columns = 0;
    file >> rows >> columns;

    GameWorld gw = {.rows = rows, .columns = columns, .cells = new int[rows*columns]};

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            int value = 0;
            file >> value;
            set(gw, i, j, value);
        }
    }

    file.close();

    return gw;
}

int save(const GameWorld& gw, const char* filename){
    ofstream file(filename);
    if( !file ) return -1;
    file << gw.rows << " " << gw.columns << endl;
    for(int i=0; i<gw.rows; i++){
        for(int j=0; j<gw.columns; j++){
            file << gw.cells[ gw.columns * i + j ] << " ";
        }
        file<<endl;
    }
    file.close();

    return 0;
}

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif