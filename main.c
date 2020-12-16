
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
    int backup_stdout = dup(STDOUT_FILENO);
    getcwd(cwd, sizeof(cwd));
    printf("%s $ ", cwd);
    fgets(line, sizeof(line), stdin);
    remover(line);

    int num_of_cmds = count_cmds(line);
    char **cmds = parse_cmds(line, num_of_cmds);
    //printf("%s\n",cmds[0]);
    //printf("%s\n",cmds[1]);

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
        /*if (redirect){
          int fd = open(arguments[j+1], O_CREAT, O_WRONLY, 0777);
          int backup_stdout = dup( STDOUT_FILENO );
          dup2(fd, STDOUT_FILENO);
          execlp(arguments[0], arguments);
          dup2(backup_stdout, STDOUT_FILENO);
        }
        */
        
        arguments = redirect(arguments, num_of_args);
        execvp(arguments[0], arguments);
        /*int num_of_eps = count_args(cmds[i], '|');
        pipe_execute(parse_args(cmds[i], num_of_eps, "|"), num_of_eps);*/

        return 0;

      }
      int pid = waitpid(-1,&status,0);
    }
    dup2(1, backup_stdout);
    free(arguments);
    int pid = waitpid(-1,&status,0);
  }
  return 0;
}
