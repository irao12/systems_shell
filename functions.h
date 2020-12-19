#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char ** pip(char ** arguments, int num_of_args);

char ** redirect_stdin (char** arguments, int num_of_args);

char ** remove_redirect(char** arguments, int loc, int num_of_args);

char ** redirect_stdout (char** arguments, int num_of_args);

void execute_redirect(char** arguments, int loc, int num_of_args);

#endif
