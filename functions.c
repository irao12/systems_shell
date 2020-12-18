#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int count_args ( char * line, char delimeter ){
	int counter = 1;
	int i;
  for (i = 0; line[i]; i++){
    if (line[i] == delimeter) 
      counter++;
  }
	return counter;
}

char ** parse_args ( char * line, int args, char *delimeter ){
	char **a = malloc(sizeof(char *) * args + 1);
	char *token, *p;
	int counter = 0;
	p = line;
	while (p){
		token = strsep(&p, " ");
    if (*token != '\0'){
		  a[counter] = token;
      counter++;
    }
    
  }
	a[counter] = NULL;

	return a;
}

char ** pip(char ** arguments, int num_of_args, int* piped){
  int i;
  int loc=0;
  for (i = 0; arguments[i]; i++){
    if (!strcmp(arguments[i], "|")){
      loc = i;
      *piped = 1;
    }
  }
  if (loc){
    int fds[2];
    pipe(fds);
    int f = fork();
    int backup_stdout = STDOUT_FILENO;
    if(!f){
      close(fds[0]);
      dup2(fds[1], STDOUT_FILENO);
      char **first_cmd = malloc(sizeof(char*)*loc + 2);
      for (i = 0; i<loc;i++){
        first_cmd[i] = arguments[i];
      }
      execvp(first_cmd[0], first_cmd);
    }
    close( fds[1] );
    wait(NULL);
    char test[500];  
    dup2(backup_stdout,1);
    //read(fds[0], test, sizeof(test)-1);
    dup2(fds[0],0);
    int j;
    for (j = 0; test[j];j++){
      j=j;
    }
    //int temp = open("temp", O_CREAT|O_RDWR, 0644);
    //write(0, test, j);
    char **new = malloc (sizeof(char*)* num_of_args);
    if (loc){
      for (j = 0; arguments[j+loc+1];j++){
      new[j] = arguments[j+loc+1];
      }
      arguments = new;
    }
  }
  return arguments;
}

char ** remove_redirect(char** arguments, int loc, int num_of_args){
  int i;
  char **new = malloc(sizeof(char *) * loc+1);
  for (i = 0; i<loc;i++){
    if (arguments[i])
    new[i] = arguments[i];
  }
    arguments = new;
    return arguments;
}

char ** redirect (char** arguments, int num_of_args)
{
  int i;
  char** new = arguments;
  for (i = 0; arguments[i]; i++){
    if (!strcmp(arguments[i], ">")){

      int fd = open(arguments[i+1],O_CREAT|O_WRONLY| O_TRUNC , 0644);

      dup2(fd, STDOUT_FILENO);
      
      new = remove_redirect(arguments, i, num_of_args);

    }

    if (!strcmp(arguments[i], ">>")){

      int fd = open(arguments[i+1], O_CREAT|O_RDWR|O_APPEND, 0644);

      dup2(fd, STDOUT_FILENO);

      new = remove_redirect(arguments, i, num_of_args);
    }

    if (!strcmp(arguments[i], "<")){
      int fd = open(arguments[i+1],O_RDONLY);

      int backup_sdin = dup(STDIN_FILENO );

      dup2(fd, STDIN_FILENO);

      new = remove_redirect(arguments, i, num_of_args);
    }
  }
  return new;
}


//removes newline from fgets
void remover(char* buffer)
{
  char *returnval;
  returnval = strchr(buffer,'\n');
  if (returnval != NULL){
    *returnval='\0';
  }
}


int count_cmds(char * cmd){
  int counter = 1;
  int i;
  for (i=1;i<strlen(cmd);i++){
    if (cmd[i]==';'){
      counter++;
    }
        
  }
  return counter;
}

char ** parse_cmds (char* cmd, int num){
  char **a = malloc(sizeof(char *) * num + 2);
	char *token, *p;
	int counter = 0;
	p = cmd;
	while (p){
		token = strsep(&p, ";"); 
		a[counter] = token;
		counter++;
	}
	a[counter] = NULL;

	return a;
}
