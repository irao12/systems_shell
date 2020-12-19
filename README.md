# PIESH
by Mohammad Hamzah, Ivan Rao, and Gene Ye 
TNPG: team bakers

# Features:
* Displays the current directory 
* Reads commands and parses it to separate the command from its arguments
* Forks and execs command
* Reads multiple commands on a single line using ;
* Redirects stdout and stdin using > and < respectively
* Allows for piping using | (only one pipe)

**All commands should have be valid and have a single space to avoid any potential errors**

# Attempted:

# Bugs:
* Happens rarely but memory allocation might not work and there will be a sysmalloc error.

# Files & Function Headers:

### main.c
 * Runs the program and creates the shell environment for the user. 
 * Checks all the commands entered, separating them as needed and then forking and executing the commands.
  
### cd.c
 * cd function that allows the user to traverse directories.
 
 ```
    === void cd() ===
    Inputs: char * s
    Returns: Nothing
    
    Changes the directory to whatever the user specifies.
 ```
#### cd.h
 * Header file for cd.c
 
### parse.c
 * Handles the parsing of multiple commands as well as the arguments within each unique command.
 
 ```
    === int count_cmds() ===
    Inputs: char * cmd_line
    Returns: Number of unique commands in the input "cmd_line"
    
    Goes through the input and finds the number of unique commands separated by a ";"
    Minimum amount of commands is 1.
    === char** parse_cmds() ===
    
    Inputs: char* cmd, int num
    Returns: An array of strings with each index in the array containing a unique command
    
    Goes through the input and puts each command into its own index in the array. Uses "num" to check how much memory to allocate for the array
    
    
```    
 
#### parse.h
 * Header file for parse.c
 
### functions.c
 
