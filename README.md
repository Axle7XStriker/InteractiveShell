# InteractiveShell
* An interactive user defined shell in C

# Complile 
* Complile using "make"
* Recompile : delete all .o file by make clean and then again do make. 

# Run
* Run using ./shell

# Features
## General
* Works almost like normal shell
* Coloured prompt 
* Keeps the directory where the shell is run, as home directory and shows the path of the     current directory relative to that home directory
* Every command is run in new forked process
* Error Handling



## Background Processes

* Commands which have '&' appended, run in background
* When background process exits, shell display a message with its exit status



## Implemented Built-in-Commands

These commands are implemented as a part of shell
* cd  (Also "cd -" )
* echo
* pwd
* ls (ls -l, ls -al, ls -a, ls -la with directory name )
* setenv var [value] 
* unsetenv var 
* jobs
* kjob <jobNumber> <signalNumber> 
* fg <jobNumber>
* bg <jobNumber>
* overkill
* quit
* CTRL-Z
* CTRL-C
* pinfo
  * It returns process related information like pid, process status, memory, etc




## For Assignment 3


### Specification 1: Foreground and background processes
1. If the background process exits then the shell will display the appropriate message to      

    the user and for foreground process shell will wait and regain its control once the process exist.

   ​

### Specification 2: Implement input-output redirection functionality

1. Output of running one (or more) commands can be redirected to a file. 



### Specification 3: Implement command redirection using pipes

1. Program can handle any number of pipes.

   ​

### Specification 4: Implement i/o redirection + pipes redirection

* Use Case : Example => cat < in.txt | wc -l > lines.txt



### Specification 5: User-defined commands

* listed in Builtins Command





### BONUS

1. If the background process exits then the shell must display the appropriate message to the user.	
2. nightswatch (interrupt,dirty) 
  * Non blocking user input method if User press 'q' then exit 
  * [ nightwatch -n t interrupt] It  print the number of times the CPU(s) has(ve) been interrupted by the keyboard   controller (i8042 with IRQ 1) t times on screen .
  * [ nightwatch -n t dirty] It prints the total amount of memory, in kilobytes, waiting to be written back to the disk on every t seconds.



# File Structure

#### Modularity in Code 
## src directory
* Makefile  
  * Compile and link all file and made a executable file ./shell to run shell
* main.c
  * Main file where shell is running and prompt is displaying
* read_and_parse.c 
  * Read user command and parse it i.e tokenise it.
* check_background_process.c 
  * Check if a process  to  be run in background
* launcher.c 
  * Launch the prepared execute instruction
* execute.c 
  * Preparing to execute the instruction
* filename.h 
  * containing  respective libraries nedded
* redirection.h
  * containing respective libraries nedded
* redirection.c
  * Execute redirection command
* piping.h
  * containing  respective libraries nedded
* piping.c
  * Execute and handle number of pipes



##### builtins directory [Name of file showing function it performs]
```c
* cd.c
* echo.c
* ls.c
* exit_quit.c
* pinfo.c
* pwd.c
* nightswatch.c
* setenv_unsetenv.c
* jobs.c
* fg_bg.c
* kjob.c
* overkill.c
* builtin_func.h
```


# Devlopers
```c
Gulshan Kumar  Aman Bansal
```



# Licensing
Copyright (C)  - All Rights Reserved
Unauthorized copying of this file, via any medium is strictly prohibited
