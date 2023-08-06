// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include<unistd.h>
#include <sched.h>

// structure for message queue
struct message {
	long messageType;  // -1 for End
	char messageText[100];
} message;

int main(){
	// ftok to generate unique key
	key_t key1 = ftok("C2S", 65);
    key_t key2 = ftok("S2C", 65);

	char write_sys[] = "write";
	/*
	NAME         top
       	write - write to a file descriptor
	SYNOPSIS         top
       #include <unistd.h>
       ssize_t write(int fd, const void *buf, size_t count);
	DESCRIPTION         top
       write() writes up to count bytes from the buffer starting at buf
       to the file referred to by the file descriptor fd.
	*/

    char getpid_sys[] = "getpid";
	/*
		NAME         top
       		getpid - get process identification
		SYNOPSIS         top
       		#include <unistd.h>
			pid_t getpid(void);
		DESCRIPTION         top
			getpid() returns the process ID (PID) of the calling process.
			(This is often used by routines that generate unique temporary
			filenames.)
	*/

	char getuid_sys[] = "getuid";
	/*
	NAME         top
		getuid - get user identity
	SYNOPSIS         top
		#include <unistd.h>
		uid_t getuid(void);
	DESCRIPTION         top
		getuid() returns the real user ID of the calling process.
	*/

	char getppid_sys[] = "getppid";
	/*
		NAME         top
       		getppid - get process identification
		SYNOPSIS         top
       		#include <unistd.h>
			pid_t getppid(void);
		DESCRIPTION         top
			getppid() returns the process ID of the parent of the calling
			process.  This will be either the ID of the process that created
			this process using fork(), or, if that process has already
			terminated, the ID of the process to which this process has been
			reparented (either init(1) or a "subreaper" process defined via
			the prctl(2) PR_SET_CHILD_SUBREAPER operation).
	*/

	char getgid_sys[] = "getgid";
	/*
	NAME         top
		getgid - get group identity
	SYNOPSIS         top
		#include <unistd.h>
		gid_t getgid(void);
	DESCRIPTION         top
		getgid() returns the real group ID of the calling process.
	*/

	int returnValue;
	int max_size_write = 100;
	int C2S = msgget(key1, 0666 | IPC_CREAT);
	int S2C = msgget(key2, 0666 | IPC_CREAT);
	while(1){
		struct message inputMessage;
		struct message outputMessage;
		// msgget creates a message queue
		// and returns identifier

		// msgrcv to receive message
		msgrcv(C2S, &inputMessage, sizeof(inputMessage), 1, 0);

		// display the message
		printf("Server receives the system call: %s \n", inputMessage.messageText);

		if(strcmp(inputMessage.messageText,write_sys)==0) { 	
			returnValue = write(1,"Write System Call called",24);
		}
		else if(strcmp(inputMessage.messageText,getpid_sys)==0){
			returnValue = getpid();
		}
		else if(strcmp(inputMessage.messageText,getuid_sys)==0){
			returnValue = getuid();
		}
		else if(strcmp(inputMessage.messageText,getppid_sys)==0){
			returnValue = getppid();
		}
		else if(strcmp(inputMessage.messageText,getgid_sys)==0){
			returnValue = getgid();
		}
		else if (strcmp(inputMessage.messageText, "End") == 0){
			printf("End called, Terminating...\n");
			return 0;
		}
		else{
			printf("Invalid System call called!\n");
		}
		outputMessage.messageType = 1;
		sprintf(outputMessage.messageText, "%d", returnValue);
		msgsnd(S2C, &outputMessage, sizeof(outputMessage), 0);
	}
	return 0;
}
