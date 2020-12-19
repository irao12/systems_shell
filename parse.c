#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int count_cmds(char * cmd_line){
  int counter = 1;
  int i;
  for (i=1;i<strlen(cmd_line);i++){
    if (cmd_line[i]==';'){
      counter++;
    }
        
  }
  return counter;
}

char ** parse_cmds (char* cmd, int num){
  char **a = malloc(sizeof(char *) * (num + 1));
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
	char **a = malloc(sizeof(char *) * (args + 1));
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
