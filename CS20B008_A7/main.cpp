//
//  main.cpp
//  osA7
//
//  Created by Araj on 21/10/22.
//

#include<bits/stdc++.h>
#include <chrono>
#include <fstream>
using namespace std;
//#define int long long
#define Y cout<<"YES"<<endl
#define N cout<<"NO"<<endl
#define D cout<<"DEBUG"<<endl

int diskHead;

void fcfs(int* a);
void sstf(int* a);
void scan(int* a);
void cScan(int* a);
void look(int* a);
void cLook(int* a);
int getNext(int* a,int* done);
void calculatedifference(int request[], int head, int diff[][2], int n);
int findMIN(int diff[][2], int n);
void getRandom(int* a);

/*
    Comments in the algorithm functions are for printing the seek sequence.
*/

int32_t main(){
    cout<<"Do you want to give disk head's initial position as input,Y/n: ";
    char c;
    cin>>c;
    if(c == 'n'){
        diskHead = 2000;
    }
    else{
        cout<<"Enter disk head's initial position(0-4999): ";
        int x;cin>>x;
        diskHead = x;
    }
    int a[1000];
    getRandom(a);
    cout<<"1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK\n";
    cout<<"Enter algorithm number: ";
    int opcode;cin>>opcode;
    switch (opcode) {
        case 1: fcfs(a);break;
        case 2: sstf(a);break;
        case 3: scan(a);break;
        case 4: cScan(a);break;
        case 5: look(a);break;
        case 6: cLook(a);break;
        default:break;
    }
}

void getRandom(int* a){
    set<int> s;
    int i=0;
    srand(static_cast<unsigned int>(time(nullptr)));
    while(s.size()<1000){
        int x = rand()%5000;
        if(s.find(x) == s.end()){
            a[i] = x;
            s.insert(x);
            i++;
        }
    }
    return;
}

void fcfs(int* a){
//    cout<<"-----------FCFS SCEDULING SEQUENCE-----------"<<endl;
//    cout<<diskHead<<", ";
    int ans = 0;
    int copy = diskHead;
    for(int i=0;i<1000;i++){
        ans += abs(diskHead - a[i]);
        diskHead = a[i];
//        cout<<diskHead<<", ";
    }
//    cout<<"---------------------------------------------"<<endl;
    cout<<"-----------FCFS-----------\n";
    cout<<"Total head movement: "<<ans<<endl;
    float av = ((float)ans)/1000;
    cout<<"Average head movement: "<<av<<endl;
    cout<<"--------------------------\n";
    diskHead = copy;
}

void calculatedifference(int request[], int head, int diff[][2], int n){
    int x = 0;
    for(int i = 0; i < n; i++){
        x++;
        diff[i][0] = abs(head - request[i]);
    }
}

int findMIN(int diff[][2], int n){
    int minimum = 1e9;
    int index = -1;
    int x = 0;
    for(int i = 0; i < n; i++){
        x++;
        if (minimum > diff[i][0] && !diff[i][1]){
            index = i;
            minimum = diff[i][0];
        }
    }
    return index;
}

void sstf(int request[]){
    int diff[1000][2] = {{0,0}};
    int seekseq[1001] = {0};
    int x = 0;
    int copy = diskHead;
    int ans = 0;
    for(int i = 0; i < 1000; i++){
        x++;
        seekseq[i] = diskHead;
        calculatedifference(request, diskHead, diff, 1000);
        int index = findMIN(diff, 1000);
        diff[index][1] = 1;
        ans += diff[index][0];
        diskHead = request[index];
    }
    seekseq[1000] = diskHead ;
//    cout<<"-----------SSTF SCEDULING SEQUENCE-----------"<<endl;
//    for(int i=0;i<1000;i++){
//        cout<<seekseq[i]<<", ";
//    }
//    cout<<"---------------------------------------------"<<endl;
    cout<<"-----------SSTF-----------\n";
    cout<<"Total head movement: "<<ans<<endl;
    float av = ((float)ans)/1000;
    cout<<"Average head movement: "<<av<<endl;
    cout<<"--------------------------\n";
    diskHead = copy;
}

void scan(int* a){
    int ans = 0;
    int copy = diskHead;
    // Assuming left to right initially
    sort(a,a+1000);
    int queryPresent[5000] = {0};
    for(int i=0;i<1000;i++){
        queryPresent[a[i]] = 1;
    }
    if(diskHead < a[0]){
//        cout<<diskHead<<", ";
        ans += a[999] - diskHead;
//        for(int i=0;i<1000;i++){
//            cout<<a[i]<<", ";
//        }
    }
    else if(diskHead > a[0]){
        ans += 4999 - diskHead + 4999 - a[0];
//        cout<<diskHead<<", ";
//        for(int i=0;i<1000;i++){
//            if(a[i]>=diskHead)cout<<a[i]<<", ";
//        }
//        cout<<"4999, ";
//        for(int i=999;i>=0;i--){
//            if(a[i]<diskHead){
//                cout<<a[i]<<", ";
//            }
//        }
    }
//    cout<<endl;
    cout<<"-----------SCAN-----------\n";
    cout<<"Total head movement: "<<ans<<endl;
    float av = ((float)ans)/1000;
    cout<<"Average head movement: "<<av<<endl;
    cout<<"--------------------------\n";
    diskHead = copy;
}

