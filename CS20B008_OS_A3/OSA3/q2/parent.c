#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define REQUEST 100
#define PIVOT 200
#define LARGE 300
#define SMALL 400
#define READY 500

char *readPipe[5];
char *writePipe[5];
int fd_write_1, fd_write_2, fd_write_3, fd_write_4, fd_write_5, fd_write_6, fd_write_7;
int fd_read1, fd_read2, fd_read3;

int pivot = -1;
int myDataArr[5];
int m = 0;
int z = 25/2;

void pipeInitialise(){
    writePipe[0] = "w0";
    readPipe[0] = "r0";
    writePipe[1] = "w1";
    readPipe[1] = "r1";
    writePipe[2] = "w2";
    readPipe[2] = "r2";
    writePipe[3] = "w3";
    readPipe[3] = "r3";
    writePipe[4] = "w4";
    readPipe[4] = "r4";
}

void pipeUnlink(){
    unlink(readPipe[0]);
    unlink(readPipe[1]);
    unlink(readPipe[2]);
    unlink(readPipe[3]);
    unlink(readPipe[4]);
    unlink(writePipe[0]);
    unlink(writePipe[1]);
    unlink(writePipe[2]);
    unlink(writePipe[3]);
    unlink(writePipe[4]);
}

void myMakeFifo(){
    mkfifo(readPipe[0], 0666);
    mkfifo(readPipe[1], 0666);
    mkfifo(readPipe[2], 0666);
    mkfifo(readPipe[3], 0666);
    mkfifo(readPipe[4], 0666);
    mkfifo(writePipe[0], 0666);
    mkfifo(writePipe[1], 0666);
    mkfifo(writePipe[2], 0666);
    mkfifo(writePipe[3], 0666);
    mkfifo(writePipe[4], 0666);
}

void createChildProcess(){
    for(int i=0;i<5;i++){
        pid_t childPid = fork();
        if(childPid == 0){
            char *binaryPath = "./child";
            char input[80];
            sprintf(input, "%d", i);
            char *ch_args[] = {binaryPath,input,NULL};
            execv(binaryPath, ch_args);
        }
        fd_write_1 = open(writePipe[i], O_CREAT | O_WRONLY);
        char writeBuffer[80];
        sprintf(writeBuffer, "%d", i);
        write(fd_write_1, writeBuffer, sizeof(writeBuffer));
        fd_read1 = open(readPipe[i], O_RDONLY);
        char readBuffer[80];
        int bytesRead = read(fd_read1, readBuffer, sizeof(readBuffer));
        
        readBuffer[bytesRead] = '\0';
    }
}

void selectPivot(){
    while(pivot == -1){
        int childId = rand()%5;
        char writeBuffer[80] = "REQUEST";
        fd_write_2 = open(writePipe[childId], O_WRONLY);
        write(fd_write_2, writeBuffer, sizeof(writeBuffer));

        fd_read2 = open(readPipe[childId], O_RDONLY);
        char readBuffer[80];
        int bytesRead = read(fd_read2, readBuffer, sizeof(readBuffer));

        readBuffer[bytesRead] = '\0';
        pivot = atoi(readBuffer);
        printf("parent sends REQUEST to Child %d\n", childId);
    }
}

void closeFifos(){
    close(fd_read1);
    close(fd_read2);
    close(fd_read3);
    close(fd_write_1);
    close(fd_write_2);
    close(fd_write_3);
    close(fd_write_4);
    close(fd_write_5);
    close(fd_write_6);
    close(fd_write_7);
    return;
}

void sumAndPrint(){
    m = 0;
    for(int i=0;i<5;i++)m += myDataArr[i];
    printf("Parent: %d=%d+%d+%d+%d+%d\n", m, myDataArr[0], myDataArr[1], myDataArr[2], myDataArr[3], myDataArr[4]); 
    return;
}

void medianFound(){
    printf("Median found,%d\n",pivot);
    printf("Parent sends kill signals to all children\n");
    for (int k = 0; k < 5; k++)
    {
      char writebuf1[80] = "EXIT";
      fd_write_5 = open(writePipe[k], O_WRONLY);
      write(fd_write_5, writebuf1, sizeof(writebuf1));
    }
    return;
}

void callSmall(){
    for (int k = 0; k < 5; k++){
        char writebuf1[80] = "SMALL";
        fd_write_6 = open(writePipe[k], O_WRONLY);
        write(fd_write_6, writebuf1, sizeof(writebuf1));
    }
    return;
}

void callLarge(){
    for (int k = 0; k < 5;k++){
        char writebuf1[80] = "LARGE";
        fd_write_7 = open(writePipe[k], O_WRONLY);
        write(fd_write_7, writebuf1, sizeof(writebuf1));
    }
    return;
}

int main() {
    pipeInitialise();
    pipeUnlink();
    myMakeFifo();
    createChildProcess();
    printf("Parent Ready\n");

    srand(time(0));

    while(1){
        pivot = -1;
        selectPivot();
        printf("Parent broadcasts pivot %d to all children\n", pivot);

        // do stuff here
        for (int k = 0; k < 5; k++){
            char writeBuffer[80] = "PIVOT";
            fd_write_3 = open(writePipe[k], O_WRONLY);
            write(fd_write_3, writeBuffer, sizeof(writeBuffer));

            int fdrx = open(readPipe[k], O_RDONLY);
            char readbuf1[80];
            int read_bytes1 = read(fdrx, readbuf1, sizeof(readbuf1));
            readbuf1[read_bytes1] = '\0';
          
            char writebuf2[80];
            sprintf(writebuf2, "%d", pivot);
              fd_write_4 = open(writePipe[k], O_WRONLY);
            write(fd_write_4, writebuf2, sizeof(writebuf2));

            int fdr3 = open(readPipe[k], O_RDONLY);
            char readbuf3[80];
            int read_bytes2 = read(fdr3, readbuf3, sizeof(readbuf3));
          
            readbuf3[read_bytes2] = '\0';
            myDataArr[k] = atoi(readbuf3);
        }
        
        sumAndPrint();

        if(m == z){
            medianFound();
            break;
        }
        else if(m>z){
            callSmall();
        }
        else if(m<z){
            callLarge();
            z = z-m;
        }
    }
    closeFifos();
    return 0;
}    