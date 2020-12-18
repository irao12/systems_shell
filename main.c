
#include "functions.h"
#include "cd.h"
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
  char line[50];
  int status;
  char cwd[50];
  int go = 1;
  while (go)
  {
    int backup_stdin = dup(STDIN_FILENO);
    int backup_stdout = dup(STDOUT_FILENO);
    getcwd(cwd, sizeof(cwd));
    printf("%s $ ", cwd);
    fgets(line, sizeof(line), stdin);
    remover(line);

    int num_of_cmds = count_cmds(line);
    char **cmds = parse_cmds(line, num_of_cmds);
  
  

    char **arguments;
    int num_of_args;

    for (i = 0; i < num_of_cmds; i++)
    {
      int j;
      num_of_args = count_args(cmds[i], ' ');
      

      arguments = parse_args(cmds[i], num_of_args, " ");


      if (!strcmp(arguments[0], "cd"))
      {
        if (num_of_args > 1)
          cd(arguments[1]);
      }
      if (!strcmp(arguments[0], "exit"))
      {
        go = 0;
        break;
      }

      int num = fork();
      
      if (!num)
      {        
        dup2(backup_stdout,1);
        int piped = 0;
        arguments = pip(arguments, num_of_args, &piped);
        //int fd = open("temp", O_RDONLY);
        //dup2(fd, 0);
        arguments = redirect(arguments, num_of_args);

        execvp(arguments[0], arguments);

        return 0;

      }
      /*
      else
      {

        



      }
      */
      int pid = waitpid(-1,&status,0);
    }


    dup2(backup_stdout,1);
    free(arguments);
    int pid = waitpid(-1,&status,0);
  }
  return 0;
}
