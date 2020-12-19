# PIESH
by Mohammad Hamzah, Ivan Rao, and Gene Ye 
TNPG: team bakers

# Features:
* Displays the current directory 
* Reads commands and parses it to separate the command from its arguments
* Forks and execs command
* Reads multiple commands on a single line using ;
* Redirects stdout and stdin using > and < respectively
* Allows for piping using |

# Attempted:

# Bugs:
* Happens rarely but memory allocation might not work and there will be a sysmalloc error.

# Files & Function Headers:

### main.c
  * Runs the program and creates the shell environment for the user. 
  * Checks all the commands entered, separating them as needed and then forking and executing the commands.
