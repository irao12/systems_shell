#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

char ** pip(char ** arguments, int num_of_args){
  int i;
  int loc=0;
  for (i = 0; arguments[i]; i++){
    if (!strcmp(arguments[i], "|")){
      loc = i;
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
    dup2(fds[0],0);
    int j;
    for (j = 0; test[j];j++){
      j=j;
    }
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

char ** redirect_stdin (char** arguments, int num_of_args){
  int i;
  for (i = 0; arguments[i]; i++){
    if (!strcmp(arguments[i], "<")){
      int fd = open(arguments[i+1],O_RDONLY);
      dup2(fd, STDIN_FILENO);

      char ** new = malloc(sizeof(char*)*(i+3));
      int j;
      for (j = 0; j < i; j++){
        new[j]=arguments[j];
      }
      for (j = i; arguments[j+2]; j++){
        new[j]=arguments[j+2];
      }
      arguments = new;
    }
  }
  return arguments;
}

char ** remove_redirect(char** arguments, int loc, int num_of_args){
  int i;
  char **new = malloc(sizeof(char *) * (loc+1));
  for (i = 0; i<loc;i++){
    new[i] = arguments[i];
  }
    new[i] = NULL;
    arguments = new;
    return arguments;
}

char ** redirect_stdout (char** arguments, int num_of_args)
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
  }
  return new;
}

