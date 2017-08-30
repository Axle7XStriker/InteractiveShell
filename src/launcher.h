#ifndef headers_and_declarations
#define headers_and_declarations

#include <stdio.h>
#include <stdlib.h>

int BACKGROUND_PROCESS_COUNT = 0;

#endif

#ifndef launcher_headers
#define launcher_headers

#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int launch_cmd(char **, int);

#endif

