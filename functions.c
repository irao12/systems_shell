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

char ** remove_redirect(char** arguments, int loc, int num_of_args){
  char **new = malloc(sizeof(char *) * loc) ;
  int i;
  char *redir_char = arguments[loc];


  if (!strcmp(redir_char, ">>") || !strcmp(redir_char, ">"))
  for (i = 0; i<loc;i++){
    new[i] = arguments[i];
  }

  if (!strcmp(redir_char, "<")) 
  for (i = 0; i<loc; i++){
    new[i] = arguments[i];
  }
    arguments = new;
    return new;



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
