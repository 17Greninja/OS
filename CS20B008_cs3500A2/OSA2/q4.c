#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define sz 100000
int MAX_INT = 100000;
// int N;
// int MAX = 0;
int arraySize;
int ans = 0;
int n;
int array[sz];

int element;

int currentThread = 0;
void* sortingThread(void *input){
    int curr = currentThread++;
    if(curr == 0){
        // sort array from 0 to arraySize/2
        int array1[arraySize/2];
        for(int i=0;i<arraySize/2;i++)array1[i] = array[i];
        int size1 = arraySize/2;
        for(int i=0;i<size1-1;i++){
            for(int j=0;j<size1-i-1;j++){
                if(array1[j]>array1[j+1]){
                    int tmp = array1[j];
                    array1[j] = array1[j+1];
                    array1[j+1] = tmp;
                }
            }
        }
        for(int i=0;i<arraySize/2;i++)array[i] = array1[i];
    }
    else{
        // sort array from arraySize/2 to arraySize
        int array2[arraySize - (arraySize/2)];
        for(int i=arraySize/2;i<arraySize;i++)array2[i-(arraySize/2)] = array[i];
        int size2 = arraySize - (arraySize/2);
        for(int i=0;i<size2-1;i++){
            for(int j=0;j<size2-i-1;j++){
                if(array2[j]>array2[j+1]){
                    int tmp = array2[j];
                    array2[j] = array2[j+1];
                    array2[j+1] = tmp;
                }
            }
        }
        for(int i=arraySize/2;i<arraySize;i++)array[i] = array2[i-(arraySize/2)];
    }
}

void* mergeThread(void* args) {
    int array1[arraySize/2];
    for(int i=0;i<arraySize/2;i++)array1[i] = array[i];
    int size1 = arraySize/2;
    int array2[arraySize - (arraySize/2)];
    for(int i=arraySize/2;i<arraySize;i++)array2[i-(arraySize/2)] = array[i];
    int size2 = arraySize - (arraySize/2);
    int index = 0;
    int p1 = 0;
    int p2 = 0;
    
    while(p1<size1 && p2<size2){
        if(array1[p1]>array2[p2]){
            array[index] = array2[p2];
            index++;
            p2++;
        }
        else{
            array[index] = array1[p1];
            index++;
            p1++;
        }
    }
    while(p1<size1){
        array[index] = array1[p1];
        index++;
        p1++;
    }
    while(p2<size2){
        array[index] = array2[p2];
        index++;
        p2++;
    }
}

int currentThread2 = 0;
void* ThreadSearch(void* args) {
   int curr = currentThread2++;
   for (int i = curr * (arraySize / n); i < ((curr + 1) * (arraySize / n)); i++){
      if (array[i]%element ==0)
         ans++; 
   }
   if(curr == n-1){
        for(int i=(curr+1)*(arraySize/n);i<arraySize;i++){   
            if (array[i]%element ==0){
                ans++;
            }
        }
   }
}

int main() 
{
    printf("Enter array elements: ");
    
    char msg[50], ch;
    int index = 0;
    while ((ch = getchar()) != '\n')
        msg[index++] = ch;
    msg[index] = '\0';
    char* token = strtok(msg, " ");
    arraySize = 0;
    while (token != NULL) {
        // printf("%s ", token);
        array[arraySize] = atoi(token);
        arraySize++;
        token = strtok(NULL, " ");
    }
    printf("Enter the value of N: ");
    scanf("%d",&n);
    printf("Enter the value of element: ");
    scanf("%d",&element);
    printf("Size of array is: %d\n",arraySize);
    pthread_t threads[3]; 
    pthread_create(&threads[0], NULL, sortingThread, (void*)NULL);
    pthread_create(&threads[1], NULL, sortingThread, (void*)NULL);
    pthread_create(&threads[2], NULL, mergeThread, (void*)NULL);
    for (int i = 0; i < 3; i++) {
      pthread_join(threads[i], NULL);
    }
    pthread_t countThread[n];
    for(int i=0;i<n;i++){
        pthread_create(&countThread[i], NULL, ThreadSearch, (void*)NULL);
    }
    for (int i=0;i<n;i++){
        pthread_join(countThread[i], NULL); //wait until all of the threads are completed
    }
    printf("Number of elements in the array: %d\n",arraySize);
    printf("Number of elements in the array divisible by given element: %d\n",ans);
    printf("Sorted array:\n");
    for(int i=0;i<arraySize;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}