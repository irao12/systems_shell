#ifndef PARSE_H
#define PARSE_H

int count_cmds(char * cmd_line);

char ** parse_cmds (char* cmd, int num);

int count_args ( char * line, char delimeter );

char ** parse_args ( char * line, int args, char *delimeter );

void remover(char* buffer);

#endif
