#include<bits/stdc++.h> 
using namespace std;

class Inode{
public:
    string fName;
    int type;
    int fileSize; // in Bytes
    string dateCreated;
    string dateModified;
    int directBlock[3];
    vector<int> indexBlocks;
    int indexBlock;
};

vector<int> blockFilled; // bit-vector: 1 if filled, else empty.
vector<int> spaces; // spaces to store integers
int D; // Disk size in KB
map<string,Inode> mapFileInode;
vector<string> files;
int numBlocks;

void load(string fileName);
const string currentDateTime();
void deLete(string fileName);
bool checkFileExist(string fileName);
void fillBlockSpaces(int blockNumber);
void print(string fileName);
void printBlock(int blockNumber);
void append(string fileName);
int insertIntoFile(string fileName,int x);
int getFreeBlock(string fileName);
int getSomeFreeBlock();
bool checkFree(int blockNumber);
void display();
void freespace();
void printInode(string fileName);

int main(int argc, char* argv[]){
    D = atoi(argv[1]);
    numBlocks = D*8;
    numBlocks -= 5; // 5 blocks at the end of the diskfile will maintain disk directory information
    for(int i=0;i<numBlocks;i++)blockFilled.push_back(0);
    int numSpaces = numBlocks*32;
    for(int i=0;i<numSpaces;i++)spaces.push_back(-1);
    for(int i=2;i<argc;i++){
        files.push_back(argv[i]);
    }
    while(1){
        cout<<"Enter command: ";
        string command;
        cin>>command;
        if(command == "load"){
            string fileName;
            cout<<"Enter file name: ";
            cin>>fileName;
            load(fileName);
        }
        else if(command == "delete"){
            string fileName;
            cout<<"Enter file name: ";
            cin>>fileName;
            deLete(fileName);
        }
        else if(command == "print"){
            string fileName;
            cout<<"Enter file name: ";
            cin>>fileName;
            print(fileName);
        }
        else if(command == "append"){
            string fileName;
            cout<<"Enter file name: ";
            cin>>fileName;
            append(fileName);
        }
        else if(command == "display"){
            display();
        }
        else if(command == "freespace"){
            freespace();
        }
        else if(command == "printinode"){
            string fileName;
            cout<<"Enter file name: ";
            cin>>fileName;
            printInode(fileName);
        }
        else if(command == "exit"){
            cout<<"Exiting...\n";
            break;
        }
        else{
            cout<<"Invalid command\n";
        }
    }
    cout<<"Process terminated\n";
    return 0;
}

const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

bool checkFileExist(string fileName){
    for(int i=0;i<files.size();i++){
        if(fileName == files[i])return true;
    }
    return false;
}

