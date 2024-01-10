#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


const int MAX_NUM_GRADES = 3;

struct Student{
    char name[128];
    int id;
    int* grades;
    int maxGrade;
    int gradesCount;
};

struct StudentRecord{
    Student* record;
    int size;
    int cap;
};

StudentRecord init(){
    const int default_cap = 2;
    return {.cap = default_cap, .size = 0, .record = new Student[default_cap]};
}

void drop(StudentRecord& stud){
    for(int i=0; i<stud.size; i++) delete[] stud.record[i].grades;
    delete[] stud.record;
    stud.size = 0;
    stud.cap = 0;
}

bool isEmpty(StudentRecord stud){
    return stud.size == 0;
}

int search(StudentRecord stud, int id){
    if( isEmpty(stud) ) return -1;
    for(int i=0; i<stud.size; i++){
        if( id == stud.record[i].id ) return i;
    }
    return -1;
}

void copy(StudentRecord source, StudentRecord& dest){
    for(int i=0; i<source.size; i++){

        dest.record[i].id = source.record[i].id;
        strcpy( dest.record[i].name, source.record[i].name);
        dest.record[i].gradesCount = source.record[i].gradesCount;
        dest.record[i].maxGrade = source.record[i].maxGrade;

        dest.record[i].grades = new int[MAX_NUM_GRADES];
        for(int j=0; j<source.record[i].gradesCount; j++){
            dest.record[i].grades[j] = source.record[i].grades[j];
        }
    }
    return;
}

void extends(StudentRecord& stud){
    StudentRecord dest = {.size = stud.size, .cap = stud.cap*2, .record = new Student[stud.cap*2]};
    copy(stud, dest);
    drop(stud);
    stud.cap = dest.cap;
    stud.size = dest.size;
    copy(dest, stud);
}

int insert(StudentRecord stud, char* name, int id){
    if( stud.cap == stud.size ) extends(stud);
    int index = search(stud, id);

    if( index != -1) return -1;
    else{
        stud.record[stud.size].id = id;
        strcpy( stud.record[stud.size].name, name );
        stud.record[stud.size].grades = new int[MAX_NUM_GRADES];
        stud.record[stud.size].maxGrade = -1;
        stud.record[stud.size].gradesCount = 0;
        stud.size++;
        return stud.size-=1;
    }

}

void calcMax(StudentRecord& stud, int index){
    int max = -1;
    for(int i=0; i<stud.record[index].gradesCount; i++){
        if(max<stud.record[index].grades[i]){
            max = stud.record[index].grades[i];
        }
    }
    stud.record[index].maxGrade = max;
}

int addGrade(StudentRecord& stud, int grade, int id){
    int index = search(stud, id);
    if( index == -1 ) return -1;
    
    if( stud.record[index].gradesCount == MAX_NUM_GRADES ) return -2;
    else{
        stud.record[index].grades[stud.record[index].gradesCount] = grade;
        stud.record[index].gradesCount++;
        calcMax(stud, index);
        return stud.record[index].gradesCount-=1;
    }
}

double calcAvg(StudentRecord& stud, int id){
    int index = search(stud, id);
    if( index == -1 ) return -1;
    
    if( stud.record[index].gradesCount == 0) return 0;
    int sum = 0;
    for(int i=0; i<stud.record[index].gradesCount; i++){
        sum+= stud.record[index].grades[i];
    }
    return (sum/stud.record[index].gradesCount);
}

void printStud( StudentRecord stud){
    for(int i=0; i<stud.size; i++){
        cout<<"Id: "<< stud.record[i].id << endl;
        cout<<"Name: "<< stud.record[i].name <<endl;
        cout<<"Number of grades "<<stud.record[i].gradesCount << endl;
        cout<<"Grades: "<<endl;
        for(int j=0; j<stud.record[i].gradesCount; j++) cout<<stud.record[i].grades[j]<<" ";
        cout<<endl;
        cout<<"Max Grade: "<< stud.record[i].maxGrade;
    }
}

int main(){
    StudentRecord stud = init();
    char name[120] = "Jacopo";
    insert(stud, name, 1234);
    printStud(stud);
    insert(stud, name, 4321);
    printStud(stud);
    insert(stud, name, 5678);
    printStud(stud);

    return 0;
}