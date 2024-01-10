// #define __SOL__
#define __TESTS__

#ifdef __SOL__
#include "simsol03.cpp"
#else
#include "simesame03.cpp"
#endif

bool checkfiles(const char* filename1, const char* filename2);

int main() {
  // init non testato
  int voto_init = 2;
  cout << "Voto per init: " << voto_init << endl;

  // drop non testato
  int voto_drop = 1;
  cout << "Voto per drop: " << voto_drop << endl;


  // tests per insert
  RecordSet rs = init(3);
  int voto_insert = 0;
  if (insert(rs, "Pippo", 18) == 0) voto_insert += 2;
  if (insert(rs, "Pluto", 15) == 1) voto_insert += 1;
  if (insert(rs, "Paperino", 31) == 2) voto_insert += 1;
  if (insert(rs, "Minni", 31) == -1) voto_insert += 1;
  cout << "Voto per insert: " << voto_insert << endl;

  // tests per search
  int voto_search = 0;
  if (search(rs, "Pippo") == 0) voto_search += 2;
  if (search(rs, "Paperino") == 2) voto_search += 2;
  if (search(rs, "Minni") == -1) voto_search += 1;
  cout << "Voto per search: " << voto_search << endl;

  // tests per update
  int voto_update = 0;
  if (update(rs, "Pippo", 31) == 0 && rs.records[0].grade == 31)
    voto_update += 2;
  if (update(rs, "Paperino", 18) == 2 && rs.records[2].grade == 18)
    voto_update += 2;
  if (update(rs, "Minni", 0) == -1) voto_update += 1;
  cout << "Voto per update: " << voto_update << endl;

  // tests per remove
  int voto_remove = 0;
  if (remove(rs, "Pluto") == 1) voto_remove += 2;
  if (insert(rs, "Paperone", 31) == 1) voto_remove += 2;
  if (remove(rs, "Minni") == -1) voto_remove += 1;
  cout << "Voto per remove: " << voto_remove << endl;

  // tests per load and save
  int voto_load = 0;
  RecordSet rsf = load("simload03.txt");
  if (rsf.size == 4) voto_load += 1;
  if (rsf.size == 4) {
    if (rsf.records[0].grade == 18) voto_load += 2;
    if (rsf.records[2].name == nullptr) voto_load += 2;
  }
  cout << "Voto per load: " << voto_load << endl;

  int voto_save = 0;
  if (save(rsf, "cartella_inesistente_8716876812/simsave03.txt") == -1)
    voto_save += 1;
  save(rsf, "simsave03.txt");
  if (checkfiles("simload03.txt", "simsave03.txt")) voto_save += 4;
  cout << "Voto per save: " << voto_save << endl;

  // Voto finale
  int voto = voto_init + voto_drop + voto_insert + voto_search + voto_update +
             voto_remove + voto_load + voto_save;
  cout << "Voto: " << voto << endl;
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
