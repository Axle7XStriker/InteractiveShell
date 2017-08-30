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
#define sz 123
#define max_sz 1234

#endif

extern char home[sz];
extern struct passwd *pws;

int ls_execute (char **);
int cd_execute (char **);
int pwd_execute (char **);
int echo_execute (char **);
int pinfo_execute (char **);
int nightswatch (char **);
int exit_execute (char **);

extern char *builtins[];
extern int (*builtin_functions[]) (char **);
