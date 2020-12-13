#include <sys/stat.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int count_args( char * line );

char ** parse_args ( char * line, int args );

void remover(char* buffer);

int count_cmds(char * cmd);

char ** parse_cmds (char* cmd, int num);

char * remove_spaces(char *s);
#endif
