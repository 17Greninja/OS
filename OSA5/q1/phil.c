#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


#define LEFT (phnum + n-1) % n
#define RIGHT (phnum + 1) % n
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define NUM_EAT 5


int n;
int phil[1000];
int eaten[1000];
int philState[1000];


sem_t mutex;
sem_t S[1000];
struct timeval stopTime, startTime;

void test(int phnum);
void take_fork(int phnum);
void put_fork(int phnum);
void* philosopher(void* num);

u_int64_t getTime(){
	gettimeofday(&stopTime, NULL);
	u_int64_t x = (stopTime.tv_usec - startTime.tv_usec + (stopTime.tv_sec - startTime.tv_sec)*1000000)/1000;
	return x;
}

int main(int argc, char** argv){   
	srand(time(0));
	n = atoi(argv[1]);
	gettimeofday(&startTime, NULL);
	for (int j = 0; j < n;j++){
		eaten[j] = 0;
		phil[j] = j;
	}
	pthread_t thread_id[n];
	sem_init(&mutex, 0, 1);
    for (int i = 0; i < n; i++)sem_init(&S[i], 0, 0);
	for (int i = 0; i < n; i++){
		pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
		u_int64_t netTime = getTime();
		printf("<%lu> Philosopher %d in THINKING philState\n",netTime, i+1);
	}
	for (int i = 0; i < n; i++)pthread_join(thread_id[i], NULL);
}

void test(int phnum){
	if (philState[phnum] == HUNGRY
		&& philState[LEFT] != EATING
		&& philState[RIGHT] != EATING) {
	    
		philState[phnum] = EATING;
        
		gettimeofday(&stopTime, NULL);
		u_int64_t x = ((stopTime.tv_sec - startTime.tv_sec) * 1000000 + stopTime.tv_usec - startTime.tv_usec);
		x /= 1000;
		eaten[phnum]++;
		printf("<%lu> Philosopher %d in EATING philState - %d\n",x, phnum+1, eaten[phnum]);
		sem_post(&S[phnum]);
	}
}

void put_fork(int phnum){   
	sem_wait(&mutex);
	philState[phnum] = THINKING;
	u_int64_t netTime = getTime();
	printf("<%lu> Philosopher %d in THINKING philState\n",netTime, phnum+1);
	int thinkingTime = rand()%50 + 50;
	usleep(thinkingTime*1000);
	test(LEFT);
	test(RIGHT);

	sem_post(&mutex);
}

void* philosopher(void* num){  
	int thinkingTime = rand()%50 + 50;
	usleep(thinkingTime*1000);
	while (1) {
        int* i = num;
		int pNum = *i;
		if(eaten[pNum]>=NUM_EAT)break;
		take_fork(pNum);
        put_fork(pNum);
	}
}

void take_fork(int phnum){   
	sem_wait(&mutex);
    philState[phnum] = HUNGRY;
	test(phnum);
    sem_post(&mutex);
	sem_wait(&S[phnum]);
    usleep(100*1000);
}