void load(string fileName){
    if(!checkFileExist(fileName)){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    Inode tmp;
    tmp.fName = fileName;
    tmp.type = 0;
    tmp.fileSize = 0;
    tmp.dateCreated = currentDateTime();
    tmp.dateModified = currentDateTime();
    tmp.directBlock[0] = -1;
    tmp.directBlock[1] = -1;
    tmp.directBlock[2] = -1;
    tmp.indexBlock = -1;
    mapFileInode[fileName] = tmp;
    return;
}

void fillBlockSpaces(int blockNumber){
    for(int i=0;i<32;i++){
        spaces[blockNumber*32 + i] = -1;
    }
}

void deLete(string fileName){
    if(!checkFileExist(fileName)){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    if(mapFileInode.find(fileName) == mapFileInode.end()){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    files.erase(remove(files.begin(), files.end(), fileName), files.end());
    if(mapFileInode[fileName].directBlock[0] != -1){
        blockFilled[mapFileInode[fileName].directBlock[0]] = 0;
        fillBlockSpaces(mapFileInode[fileName].directBlock[0]);
    }
    if(mapFileInode[fileName].directBlock[1] != -1){
        blockFilled[mapFileInode[fileName].directBlock[1]] = 0;
        fillBlockSpaces(mapFileInode[fileName].directBlock[1]);
    }
    if(mapFileInode[fileName].directBlock[2] != -1){
        blockFilled[mapFileInode[fileName].directBlock[2]] = 0;
        fillBlockSpaces(mapFileInode[fileName].directBlock[2]);
    }
    for(int i=0;i<mapFileInode[fileName].indexBlocks.size();i++){
        blockFilled[mapFileInode[fileName].indexBlocks[i]] = 0;
        fillBlockSpaces(mapFileInode[fileName].indexBlocks[i]);
    }
    if(mapFileInode[fileName].indexBlocks.size()>=1)blockFilled[mapFileInode[fileName].indexBlock] = 0;
    mapFileInode[fileName].indexBlocks.clear();
    mapFileInode.erase(fileName);
    cout<<"File "<<fileName<<" successfully deleted\n";
    return;
}

void printBlock(int blockNumber){
    for(int i=0;i<32;i++){
        if(spaces[blockNumber*32 + i] == -1)return;
        cout<<spaces[blockNumber*32 + i]<<" ";
    }
    return;
}

void print(string fileName){
    if(!checkFileExist(fileName)){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    if(mapFileInode.find(fileName) == mapFileInode.end()){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    cout<<"Printing file contents: ";
    if(mapFileInode[fileName].directBlock[0] != -1){
        printBlock(mapFileInode[fileName].directBlock[0]);
    }
    if(mapFileInode[fileName].directBlock[1] != -1){
        printBlock(mapFileInode[fileName].directBlock[1]);
    }
    if(mapFileInode[fileName].directBlock[2] != -1){
        printBlock(mapFileInode[fileName].directBlock[2]);
    }
    for(int i=0;i<mapFileInode[fileName].indexBlocks.size();i++){
        printBlock(mapFileInode[fileName].indexBlocks[i]);
    }
    cout<<endl;
    return;
}

int getSomeFreeBlock(){
    for(int i=0;i<numBlocks;i++){
        if(blockFilled[i] == 0){
            blockFilled[i] = 1;
            return i;
        }
    }
    return -1;
}

bool checkFree(int blockNumber){
    for(int i=0;i<32;i++){
        if(spaces[blockNumber*32 + i] == -1)return true;
    }
    return false;
}

int getFreeBlock(string fileName){
    if(mapFileInode[fileName].directBlock[0] == -1){
        int free = getSomeFreeBlock();
        if(free == -1){
            cout<<"No space available\n";
            return -1;
        }
        mapFileInode[fileName].directBlock[0] = free;
        return free;
    }
    if(mapFileInode[fileName].directBlock[0] != -1){
        if(checkFree(mapFileInode[fileName].directBlock[0]))return mapFileInode[fileName].directBlock[0];
    }
    if(mapFileInode[fileName].directBlock[1] == -1){
        int free = getSomeFreeBlock();
        if(free == -1){
            cout<<"No space available\n";
            return -1;
        }
        mapFileInode[fileName].directBlock[1] = free;
        return free;
    }
    if(mapFileInode[fileName].directBlock[1] != -1){
        if(checkFree(mapFileInode[fileName].directBlock[1]))return mapFileInode[fileName].directBlock[1];
    }
    if(mapFileInode[fileName].directBlock[2] == -1){
        int free = getSomeFreeBlock();
        if(free == -1){
            cout<<"No space available\n";
            return -1;
        }
        mapFileInode[fileName].directBlock[2] = free;
        return free;
    }
    if(mapFileInode[fileName].directBlock[2] != -1){
        if(checkFree(mapFileInode[fileName].directBlock[2]))return mapFileInode[fileName].directBlock[2];
    }
    for(int i=0;i<mapFileInode[fileName].indexBlocks.size();i++){
        if(checkFree(mapFileInode[fileName].indexBlocks[i]))return mapFileInode[fileName].indexBlocks[i];
    }
    if(mapFileInode[fileName].indexBlocks.size() == 0){
        mapFileInode[fileName].indexBlock = getSomeFreeBlock();
    }
    if(mapFileInode[fileName].indexBlocks.size() == 32){
        cout<<"File reached max limit\n";
        return -1;
    }
    int free = getSomeFreeBlock();
    if(free == -1){
        cout<<"No space available\n";
        return -1;
    }
    mapFileInode[fileName].indexBlocks.push_back(free);
    return free;
}

int insertIntoFile(string fileName,int x){
    int freeBlock = getFreeBlock(fileName);
    if(freeBlock == -1)return -1;
    for(int i=0;i<32;i++){
        if(spaces[freeBlock*32 + i] == -1){
            spaces[freeBlock*32 + i] = x;
            return 1;
        }
    }
    return 1;
}

void append(string fileName){
    if(!checkFileExist(fileName)){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    if(mapFileInode.find(fileName) == mapFileInode.end()){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    cout<<"Enter number of integers you want to append: ";
    int numAppend;
    cin>>numAppend;
    cout<<"Enter the integers: ";
    int A[numAppend];
    for(int i=0;i<numAppend;i++)cin>>A[i];
    for(int i=0;i<numAppend;i++){
        int x = A[i];
        int check = insertIntoFile(fileName,x);
        if(check == -1){
            cout<<"Stop entering, space not available or file limit reached\n";
            cout<<i<<" numbers appended\n";
            mapFileInode[fileName].fileSize += i*4;
            mapFileInode[fileName].dateModified = currentDateTime();
            return;
        }
    }
    cout<<"All integers appended\n";
    mapFileInode[fileName].dateModified = currentDateTime();
    mapFileInode[fileName].fileSize += numAppend*4;
    return;
}
 
void display(){
    for(int i=0;i<files.size();i++){
        if(mapFileInode.find(files[i]) != mapFileInode.end()){
            cout<<"File name: "<<files[i]<<", file size: "<<mapFileInode[files[i]].fileSize<<" bytes"<<endl;
        }   
    }
    return;
} 

void freespace(){
    cout<<"Number of free blocks available: ";
    int ans = 0;
    for(int i=0;i<blockFilled.size();i++){
        if(blockFilled[i] == 1)ans++;
    }
    cout<<numBlocks - ans<<endl;
    ans = 0;
    for(int i=0;i<spaces.size();i++){
        if(spaces[i] == -1)ans++;
    }
    cout<<"Total free size: "<<ans*4<<" Bytes\n";
    return;
}
 
void printInode(string fileName){
    if(!checkFileExist(fileName)){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    if(mapFileInode.find(fileName) == mapFileInode.end()){
        cout<<"ERROR: The given file does not exist\n";
        return;
    }
    cout<<"************************\n";
    cout<<"Filename: "<<mapFileInode[fileName].fName<<endl;
    cout<<"Size: "<<mapFileInode[fileName].fileSize<<" bytes\n";
    cout<<"Date Created: "<<mapFileInode[fileName].dateCreated<<endl;
    cout<<"Date Last Modified: "<<mapFileInode[fileName].dateModified<<endl;
    cout<<"Direct block values: ";
    if(mapFileInode[fileName].directBlock[0] != -1){
        cout<<mapFileInode[fileName].directBlock[0]<<" ";
    }
    if(mapFileInode[fileName].directBlock[1] != -1){
        cout<<mapFileInode[fileName].directBlock[1]<<" ";
    }
    if(mapFileInode[fileName].directBlock[2] != -1){
        cout<<mapFileInode[fileName].directBlock[2]<<" ";
    }
    cout<<endl;
    cout<<"Index block is stored in: ";
    if(mapFileInode[fileName].indexBlock == -1){
        cout<<"No index block\n";
    }
    else{
        cout<<mapFileInode[fileName].indexBlock<<endl;
    }
    cout<<"Index block contents: ";
    for(int i=0;i<mapFileInode[fileName].indexBlocks.size();i++){
        cout<<mapFileInode[fileName].indexBlocks[i]<<" ";
    }
    cout<<endl;
    cout<<"************************"<<endl;
} 
