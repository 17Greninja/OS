#include<bits/stdc++.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <random>
using namespace std;

void choice2MemAllocation(int n);
void choice1MemAllocation(int n);
void inPlaceTranspose(long* mat,int n);

int selfUsage;
struct rusage usage;
long initialMemory;
long initPageFaults;

int main(){   
    selfUsage=RUSAGE_SELF;
    getrusage(selfUsage, &usage);
    initialMemory=usage.ru_maxrss;
    initPageFaults=usage.ru_majflt+usage.ru_minflt;
    srand(time(NULL));
    
    int n;
    cout << "Enter n value: ";
    cin >> n;
    cout << "Enter Choice"<<endl<<"Memory Allocated once - 1"<<endl<<"Memory Allocated each time -2"<<endl;
    int choice;
    cin >> choice;
    switch(choice){
        case 1: choice1MemAllocation(n);cout << "\n(" << initialMemory << " is the baseline memory before dynamic allocation)\n";break;
        case 2: choice2MemAllocation(n);cout << "\n(" << initialMemory << " is the baseline memory before dynamic allocation)\n";break;
        default: cout<<"Wrong choice"<<endl;
    }
}

void choice1MemAllocation(int n){   
    long **mat = new long* [5];
    for (int i = 0; i < 5;i++)mat[i] = new long[n * n];
    for (int ii = 0; ii < 5;ii++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)mat[ii][i*n+j] = rand();
        }
    }
    for (int i = 0; i < 10;i++){
        inPlaceTranspose(mat[i%5], n);
        getrusage(selfUsage, &usage);
        cout<<"memory usage: "<<initialMemory<<"+"<<usage.ru_maxrss-initialMemory<<", page_faults: "<<usage.ru_majflt+usage.ru_minflt-initPageFaults<<"\n";
    }
    return;
}

void choice2MemAllocation(int n){  
    long **mat = new long* [5];
    for (int k = 0; k < 2;k++){ 
        for (int i = 0; i < 5;i++){
            for (int j = 0; j < 5; j++)mat[j] = new long[n * n];
            for (int jj = 0; jj < 5; jj++){
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++) mat[jj][i*n+j] = rand();
                }
            }
            inPlaceTranspose(mat[i], n);
            getrusage(selfUsage, &usage);
            cout<<"memory usage: "<<initialMemory<<"+"<<usage.ru_maxrss-initialMemory<<", page_faults: "<<usage.ru_majflt+usage.ru_minflt-initPageFaults<<"\n";
        }
    }
    return;
}

void inPlaceTranspose(long* mat,int n){  
    long temp;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){   
            temp=mat[i*n+j];
            mat[i*n+j]=mat[j*n+i];
            mat[j*n+i]=temp;
        }
    }
    return;
}