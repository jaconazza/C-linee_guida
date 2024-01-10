#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


// Array dinamici monodimensionali

struct dinArray{
	int* arr;
	int size;
	int maxCapacity;
};

dinArray initDinArray(int initialCapacity) {
    dinArray dynArr;
    dynArr.arr = new int[initialCapacity];
    dynArr.size = 0;
    dynArr.maxCapacity = initialCapacity;
    return dynArr;
}

void dropArr(dinArray& arr){
	delete[] arr.arr;
	arr.arr = nullptr;
	arr.size = 0;
	arr.maxCapacity = 0;
}

int pushIntArr(dinArray& arr, int value){
	if(arr.size == arr.maxCapacity){
		arr.maxCapacity *= 2;
		int* newArr = new int[arr.maxCapacity];
		for(int i = 0; i < arr.size; i++){
			newArr[i] = arr.arr[i];
		}
		newArr[arr.size] = value;
		arr.size ++;
		delete[] arr.arr;
		arr.arr = newArr;
		return arr.size --;
	}else{
		arr.arr[arr.size] = value;
		arr.size ++;
		return arr.size - 1;
	}
}

int popIntArr(dinArray& arr){
	int value = arr.arr[arr.size - 1];
	arr.arr[arr.size - 1] = 0;
	return value;
}

int insertIntArr(dinArray& arr, int element, int position) {
    if (position < 0 || position > arr.size) { return 0;}

    if (arr.size == arr.maxCapacity) {
        int newCapacity = (arr.maxCapacity == 0) ? 10 : arr.maxCapacity * 2;
        int* tempArray = new int[newCapacity];

        for (int i = 0; i < position; i++) {
            tempArray[i] = arr.arr[i];
        }

        tempArray[position] = element;

        for (int i = position; i < arr.size; i++) {
            tempArray[i + 1] = arr.arr[i];
        }

        ++arr.size;
        arr.maxCapacity = newCapacity;

        delete[] arr.arr;
        arr.arr = tempArray;
        return 0;
    } else {
        // Sposta gli elementi in modo da fare spazio all'elemento da inserire
        for (int i = arr.size; i > position; i--) {
            arr.arr[i] = arr.arr[i - 1];
        }
        arr.arr[position] = element;
        ++arr.size;
        return 0;
    }
}

int removeIntArr(dinArray& arr, int position) {
    if (position < 0 || position >= arr.size) { return -1; }

    // Sposta gli elementi dopo la posizione specificata verso sinistra
    for (int i = position; i < arr.size - 1; i++) {
        arr.arr[i] = arr.arr[i + 1];
    }
    arr.arr[arr.size - 1] = 0;
    --arr.size;

    return 0;
}

dinArray sortIntArr(const dinArray& arrayToSort, char sortOrder) {
    dinArray sortedArray = arrayToSort;

    if (sortedArray.size <= 1) {
        return sortedArray;
    }

    for (int i = 0; i < sortedArray.size - 1; ++i) {
        for (int j = 0; j < sortedArray.size - i - 1; ++j) {
            if ((sortOrder == 'a' && sortedArray.arr[j] > sortedArray.arr[j + 1]) || (sortOrder == 'd' && sortedArray.arr[j] < sortedArray.arr[j + 1])) {
	            int temp = sortedArray.arr[j];
			    sortedArray.arr[j] = sortedArray.arr[j + 1];
			    sortedArray.arr[j + 1] = temp;
            }
        }
    }

    return sortedArray;
}

dinArray copyIntArr(const dinArray& arr){
	dinArray copiedArr = initDinArray(arr.maxCapacity);

	for(int i = 0; i < arr.size; i++){
		copiedArr.arr[i] = arr.arr[i];
	}

	return copiedArr;
}

