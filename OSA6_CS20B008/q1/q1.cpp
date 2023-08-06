#include<bits/stdc++.h> 
using namespace std;
#define int long long
#define Y cout<<"YES"<<endl
#define N cout<<"NO"<<endl
#define D cout<<"DEBUG"<<endl

void firstFit(int *a, int n,int* b,int m){
    int check[n+1];
    for(int i=1;i<=n;i++)check[i] = 0;
    cout<<"First-Fit"<<endl;
    cout<<"Process number | Process size | Block size | Block Number"<<endl;
    for(int i=1;i<=m;i++){
        cout<<i<<"\t"<<b[i]<<"\t";
        int flag = 0;
        for(int j=1;j<=n;j++){
            if(check[j] == 0 && b[i]<=a[j]){
                check[j] = 1;
                flag = 1;
                cout<<a[j]<<"\t"<<j<<endl;
                break;
            }
        }
        if(flag == 0){
            cout<<"Not Allocated"<<endl;
        }
    }
}

void bestFit(int *a, int n,int* b,int m){
    int check[n+1];
    for(int i=1;i<=n;i++)check[i] = 0;
    cout<<"Best-Fit"<<endl;
    cout<<"Process number | Process size | Block size | Block Number"<<endl;
    for(int i=1;i<=m;i++){
        cout<<i<<"\t"<<b[i]<<"\t";
        int flag = 0;
        int smallest = 0;
        int smallestIndex = -1;
        for(int j=1;j<=n;j++){
            if(a[j]>=b[i] && check[j] == 0){
                flag = 1;
                smallest = a[j];
                smallestIndex = j;
                break;
            }
        }
        if(flag == 0){
            cout<<"Not Allocated"<<endl;
            continue;
        }
        for(int j=1;j<=n;j++){
            if(a[j]<smallest && b[i]<=a[j] && check[j] == 0){
                smallest = a[j];
                smallestIndex = j;
            }
        }
        cout<<smallest<<"\t"<<smallestIndex<<endl;
        check[smallestIndex] = 1;
    }
}

void worstFit(int *a, int n,int* b,int m){
    int check[n+1];
    for(int i=1;i<=n;i++)check[i] = 0;
    cout<<"Worst-Fit"<<endl;
    cout<<"Process number | Process size | Block size | Block Number"<<endl;
    for(int i=1;i<=m;i++){
        cout<<i<<"\t"<<b[i]<<"\t";
        int flag = 0;
        int largest = 0;
        int largestIndex = -1;
        for(int j=1;j<=n;j++){
            if(a[j]>=b[i] && check[j] == 0){
                flag = 1;
                largest = a[j];
                largestIndex = j;
                break;
            }
        }
        if(flag == 0){
            cout<<"Not Allocated"<<endl;
            continue;
        }
        for(int j=1;j<=n;j++){
            if(a[j]>largest && b[i]<=a[j] && check[j] == 0){
                largest = a[j];
                largestIndex = j;
            }
        }
        cout<<largest<<"\t"<<largestIndex<<endl;
        check[largestIndex] = 1;
    }
}

int32_t main(){
    int n;
    cout<<"Enter number of blocks: ";
    cin>>n;
    int a[n+1];
    cout<<"Enter "<<n<<" block sizes: ";
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a[i] = x;
    }
    int m;
    cout<<"Enter number of processes: ";
    cin>>m;
    int b[m+1];
    cout<<"Enter "<<m<<" Process Sizes: ";
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        b[i] = x;
    }
    firstFit(a,n,b,m);
    cout<<endl;
    bestFit(a,n,b,m);
    cout<<endl;
    worstFit(a,n,b,m);
    cout<<endl;
}

 
 
 
 
 
 

















