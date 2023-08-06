#include<bits/stdc++.h> 
using namespace std;
#define int long long
#define Y cout<<"YES"<<endl
#define N cout<<"NO"<<endl
#define D cout<<"DEBUG"<<endl

void displayQueue(queue<int> q){
    while(q.size()!=0){
        int u = q.front();
        cout<<u<<" ";
        q.pop();
    }
    cout<<endl;
    return;
}

int checkPresentInQueue(queue<int> q,int num){
    while(q.size()!=0){
        int u = q.front();
        if(u == num){
            return 1;
        }
        q.pop();
    }
    return 0;
}

void fifo(int* a, int n, int m){
    cout<<"FIFO"<<endl;
    queue<int> q;
    int pageFault = 0;
    for(int i=0;i<n;i++){
        int process = a[i];
        int check = checkPresentInQueue(q,a[i]);
        if(check == 1){
            cout<<"No page fault"<<endl;
            continue;
        }
        pageFault++;
        if(q.size() != m){
            q.push(a[i]);
            displayQueue(q);
            continue;
        }
        q.pop();
        q.push(a[i]);
        displayQueue(q);
    }
    cout<<"Total number of page faults = "<<pageFault<<endl;
}

void displayArray(int* b,int bSize){
    for(int i=0;i<bSize;i++)cout<<b[i]<<" ";
    cout<<endl;
}

int checkPresentInArray(int* b,int bSize,int num){
    for(int i=0;i<bSize;i++){
        if(b[i] == num)return 1;
    }
    return 0;
}

void replaceOptimal(int* a, int index,int n, int* b, int bSize){
    int dist[bSize];
    int maxDist = INT_MIN;
    for(int i=0;i<bSize;i++){
        int num = b[i];
        int dis = 0;
        for(int j=index;j<n;j++){
            if(num == a[j]){
                break;
            }
            else{
                dis++;
            }
        }
        dist[i] = dis;
        maxDist = max(maxDist,dist[i]);
    }
    for(int i=0;i<bSize;i++){
        if(dist[i] == maxDist){
            b[i] = a[index];
            break;
        }
    }
    return;
}

void optimal(int* a, int n, int m){
    cout<<"Optimal"<<endl;
    int pageFault = 0;
    int b[m];
    for(int i=0;i<m;i++)b[i] = -1;
    int bSize = 0;
    for(int i=0;i<n;i++){
        int process = a[i];
        int check = checkPresentInArray(b,bSize,a[i]);
        if(check == 1){
            cout<<"No page fault"<<endl;
            continue;
        }
        pageFault++;
        if(bSize != m){
            b[bSize] = a[i];
            bSize++;
            displayArray(b,bSize);
            continue;
        }
        replaceOptimal(a,i,n,b,bSize);
        displayArray(b,bSize);
    }    
    cout<<"Total number of page faults = "<<pageFault<<endl;
}

void lru(int* a, int n, int m){
    cout<<"LRU"<<endl;
    int pageFault = 0;
    int b[m];
    for(int i=0;i<m;i++)b[i] = -1;
    int bSize = 0;
    int lruArray[m];
    for(int i=0;i<m;i++)lruArray[i] = -1;
    for(int i=0;i<n;i++){
        int process = a[i];
        int check = checkPresentInArray(b,bSize,a[i]);
        if(check == 1){
            cout<<"No page fault"<<endl;
            for(int j=0;j<bSize;j++){
                if(process == b[j])lruArray[j] = 0;
                else lruArray[j]++;
            }
            continue;
        }
        pageFault++;
        if(bSize != m){
            b[bSize] = a[i];
            bSize++;
            for(int j=0;j<bSize;j++){
                if(process == b[j])lruArray[j] = 0;
                else lruArray[j]++;
            }
            displayArray(b,bSize);
            continue;
        }
        int maxlru = INT_MIN;
        int maxIndex = -1;
        for(int j=0;j<m;j++){
            if(lruArray[j]>maxlru){
                maxlru = lruArray[j];
                maxIndex = j;
            }
        }
        b[maxIndex] = a[i];
        for(int j=0;j<bSize;j++){
            if(process == b[j])lruArray[j] = 0;
            else lruArray[j]++;
        }
        displayArray(b,bSize);
    }    
    cout<<"Total number of page faults = "<<pageFault<<endl;
}

int32_t main(){
    int n;
    cout<<"Sequence Length: ";
    cin>>n;
    int a[n];
    cout<<"Enter Sequence: ";
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        a[i] = x;
    }
    int m;
    cout<<"Page-frame size: ";
    cin>>m;
    int opcode;
    cout<<endl;
    cout<<"FIFO - 1\nOptimal - 2\nLRU - 3\n";
    cout<<"Enter Page replacement strategy: ";
    cin>>opcode;
    switch (opcode)
    {
        case 1:fifo(a,n,m);break;
        case 2:optimal(a,n,m);break;
        case 3:lru(a,n,m);break;
    }
}

 
 
 
 
 
 

















