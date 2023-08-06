#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define REQUEST 100
#define PIVOT 200
#define LARGE 300
#define SMALL 400
#define READY 500

int id;
char *my_read_pipe[5];
char *my_write_pipe[5];

int dataArray[5];
int data_len = 5;

void my_r_w_pipeInitialise(){
    my_write_pipe[0] = "r0";
    my_read_pipe[0] = "w0";
    my_write_pipe[1] = "r1";
    my_read_pipe[1] = "w1";
    my_write_pipe[2] = "r2";
    my_read_pipe[2] = "w2";
    my_write_pipe[3] = "r3";
    my_read_pipe[3] = "w3";
    my_write_pipe[4] = "r4";
    my_read_pipe[4] = "w4";
}

int emp(int a[5])
{
    for (int i = 0; i < 5;i++)
    {if(a[i]!=-1)
            return 0;
    }
    return -1;
}

void readInput(int childId){
    FILE* file;
    char fileName[100] = "data_i.txt";
    fileName[5] = childId + 1 + 48;
    file = fopen(fileName, "r");
    fscanf(file, "%d", &dataArray[0]);
    fscanf(file, "%d", &dataArray[1]);
    fscanf(file, "%d", &dataArray[2]);
    fscanf(file, "%d", &dataArray[3]);
    fscanf(file, "%d", &dataArray[4]);
    fclose(file);
    return;
}

int main(int argc, char* argv[]) {   
    my_r_w_pipeInitialise();
    srand(time(0));
    int i = atoi(argv[1]);
    id = i;
    int fileDescRead1 = open(my_read_pipe[i], O_RDONLY);
    int fileDescWrite1 = open(my_write_pipe[i], O_WRONLY);
    readInput(i);
    char readBuffer[100];
    int read_bytes = read(fileDescRead1, readBuffer, sizeof(readBuffer));
    readBuffer[read_bytes] = '\0';
    printf("Child %s sends READY\n",readBuffer);
    char writebuf[80] = "READY";
    write(fileDescWrite1, writebuf, sizeof(writebuf));
    int pivot;
    while (1){
        char readBuffer[80];
        int read_bytes = read(fileDescRead1, readBuffer, sizeof(readBuffer));
        readBuffer[read_bytes] = '\0';
        if(strcmp(readBuffer, "REQUEST") == 0){
            int check = -1;
            int ans = -1;
            for(int i=0;i<5;i++){
                if(dataArray[i] != -1)check = 0;
            }
            if(check != -1){
                while(1){
                    int randomIndex = rand()%5;
                    if(dataArray[randomIndex] == -1)continue;
                    ans = dataArray[i];
                    break;
                }
            }
            char writebuf[80];
            sprintf(writebuf, "%d", ans);
            write(fileDescWrite1, writebuf, sizeof(writebuf));
        }
        else if(strcmp(readBuffer, "PIVOT") == 0){
            char writebuf[80];
            write(fileDescWrite1, writebuf, sizeof(writebuf));
            char readBuffer[80];
            int read_bytes = read(fileDescRead1, readBuffer, sizeof(readBuffer));
            readBuffer[read_bytes] = '\0';
            pivot = atoi(readBuffer);
            int ans = 0;
            for(int i=0;i<5;i++){
                if(dataArray[i] > pivot)ans++;
            }
            printf("Child %d receives pivot %d and replies %d\n", i + 1, pivot, ans);
            char writebuf3[80];
            sprintf(writebuf3, "%d", ans);
            write(fileDescWrite1, writebuf3, sizeof(writebuf3));
        }
        else if(strcmp(readBuffer, "SMALL") == 0){
            for(int i=0;i<5;i++){
                if(dataArray[i]<pivot){
                    dataArray[i] = -1;
                    data_len--;
                }
            }
        }
        else if(strcmp(readBuffer, "LARGE") == 0){    
            for(int i=0;i<5;i++){
                if(dataArray[i]>pivot){
                    dataArray[i] = -1;
                    data_len--;
                }
            }
        }
        else if(strcmp(readBuffer, "EXIT") == 0){   
            printf("Child %d terminating\n", i);
            exit(0);
        }
   } 
  close(fileDescRead1);
  close(fileDescWrite1);

  return 0;
}