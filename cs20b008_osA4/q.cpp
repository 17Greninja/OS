#include<bits/stdc++.h> 
using namespace std;
#define int long long
#define Y cout<<"YES"<<endl
#define N cout<<"NO"<<endl
#define D cout<<"DEBUG"<<endl

class Process{
    public:
    string id; 
    int arrivalTime;
    int burstTime;
    int processType;
    bool complete;
    int waitingTime;
    int processNumber;
    int timeGivenToProcess;
    int finishingTime;
    int processPriority;
    int timeNeeded;
};

class Compare1 {
  public:
    bool operator() (Process p1, Process p2) {
        if(p1.processPriority != p2.processPriority)return p1.processPriority > p2.processPriority;
        else return p1.arrivalTime > p2.arrivalTime;
    }
};

class Compare2 {
  public:
    bool operator() (Process p1, Process p2) {
        if(p1.timeNeeded != p2.timeNeeded)return p1.timeNeeded > p2.timeNeeded;
        else return p1.arrivalTime > p2.arrivalTime;
    }
};

class Compare3 {
  public:
    bool operator() (Process p1, Process p2) {
      return p1.arrivalTime > p2.arrivalTime;
    }
};

int q;
int n;
int completed = 0;
int currentTime = 0;
vector<Process> p;
vector<int> execSequence;
int qnumber = -1;
int qtime = 0;
int sizeQueue[6] = {0,0,0,0,0,0};

priority_queue<Process, std::vector<Process>, Compare1> q1; 
priority_queue<Process, std::vector<Process>, Compare3> q2; 
priority_queue<Process, std::vector<Process>, Compare3> q3; 
priority_queue<Process, std::vector<Process>, Compare2> q4; 
priority_queue<Process, std::vector<Process>, Compare2> q5; 

void run1SecQ1(){
    Process tmp = q1.top();
    int pNumber = tmp.processNumber;
    q1.pop();
    p[pNumber].timeGivenToProcess++;
    p[pNumber].timeNeeded--;
    execSequence.push_back(pNumber);
    if(p[pNumber].timeGivenToProcess == p[pNumber].burstTime){
        p[pNumber].complete = true;
        completed++;
        p[pNumber].finishingTime = currentTime;
        sizeQueue[1]--;
        return;
    }
    else{
        q1.push(p[pNumber]);
    }
    return;
}

void run1SecQ2(){
    Process tmp = q2.top();
    int pNumber = tmp.processNumber;
    q2.pop();
    p[pNumber].timeGivenToProcess++;
    p[pNumber].timeNeeded--;
    execSequence.push_back(pNumber);
    if(p[pNumber].timeGivenToProcess == p[pNumber].burstTime){
        p[pNumber].complete = true;
        completed++;
        p[pNumber].finishingTime = currentTime;
        sizeQueue[2]--;
        return;
    }
    else{
        q2.push(p[pNumber]);
    }
    return;
}

void run1SecQ3(){ 
    Process tmp = q3.top();
    int pNumber = tmp.processNumber;
    q3.pop();
    p[pNumber].timeGivenToProcess++;
    p[pNumber].timeNeeded--;
    execSequence.push_back(pNumber);
    if(p[pNumber].timeGivenToProcess == p[pNumber].burstTime){
        p[pNumber].complete = true;
        completed++;
        p[pNumber].finishingTime = currentTime;
        sizeQueue[3]--;
        return;
    }
    else{
        q3.push(p[pNumber]);
    }
    return;
}

void run1SecQ4(){
    Process tmp = q4.top();
    int pNumber = tmp.processNumber;
    q4.pop();
    p[pNumber].timeGivenToProcess++;
    p[pNumber].timeNeeded--;
    execSequence.push_back(pNumber);
    if(p[pNumber].timeGivenToProcess == p[pNumber].burstTime){
        p[pNumber].complete = true;
        completed++;
        p[pNumber].finishingTime = currentTime;
        sizeQueue[4]--;
        return;
    }
    else{
        q4.push(p[pNumber]);
    }
    return;
}

void run1SecQ5(){
    Process tmp = q5.top();
    int pNumber = tmp.processNumber;
    q5.pop();
    p[pNumber].timeGivenToProcess++;
    p[pNumber].timeNeeded--;
    execSequence.push_back(pNumber);
    if(p[pNumber].timeGivenToProcess == p[pNumber].burstTime){
        p[pNumber].complete = true;
        completed++;
        p[pNumber].finishingTime = currentTime;
        sizeQueue[5]--;
        return;
    }
    else{
        q5.push(p[pNumber]);
    }
    return;
}

