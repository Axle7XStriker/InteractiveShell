#ifndef headers_and_declarations
#define headers_and_declarations

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#endif

#ifndef BUILTINS
#define BUILTINS

#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <sys/select.h>
#include <termios.h>
#define sz 123
#define max_sz 1234

#endif

#include "../launcher.h"

extern char home[sz];
extern char previous[sz];
extern char current[sz];
extern char linklist[sz];
extern struct passwd *pws;

//extern int num_bg_process;
//extern struct background_process *bg_proc[1000];

int ls_execute (char **);
int cd_execute (char **);
int pwd_execute (char **);
int echo_execute (char **);
int pinfo_execute (char **);
int nightswatch (char **);
int exit_execute (char **);
int quit_execute (char **);
int setenv_execute (char **);
int unsetenv_execute (char **);
int jobs_execute(char **);
int kjob_execute(char **);
int fg_execute(char **);
int bg_execute(char **);
int overkill_execute(char **);

extern char *builtins[];
extern int (*builtin_functions[]) (char **);
