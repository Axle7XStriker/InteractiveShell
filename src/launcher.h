#ifndef headers_and_declarations
#define headers_and_declarations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#ifndef launcher_headers
#define launcher_headers

#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

#include "redirection.h"

extern int num_bg_process;
typedef struct background_process
{
    int pid;
    char cmd[1000];
}background_process;
background_process *bg_proc[1000];

extern int current_running_child_pid;

int launch_cmd(char **, int);

#endif

