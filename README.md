# PIESH
by Mohammad Hamzah, Ivan Rao, and Gene Ye\
TNPG: team bakers

# Features:
* Displays the current directory 
* Reads commands and parses it to separate the command from its arguments
* Forks and execs command
* Reads multiple commands on a single line using ;
* Redirects stdout and stdin using > and < respectively
* Allows for piping using |

**All commands should have be valid and have a single space to avoid any potential errors**

# Attempted but Failed:
* None so far

# Bugs:
* Will get a segmentation fault if only spaces are entered as a command
* Having multiple ;'s next to each other will result in a segmentation fault
* Redirecting stdin with a file that does not exists will break the program and force you
  to exit manually
* Shell will return a segmentation fault if the command line inputted is over 100
  chars
# Limitations:
* Must pipe before redirection in order for the shell to work.
       ex: ls | wc > foo will work but
           ls < foo | wc will not work     
* Only pipe once per command
* "exit" command should be run by itself

# Files & Function Headers:

### main.c
 * Runs the program and creates the shell environment for the user. 
 * Checks all the commands entered, separating them as needed and then forking and executing the commands.

### parse.c
 * Handles the parsing of multiple commands as well as the arguments within each unique command.
 
 ```
    /*========== int count_cmds() ==========
    Inputs: char * cmd_line
    Returns: Number of unique commands in the input "cmd_line"
    
    Goes through the line and finds the number of unique commands separated by a ";"
    Minimum amount of commands is 1.
    The number of commands is 1 more than the number of ";".
    ====================*/
    
    /*========== char** parse_cmds() ==========
    
    Inputs: char* cmd, int num
    Returns: An array of strings with each index in the array containing a unique command
    
    Goes through the input and puts each command into its own index in an array. Uses "num"
    to check how much memory to allocate for the array
    ====================*/
    
    /*========== int count_args() ==========
    Inputs: char * line
    Returns: number of arguments in the line
    
    Goes through the line and finds the number of arguments separated by a " " or a space.
    The number of arguments is 1 more than the number of spaces.
    ====================*/
    
    /*========== int parse_args() ==========
    Inputs: char * line, int num
    Returns: An array of strings where each entry is an argument separated by a space.
    
    Goes through the line and puts each argument into its own index in an array. Uses "num"
    to check much memory to allocate for the array.
    ====================*/
    
    
    /*========== void remover() ==========
    Inputs: char* buffer
    Returns: void
    
    removes newline characters from the buffer
    ====================*/
    
```    
 
#### parse.h
 * Header file for parse.c
 
### functions.c
 * Handles the arguments and files to allow for redirection and piping 
 
 ```
 
    /*========== char ** pip() ==========
    Inputs: char ** arguments, int num_of_args
    Returns: array of strings with each index containing the separate commands taken from
    the input without the "|" and the first command so that the command can be executed.
    
    Implements piping between commands. The output of one command will be used as input for
    the other. num_of_args is used for memory allocation.
    
    ====================*/
    
    /*========== char ** redirect_stdin() ==========
    Inputs: char ** arguments, int num_of_args
    Returns: array of strings with each index containing the separate arguments taken from 
    the input without the "<" and the file name after the "<" so that the command can be executed.
    
    Redirects input using "<". The function looks through char** arguments and sees if "<" is 
    present. The file name after "<" will replace stdin and the function returns an array
    that can be checked for redirection or be exectued. num_of_args is used for 
    memory allocation. 

    ====================*/
    
    /*========== char ** remove_redirect() ==========
    Inputs: char ** arguments, int loc, int num_of_args
    Returns: array of strings without the redirection symbols and the file name in them
    
    Removes the redirection symbols from char** arguments found at index "loc". num_of_args 
    is used for memory allocation.
    
    ====================*/
    
    /*========== char ** redirect_stdout() ==========
    Inputs: char ** arguments, int num_of_args
    Returns: array of strings with each index containing the separate arguments taken from
    the input without the ">" or ">>", and without the filename after the redirection symbol 
    so that the command can be executed.
    
    Redirects output using ">" or ">>". The function looks through char** arguments and if 
    ">" or ">>" is present. If ">" is present and the command is executed, it will overwrite
    a file with the contents of executions.  If ">>" is present and the command is executed, 
    the contents of execution will be appended to the file. num_of_args is used for memory allocation. 
    
    ====================*/
```
#### functions.h
* Header file for functions.c