void findQueueNumber(){
    if(qnumber == -1){
        if(sizeQueue[1]!=0){
            qnumber = 1;
            qtime = 1;
            return;
        }
        if(sizeQueue[2]!=0){
            qnumber = 2;
            qtime = 1;
            return;
        }
        if(sizeQueue[3]!=0){
            qnumber = 3;
            qtime = 1;
            return;
        }
        if(sizeQueue[4]!=0){
            qnumber = 4;
            qtime = 1;
            return;
        }
        if(sizeQueue[5]!=0){
            qnumber = 5;
            qtime = 1;
            return;
        }
        else return;
    }
    else{
        if(qtime == q){
            qtime = 1;
            int cur = qnumber;
            int x = (cur%5)+1;
            while(x!=cur){
                if(sizeQueue[x]!=0){
                    qnumber = x;
                    return;
                }
                else{
                    x = (x%5)+1;
                }
            }
            if(sizeQueue[qnumber] !=0)return;
            else qnumber = -1;
            return;
        }
        else{
            if(sizeQueue[qnumber] != 0){
                qtime++;
                return;
            }
            else{
                qtime = 1;
                int cur = qnumber;
                int x = (cur%5)+1;
                while(x!=cur){
                    if(sizeQueue[x]!=0){
                        qnumber = x;
                        return;
                    }
                    else{
                        x = (x%5)+1;
                    }
                }
                qnumber = -1;
                return;
            }
        }
    }
}

int32_t main(){
    cin>>q;
    cin>>n;
    map<int,string> m; // pNumber -- id 
    m[-1] = -1;
    for(int i=0;i<n;i++){
        Process tmp;
        cin>>tmp.id;
        cin>>tmp.arrivalTime;
        cin>>tmp.burstTime;
        // cin>>tmp.processType;
        string s;cin>>s;
        if(s == "sys")tmp.processType = 1;
        else if(s == "ip")tmp.processType = 2;
        else if(s == "iep")tmp.processType = 3;
        else if(s == "bp")tmp.processType = 4;
        else if(s == "sp")tmp.processType = 5;
        cin>>tmp.processPriority;
        tmp.complete = false;
        tmp.waitingTime = 0;
        tmp.timeGivenToProcess = 0;
        tmp.processNumber = i;
        tmp.finishingTime = -1;
        tmp.timeNeeded = tmp.burstTime;
        m[tmp.processNumber] = tmp.id; 
        p.push_back(tmp);
    }
    while(completed<n){
        // simulation between currentTime to currentTime+1
        for(int i=0;i<n;i++){
            if(p[i].arrivalTime == currentTime){
                switch (p[i].processType){
                    case 1 : q1.push(p[i]);sizeQueue[1]++;break;
                    case 2 : q2.push(p[i]);sizeQueue[2]++;break;
                    case 3 : q3.push(p[i]);sizeQueue[3]++;break;
                    case 4 : q4.push(p[i]);sizeQueue[4]++;break;
                    case 5 : q5.push(p[i]);sizeQueue[5]++;break;
                }
            }
        }
        // cout<<qnumber<<endl;
        findQueueNumber();
        switch (qnumber){
            case 1: run1SecQ1();break;
            case 2: run1SecQ2();break;
            case 3: run1SecQ3();break;
            case 4: run1SecQ4();break;
            case 5: run1SecQ5();break;
            case -1: execSequence.push_back(-1);break;
        }
        currentTime++;
    }
    
    cout<<"Process execution sequence:\n";
    int cur = execSequence[0];
    int start = 0;
    int tmp = 1;
    for(int i=1;i<execSequence.size();i++){
        if(cur == execSequence[i])tmp++;
        if(cur != execSequence[i]){
            if(cur == -1){
                cout<<"Idle: "<<start<<" to "<<start+tmp<<endl;
                start+=tmp;
            }
            else {
                cout<<"Process_id: "<<m[cur]<<" :: Time: "<<start<<" to "<<start+tmp<<endl;
                start += tmp;
            }
            cur = execSequence[i];
            tmp = 1;
        }
    }
    if(cur == -1)cout<<"Idle: "<<start<<" to "<<start+tmp<<endl;
    else cout<<"Process_id: "<<m[cur]<<" :: Time: "<<start<<" to "<<start+tmp<<endl;
    
    cout<<"Scheduling statistics:\n";
    
    for(int i=0;i<n;i++){
        cout<<"Process_id: "<<p[i].id<<" :: Completion_time: "<<p[i].finishingTime + 1<<" :: TAT: "<<
            p[i].finishingTime + 1 - p[i].arrivalTime<<" :: WT: "<<p[i].finishingTime + 1 -p[i].arrivalTime-p[i].burstTime<<endl;
    }
    return 0;
}