void cScan(int* a){
    int copy = diskHead;
    int ans = 0;
    // Assuming left to right initially
    sort(a,a+1000);
    int queryPresent[5000] = {0};
    for(int i=0;i<1000;i++){
        queryPresent[a[i]] = 1;
    }
    if(diskHead< a[0]){
        ans += a[999] - diskHead;
//        cout<<diskHead<<", ";
//        for(int i=0;i<1000;i++){
//            cout<<a[i]<<", ";
//        }
    }
    else{
        ans += 4999 - diskHead;
        ans += 4999;
        int maxD = 0;
        for(int i=0;i<diskHead;i++){
            if(queryPresent[i] == 1){
                maxD = max(maxD,i);
            }
        }
        ans += maxD;
//        cout<<diskHead<<", ";
//        for(int i=0;i<1000;i++){
//            if(a[i]>=diskHead)cout<<a[i]<<", ";
//        }
//        cout<<"4999, ";
//        cout<<"0, ";
//        for(int i=0;i<1000;i++){
//            if(a[i]<diskHead)cout<<a[i]<<", ";
//        }
    }
    cout<<"----------C-SCAN----------\n";
    cout<<"Total head movement: "<<ans<<endl;
    float av = ((float)ans)/1000;
    cout<<"Average head movement: "<<av<<endl;
    cout<<"--------------------------\n";
    diskHead = copy;
}

void look(int *a){
    int copy = diskHead;
    int ans = 0;
    // Assuming left to right initially
    sort(a,a+1000);
    int queryPresent[5000] = {0};
    for(int i=0;i<1000;i++){
        queryPresent[a[i]] = 1;
    }
    if(diskHead <= a[0]){
        ans += a[999] - diskHead;
//        cout<<diskHead<<", ";
//        for(int i=0;i<1000;i++){
//            cout<<a[i]<<", ";
//        }
    }
    else{
        if(diskHead > a[999]){
            ans += diskHead - a[0];
//            cout<<diskHead<<", ";
//            for(int i=999;i>=0;i--){
//                cout<<a[i]<<", ";
//            }
        }
        else{
            ans += a[999] - diskHead;
            ans += a[999] - a[0];
//            cout<<diskHead<<", ";
//            for(int i=0;i<1000;i++){
//                if(a[i]>=diskHead)cout<<a[i]<<", ";
//            }
//            for(int i=1000;i>=0;i--){
//                if(a[i]<diskHead)cout<<a[i]<<", ";
//            }
        }
    }
    cout<<"-----------LOOK-----------\n";
    cout<<"Total head movement: "<<ans<<endl;
    float av = ((float)ans)/1000;
    cout<<"Average head movement: "<<av<<endl;
    cout<<"--------------------------\n";
    diskHead = copy;
}

void cLook(int *a){
    int copy = diskHead;
    int ans = 0;
    // Assuming left to right initially
    sort(a,a+1000);
    int queryPresent[5000] = {0};
    for(int i=0;i<1000;i++){
        queryPresent[a[i]] = 1;
    }
    int start = a[0];
    int end = a[999];
    if(diskHead <= start){
        diskHead += a[999] - diskHead;
//        cout<<diskHead<<", ";
//        for(int i=0;i<1000;i++){
//            cout<<a[i]<<", ";
//        }
    }
    else{
        if(diskHead > end){
            ans += diskHead - start;
            ans += end - start;
//            cout<<diskHead<<", ";
//            for(int i=0;i<1000;i++){
//                cout<<a[i]<<", ";
//            }
        }
        else if(diskHead == end){
            ans += diskHead - start;
            ans += a[998];
//            cout<<diskHead<<", ";
//            for(int i=0;i<999;i++){
//                cout<<a[i]<<", ";
//            }
        }
        else{
            ans += end - diskHead;
            ans += end - start;
            int maxD = 0;
            for(int i=start;i<diskHead;i++){
                if(queryPresent[i] == 1){
                    maxD = max(i,maxD);
                }
            }
            ans += maxD - start;
//            cout<<diskHead<<", ";
//            for(int i=0;i<1000;i++){
//                if(a[i]>=diskHead)cout<<a[i]<<", ";
//            }
//            cout<<start<<", ";
//            for(int i=1;i<1000;i++){
//                if(a[i]<diskHead)cout<<a[i]<<", ";
//            }
        }
    }
    cout<<"----------C-LOOK----------\n";
    cout<<"Total head movement: "<<ans<<endl;
    float av = ((float)ans)/1000;
    cout<<"Average head movement: "<<av<<endl;
    cout<<"--------------------------\n";
    diskHead = copy;
}



