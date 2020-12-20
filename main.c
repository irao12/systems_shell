#include "parse.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

  int i;
  char line[100];
  int status;
  char cwd[100];
  int go = 1;
  int backup_stdin = dup(STDIN_FILENO);
  int backup_stdout = dup(STDOUT_FILENO);
  while (go)
  {
    getcwd(cwd, sizeof(cwd));
    printf("\n%s $ ", cwd);
    fgets(line, sizeof(line), stdin);
    remover(line);

    int num_of_cmds = count_cmds(line);
    char **cmds = parse_cmds(line, num_of_cmds);
  
  

    char **arguments;
    int num_of_args;

    for (i = 0; cmds[i]; i++)
    {
      int j;
      num_of_args = count_args(cmds[i]);
      

      arguments = parse_args(cmds[i], num_of_args);
      printf("\n");

      if (!strcmp(arguments[0], "cd"))
      {
        if (num_of_args > 1){
          int val = chdir(arguments[1]);
          if (val == -1)
          printf("%s\n",strerror(errno));
        }
          break; 
      }
      if (!strcmp(arguments[0], "exit"))
      { 
        exit(0);
      }

      int num = fork();
      
      if (!num)
      {        

        arguments = pip(arguments, num_of_args);

        arguments = redirect_stdin(arguments, num_of_args);

        arguments = redirect_stdout(arguments,num_of_args);

        execvp(arguments[0], arguments);
        printf("command not found\n");
        return 0;
      }
    
      int pid = waitpid(-1,&status,0);
    }
    dup2(backup_stdin, 0);
    dup2(backup_stdout, 1);
    free(arguments);
  }
  return 0;
}
