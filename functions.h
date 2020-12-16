#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int count_args( char * line, char delimeter );

char ** parse_args ( char * line, int args, char *delimeter );

void remover(char* buffer);

int count_cmds(char * cmd);

char ** parse_cmds (char* cmd, int num);

char * remove_spaces(char *s);

char** redirect (char** arguments, int num_of_args);
#endif
