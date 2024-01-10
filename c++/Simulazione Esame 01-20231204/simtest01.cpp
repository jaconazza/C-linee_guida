// #define __SOL__
#define __TESTS__

#ifdef __SOL__
#include "simsol01.cpp"
#else
#include "simesame01.cpp"
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
  RecordSet rs = init();
  int voto_insert = 0;
  if (insert(rs, "a", 1) == 0) voto_insert += 2;
  if (insert(rs, "b", 2) == 1) voto_insert += 2;
  if (insert(rs, "b", 2) == -1) voto_insert += 1;
  cout << "Voto per insert: " << voto_insert << endl;

  // tests per search
  int voto_search = 0;
  if (search(rs, "a") == 0) voto_search += 2;
  if (search(rs, "b") == 1) voto_search += 2;
  if (search(rs, "c") == -1) voto_search += 1;
  cout << "Voto per search: " << voto_search << endl;

  // tests per update
  int voto_update = 0;
  if (update(rs, "a", 1) == 0 && rs.records[0].value == 1) voto_update += 2;
  if (update(rs, "b", 3) == 1 && rs.records[1].value == 3) voto_update += 2;
  if (update(rs, "c", 0) == -1) voto_update += 1;
  cout << "Voto per update: " << voto_update << endl;

  // tests per remove
  int voto_remove = 0;
  if (remove(rs, "a") == 0) voto_remove += 4;
  if (remove(rs, "c") == -1) voto_remove += 1;
  cout << "Voto per remove: " << voto_remove << endl;

  // tests per load and save
  RecordSet rsf = init();
  int voto_load = 0;
  if (load(rsf, "simload01.txt") == 2) voto_load += 1;
  if (rsf.size == 2) {
    if (rsf.records[0].value == 10) voto_load += 2;
    if (rsf.records[1].value == 20) voto_load += 2;
  }
  cout << "Voto per load: " << voto_load << endl;

  int voto_save = 0;
  if (save(rsf, "simsave01.txt") == 2) voto_save += 1;
  if (checkfiles("simload01.txt", "simsave01.txt")) voto_save += 4;
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
