#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void cd(char * s){
  int val = chdir(s);
  if (val == -1)
    printf("%s\n",strerror(errno));

/*
  if (val ==0)
    printf("Directory changed \n");
*/

}
