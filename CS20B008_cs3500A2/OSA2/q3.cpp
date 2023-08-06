// C program to demonstrate use of fork() and pipe()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int fd[2]; 
pid_t p;

void childProcess(){
    close(fd[0]); 
    char input_str[100];
    printf("Enter the input string:\n");
    scanf("%[^\n]%*c", input_str);
    write(fd[1], input_str, 100);
    close(fd[1]);
}

void parentProcess(){
    char ret_str[100];

    close(fd[1]);
    wait(NULL);
    
    read(fd[0], ret_str, 100);
    printf("the returned string is:\n%s\n",ret_str);
    close(fd[0]);
}

int main()
{   
	if (pipe(fd) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	p = fork();

	if (p < 0) {
		fprintf(stderr, "fork Failed");
		return 1;
	}
    // child process
	else if(p==0){
		childProcess();
	}
	// Parent process
	else if (p > 0) {
		parentProcess();
	}
	return 0;
}