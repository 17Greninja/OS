// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 100

// structure for message queue
struct message {
	long messageType;  // -1 for End
	char messageText[100];
} message;

int main(){
	// ftok to generate unique key
	key_t keyC2S = ftok("C2S", 65);
    key_t keyS2C = ftok("S2C", 65);
	
	while(1){
		struct message inputMessage;
     	struct message outputMessage;
		// msgget creates a message queue
		// and returns identifier
		int C2S = msgget(keyC2S, 0666 | IPC_CREAT);
		int S2C = msgget(keyS2C, 0666 | IPC_CREAT);
		printf("Input the system call : ");
		fgets(inputMessage.messageText,MAX,stdin);
		inputMessage.messageText[strcspn(inputMessage.messageText, "\n")] = 0;
		inputMessage.messageType = 1;
		if (strcmp(inputMessage.messageText, "End") == 0){
			msgsnd(C2S, &inputMessage, sizeof(inputMessage), 0);
			printf("Terminating...\n");
			return 0;
		}
		msgsnd(C2S, &inputMessage, sizeof(inputMessage), 0);
		msgrcv(S2C, &outputMessage, sizeof(outputMessage), 1, 0);
		printf("Server sends the return value of the system call: %s \n", outputMessage.messageText);
	}

	return 0;
}
