#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h> 
#include<sys/stat.h>
#include<limits.h>
#include <ctype.h>
#define MAX_BUF 200
#define MAXCOM 1000 
#define MAXLIST 100 
#define COMMAND_SIZE 100
#define clear() printf("\033[H\033[J")

int numberOfCommands = 0;
char input_string[COMMAND_SIZE] = "araj";
int flag = 0;
int check_enter = 0;
void init_shell()
{
    system("clear");
	printf("Shell Starting....\n");
	sleep(1);
}

void printDirPrompt(){
    char path[MAX_BUF];
    getcwd(path, MAX_BUF);
    printf("%s>", path);
}

void printDir(){
    char path[MAX_BUF];
    getcwd(path, MAX_BUF);
    printf("%s\n", path);
}

// int notinputTaken(char* input_string){
//     if(fgets(input_string,100,stdin)!=NULL)return 0;
//     return 1;
// }

void listAllFiles(){
    system("ls");
}

void printHistory(){
    int numCommands = 1;

    FILE *in_file = fopen("history.txt", "r");

    struct stat sb;
    stat("history.txt", &sb);

    char *file_contents = malloc(sb.st_size);

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        printf("> %s ", file_contents);
        printf("%d",numCommands);
        printf("\n");
        numCommands++;
    }
    fclose(in_file);
    return;
}

void createDirectory(){
    DIR* dir = opendir("dir");
    if(dir)return;
    if (mkdir("dir", 0777) == -1)
        printf("Error/n");
    else
        // Directory created
    return;
}

void removeDirectory(){
    rmdir("./dir");
    return;
}

int execSimple(char* command){
    if(strcmp(command,"ls") == 0){
        listAllFiles();
    }
    else if(strcmp(command,"ls -l") == 0){
        system("ls -l");
    }
    else if(strcmp(command,"clear") == 0){
        system("clear");
    }
    else if(strcmp(command,"pwd") == 0){
        printDir();
    }
    else if(strcmp(command,"history") == 0){
        printHistory();
    }
    else if(strcmp(command,"exit") == 0){
        ;
    }
    else if(strcmp(command,"mkdir") == 0){
        createDirectory();
    }
    else if(strcmp(command,"rmdir") == 0){
        DIR* dir = opendir("dir");
        if(dir)removeDirectory();
    }
    else{
    	printf("Invalid command\n");
    }
    return 0;
}

void trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return;
}

void main_function(){
	int check = 0;
	FILE *fptr = fopen("history.txt","a");
	while (strcmp(input_string, "exit") != 0){
        input_string[0] = '\0'; // empty the char array
		printDirPrompt();
        scanf("%[^\n]%*c", input_string);
        if(input_string[0] == '\0'){
            printf("NO");
        }
		else{
		trimwhitespace(input_string);	
			fputs(input_string,fptr);
			fputs("\n",fptr);
			fflush(fptr);
			numberOfCommands++;
			flag = execSimple(input_string);
		}
	}
    fclose(fptr);
    fclose(fopen("history.txt","w"));
}

int main(){
    init_shell();
    numberOfCommands = 0;
    main_function();
	return 0;
}
