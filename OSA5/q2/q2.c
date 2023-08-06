#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include<stdio.h>
#include <stdlib.h>

#define maxBufferSize 1000 

int p, c, pc, cc;
int top = -1;
int myStack[maxBufferSize];
sem_t empty;
sem_t full;
pthread_mutex_t mutex;


void *producer(void *pno);
void *consumer(void *cno);
void destroy();

int main(int argc, char** argv)
{   
    srand(time(0));
    p = atoi(argv[2]);
    pc = atoi(argv[4]);
    c = atoi(argv[6]);
    cc = atoi(argv[8]);

    pthread_t pro[p],con[c];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,maxBufferSize);
    sem_init(&full,0,0);

    int producerNum[p];
    int consumerNum[c];
    for (int i = 0; i < p;i++){ 
        producerNum[i] = i + 1;
    }
    for (int i = 0; i < c;i++){ 
        consumerNum[i] = i + 1;
    }
    for (int i = 0; i < p; i++){ 
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&producerNum[i]);
    }
    for (int i = 0; i < c; i++){
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&consumerNum[i]);
    }
    for(int i = 0; i < p; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < c; i++) {
        pthread_join(con[i], NULL);
    }
    destroy();
    return 0;
}

void destroy(){
    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
}

void *consumer(void *cno){   
    for(int i = 0; i < cc; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if(top<=-1){   
            while(1){
                if(!(top<=-1))break;
            }
        }
        int item = myStack[top];
        printf("Consumer %d consumed %d\n",*((int *)cno),item);
        top--;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int getRand(){
    return rand()%1000;
}

void *producer(void *pno){   
    // sleep(5);
    int item;
    for(int i = 0; i < pc; i++) {
        item = getRand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        if(top>=maxBufferSize-1){ 
            while(1){
                if(!(top>=maxBufferSize-1))break;
            }
        }
        top++;
        myStack[top] = item;
        printf("Producer %d produced %d\n", *((int *)pno),myStack[top]);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}