dinArray shuffleIntArr(const dinArray& arr){
	dinArray shuffledArray = arr;
    srand(time(0)); // Inizializzo il seme per la generazione dei numeri casuali

    for (int i = shuffledArray.size - 1; i > 0; --i) {
        // Genero un indice casuale compreso tra 0 e i
        int j = rand() % (i + 1);
        
        int temp = shuffledArray.arr[i];
	    shuffledArray.arr[i] = shuffledArray.arr[j];
	    shuffledArray.arr[j] = temp;
    }

    return shuffledArray;
}

void printArr(dinArray& arr){
	cout << "[";
	for(int i = 0; i < arr.maxCapacity; i++){
		cout << arr.arr[i] << ",";
	}
	cout << "]" << endl;
}

void newstrcpy(char* &destination, const char* source){
	delete[] destination;
	destination = nullptr;

	destination = new char[strlen(source) + 1];

	for(unsigned long int i = 0; i < strlen(source) + 1; i++){
		destination[i] = source[i];
	}
}


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

RecordSet init(int size) {
  if (size == 0) return {nullptr, 0};
  RecordSet rs = {new Record[size], size};
  for (int idx = 0; idx < rs.size; idx++) {
    rs.records[idx].name = nullptr;
    rs.records[idx].grade = -2;
  }
  return rs;
}

void drop(RecordSet& rs) {
  for (int idx = 0; idx < rs.size; idx++) {
    delete[] rs.records[idx].name;
  }
  delete[] rs.records;
  rs.records = nullptr;
  rs.size = 0;
}

int insert(RecordSet& rs, const char* name, int grade) {
  for (int idx = 0; idx < rs.size; idx++) {
    if (rs.records[idx].name == nullptr) {
      rs.records[idx].name = new char[strlen(name) + 1];
      strcpy(rs.records[idx].name, name);
      rs.records[idx].grade = grade;
      return idx;
    }
  }
  return -1;
}

int search(const RecordSet& rs, const char* name) {
  for (int idx = 0; idx < rs.size; idx++) {
    if (rs.records[idx].name == nullptr) continue;
    if (strcmp(rs.records[idx].name, name) == 0) return idx;
  }
  return -1;
}

int update(RecordSet& rs, const char* name, int grade) {
  int pos = search(rs, name);
  if (pos == -1) return -1;
  rs.records[pos].grade = grade;
  return pos;
}

int remove(RecordSet& rs, const char* name) {
  int pos = search(rs, name);
  if (pos == -1) return -1;
  delete[] rs.records[pos].name;
  rs.records[pos].name = nullptr;
  rs.records[pos].grade = -2;
  return pos;
}

RecordSet load(const char* filename) {
  ifstream fs(filename);
  if (!fs) return init(0);
  int num;
  fs >> num;
  RecordSet rs = init(num);
  char buf[256];
  int grade;
  for (int idx = 0; idx < rs.size; idx++) {
    fs >> buf >> grade;
    if (strcmp(buf, "CANCELLATO") == 0) {
      rs.records[idx].name = 0;
      rs.records[idx].grade = -2;
    } else {
      rs.records[idx].name = new char[strlen(buf) + 1];
      strcpy(rs.records[idx].name, buf);
      rs.records[idx].grade = grade;
    }
  }
  return rs;
}

int save(const RecordSet& rs, const char* filename) {
  ofstream fs(filename);
  if (!fs) return -1;
  fs << rs.size << endl;
  for (int idx = 0; idx < rs.size; idx++) {
    fs << (rs.records[idx].name ? rs.records[idx].name : "CANCELLATO") << " "
       << rs.records[idx].grade << endl;
  }
  return 0;
}


// STRUTTURE DATI --------------------------------------------------------------
struct Record2 {
  char name[128];
  int value;
};

struct RecordSet2 {
  Record2* records;
  int size;
  int capacity;
};

// FUNZIONI --------------------------------------------------------------------

RecordSet2 init() {
  RecordSet2 rs;
  rs.records = nullptr;
  rs.size = 0;
  rs.capacity = 0;
  return rs;
}

void drop(RecordSet2& rs) {
  if (rs.records != nullptr) {
    delete[] rs.records;
    rs.records = nullptr;
    rs.size = 0;
    rs.capacity = 0;
  }
}

