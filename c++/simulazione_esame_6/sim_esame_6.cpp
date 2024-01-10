#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Package{
    int id;
    char recipient[128];
    char shippingAddress[256];
    double weight;
};

struct PackageArray{
    int cap;
    int len;
    Package* record;
};

PackageArray init(){
    const int base_cap = 10;
    return {.cap = base_cap, .len = 0, .record = new Package[base_cap]};
}

void drop(PackageArray& arr){
    delete[] arr.record;
    arr.cap = 0;
    arr.len = 0;
}

int search(const PackageArray& arr, int id){
    for(int i=0; i<arr.len; i++){
        if(arr.record[i].id == id) return i;
    }
    return -1;
}

void copy(PackageArray& new_array, const PackageArray arr){
    for(int i=0; i<arr.len; i++){
        new_array.record[i].id = arr.record[i].id;
        strcpy( new_array.record[i].recipient, arr.record[i].recipient);
        strcpy( new_array.record[i].shippingAddress, arr.record[i].shippingAddress);
        new_array.record[i].weight = arr.record[i].weight;
    }
}

void expand(PackageArray& arr){
    PackageArray new_array = {.cap = arr.cap*2, .len = arr.len, .record = new Package[arr.cap*2]};
    copy(new_array, arr);
    drop(arr);
    arr.cap = new_array.cap;
    arr.len = new_array.len;
    copy(arr, new_array);
}



int insert(PackageArray& arr, const char* recipient, const char* address, const int id, const double weight){
    if( arr.len == arr.cap ) expand(arr);
    int index = search(arr, id);
    if(index != -1 ) return -1;

    arr.record[arr.len].id = id;
    strcpy( arr.record[arr.len].recipient, recipient);
    strcpy(arr.record[arr.len].shippingAddress, address);
    arr.record[arr.len].weight = weight;
    arr.len++;

    return arr.len-=1;
}

int update(PackageArray& arr, const int id, const double weight){
    int index = search(arr, id);
    if( index == -1 ) return 0;

    arr.record[index].weight = weight;
    return index;
}

int display(const PackageArray& arr, int id){
    int index = search(arr, id);
    if(index == -1){
        cout<<"Package not found "<<endl;
        return 0;
    }

    cout<<"ID: " << arr.record[index].id << endl;
    cout<<"Recipient: " << arr.record[index].recipient << endl;
    cout<<"Shippig Address:" << arr.record[index].shippingAddress << endl;
    cout<<"Weight: "<< arr.record[index].weight << endl;

    return index;
}

void displayAll(const PackageArray& arr){
    if(arr.len == 0) cout<<"Empty lsit"<<endl;
    for(int index = 0; index<arr.len; index++){
        cout<<"ID: " << arr.record[index].id << endl;
        cout<<"Recipient: " << arr.record[index].recipient << endl;
        cout<<"Shippig Address:" << arr.record[index].shippingAddress << endl;
        cout<<"Weight: "<< arr.record[index].weight << endl;
        cout<<"---"<<endl;
    }
}

double calculateTotalWeight(const PackageArray& arr){
    double total = 0;
    for(int i=0; i<arr.len; i++){
        total+=arr.record[i].weight;
    }
    return total;
}

PackageArray load(char* filename){
    ifstream file(filename);
    if(!file ) return {.cap=0, .len=0, .record = nullptr};

    int len = 0;
    int weight = 0;
    int id = 0;
    char* recipient = new char[128]; 
    char* address = new char[256];

    file >> len;

    PackageArray arr = {.cap = len*2, .len = len, .record = new Package[len*2]};
    for(int i=0; i<len; i++){
        file>> id >> recipient >> address >> weight;
        arr.record[i].id = id;
        strcpy( arr.record[i].recipient, recipient);
        strcpy( arr.record[i].shippingAddress, address);
        arr.record[i].weight = weight;
    }
    delete[] recipient;
    delete[] address;

    file.close();

    return arr;
}

void save(const PackageArray& arr, const char* filename){
    ofstream file(filename);
    if(!file) return;

    file<<arr.len<<endl; 
    for(int i=0; i<arr.len; i++){
        file<<arr.record[i].id<<endl;
        file<<arr.record[i].recipient<<endl;
        file<<arr.record[i].shippingAddress<<endl;
        file<<arr.record[i].weight<<endl;
    }

    file.close();
    return;
}


int main(){
    
    return 0;
}