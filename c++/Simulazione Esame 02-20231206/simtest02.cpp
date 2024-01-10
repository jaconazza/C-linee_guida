// #define __SOL__
#define __TESTS__

#ifdef __SOL__
#include "simsol02.cpp"
#else
#include "simesame02.cpp"
#endif

bool checkfiles(const char* filename1, const char* filename2);

int main() {
  // init non testato
  int voto_init = 2;
  cout << "Voto per init: " << voto_init << endl;

  // drop non testato
  int voto_drop = 1;
  cout << "Voto per drop: " << voto_drop << endl;

  // tests per get/set
  int cells[] = {0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
  GameWorld gw = init(4, 4, cells);
  int voto_get = 0;
  if (get(gw, 0, 2) == 1) voto_get += 1;
  if (get(gw, 2, 1) == 1) voto_get += 1;
  if (get(gw, -1, -1) == 0) voto_get += 1;
  cout << "Voto per get: " << voto_get << endl;

  // set non testato
  int voto_set = 0;
  cout << "Voto per set: " << voto_set << endl;

  // tests per count
  int voto_count = 0;
  if (count(gw, 1, 1) == 5) voto_count += 1;
  if (count(gw, 3, 3) == 1) voto_count += 1;
  cout << "Voto per count: " << voto_count << endl;

  // tests per step
  int voto_step = 0;
  step(gw);
  if (get(gw, 2, 1) == 1) voto_step += 5;
  step(gw);
  if (get(gw, 2, 3) == 1) voto_step += 5;
  step(gw);
  if (get(gw, 3, 2) == 1) voto_step += 5;
  cout << "Voto per step: " << voto_step << endl;

  // tests per load and save
  int voto_load = 0;
  GameWorld gwf = load("simload02.txt");
  if (gwf.rows == 4 && gwf.columns == 4) voto_load += 1;
  if (gwf.rows == 4 && gwf.columns == 4) {
    if (get(gwf, 0, 0) == 0) voto_load += 2;
    if (get(gwf, 2, 1) == 1) voto_load += 2;
  }
  cout << "Voto per load: " << voto_load << endl;

  step(gwf);
  int voto_save = 0;
  if (save(gwf, "simsave02.txt") != -1) voto_save += 1;
  if (checkfiles("simcheck02.txt", "simsave02.txt")) voto_save += 4;
  cout << "Voto per save: " << voto_save << endl;

  //test wrapped step


  // Voto finale
  int voto = voto_init + voto_drop + voto_get + voto_set + voto_count +
             voto_step + voto_load + voto_save;
  cout << "Voto: " << voto << endl;
  
  
  cout<<"Testing del wrapped "<<endl;
  gwf = load("simload02.txt");
  print_world(gwf);
  cout<<"Step 1"<<endl;
  wrapprd_step(gwf);
  cout<<"Step 2"<<endl;
  wrapprd_step(gwf);
  cout<<"Step 3"<<endl;
  wrapprd_step(gwf);
  
  return 0;
}

#include <string>

bool checkfiles(const char* filename1, const char* filename2) {
  ifstream ifs1(filename1);
  ifstream ifs2(filename2);
  if (!ifs1 || !ifs2) return false;
  string s1, s2;
  while (ifs1 >> s1) {
    if (!(ifs2 >> s2)) return false;
    if (s1 != s2) return false;
  }
  return true;
}