int search(RecordSet2& rs, const char* name);
int insert(RecordSet2& rs, const char* name, int value) {
  if (search(rs, name) != -1) {
    return -1;
  }
  if (rs.size == rs.capacity) {
    Record2* tmp = new Record2[rs.capacity * 2];
    for (int i = 0; i < rs.size; i++) {
      tmp[i] = rs.records[i];
    }
    delete[] rs.records;
    rs.records = tmp;
    rs.capacity *= 2;
  }
  strcpy(rs.records[rs.size].name, name);
  rs.records[rs.size].value = value;
  rs.size += 1;
  return rs.size - 1;
}

int search(RecordSet2& rs, const char* name) {
  for (int i = 0; i < rs.size; i++) {
    if (strcmp(rs.records[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

int remove(RecordSet2& rs, const char* name) {
  int pos = search(rs, name);
  if (pos == -1) {
    return -1;
  }
  for (int i = pos; i < rs.size - 1; i++) {
    rs.records[i] = rs.records[i + 1];
  }
  rs.size--;
  return pos;
}

int update(RecordSet2& rs, const char* name, int value) {
  int pos = search(rs, name);
  if (pos == -1) {
    return -1;
  }
  rs.records[pos].value = value;
  return pos;
}

int load(RecordSet2& rs, const char* filename) {
  ifstream ifs(filename);
  if (!ifs) {
    return -1;
  }

  drop(rs);
  ifs >> rs.size;
  rs.capacity = rs.size;
  rs.records = new Record2[rs.size];

  for (int i = 0; i < rs.size; i++) {
    ifs >> rs.records[i].name >> rs.records[i].value;
  }

  return rs.size;
}

int save(RecordSet2& rs, const char* filename) {
  ofstream ofs(filename);
  if (!ofs) {
    return -1;
  }

  ofs << rs.size << endl;
  for (int i = 0; i < rs.size; i++) {
    ofs << rs.records[i].name << " " << rs.records[i].value << endl;
  }

  return rs.size;
}

int c;
char* fun(const char* stringa);



int main(){
	/*
		Metodi delle stringhe:

		- strcpy(destinazione, sorgente): copia il contenuto di una stringa in un'altra senza allocarne memoria aggiuntiva. ATTENZIONE AI SEGMENTATION FAULT!
		- strncpy(destinazione, sorgente, n): copia i primi n caratteri di una stringa in un'altra senza allocarne memoria aggiuntiva.
		- strcat(destinazione, sorgente): concatena il contenuto sorgente nella destinazione.
		- strncat(destinazione, sorgente, n): stesso concetto di strcpy.
		- strcmp(stringa1, stringa2): confronta le due stringhe e ritorna 0 (uguali), n > 0 (stringa 1 > stringa 2), n < 0 (stringa 1 < stringa 2).
		  dove per maggiore si intende che il primo carattere che non matcha ha un valore maggiore nella stringa 1 e viceversa.
		- strncmp(stringa1, stringa2): stesso concetto dei precedenti.
	*/

	bool finito = false ;
	for( int i = 0 ; ! finito ; ) {
		cout<<i<<" " ;
		if (i == 2)
			finito = true ;
		cout<<i<<" " ;
		i++ ;
	}
  return 0;

}

char* fun(const char* stringa){
	int c = 1;
	int lastpos = 1;
	char* risultato = new char[strlen(stringa) + 1];
	risultato[0] = stringa[0];
	risultato[1] = '\0';
	for(unsigned int i = 1; i < strlen(stringa); i++){
		if(stringa[i] == stringa[i-1] && c < 2){
			risultato[lastpos++] = stringa[i];
			risultato[lastpos] = '\0';
			c++;
		} else if(stringa[i] != stringa[i-1]){
			c = 1;
			risultato[lastpos++] = stringa[i];
			risultato[lastpos] = '\0';
		}
	}

	char* result = new char[lastpos];
	strcpy(result, risultato);
	return result;
}