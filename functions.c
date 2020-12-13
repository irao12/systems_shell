#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int count_args ( char * line ){
	int counter = 1;
	int i;
  for (i = 0; line[i]; i++){
    if (line[i] == ' ') 
      counter++;
  }
	return counter;
}

char ** parse_args ( char * line, int args ){
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

