#ifndef headers_and_declarations
#define headers_and_declarations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <grp.h>
#include <sys/select.h>
#include <termios.h>

char* read_cmd();
char** parse_cmd(char *, const char *);
char ** redirect(char** args);
#endif

//#include "builtin_func.h"
#include "read_and_parse.h"
#include "check_background_process.h"
#include "execute.h"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

const char *TOKEN_DELIMITER = " \t\n\r\a";
const char *CMD_DELIMITER = ";";

char home[sz];
char previous[sz];
char current[sz];
char linklist[sz];
struct passwd *pws;


char *builtins[] = {"ls","cd", "pwd", "echo", "pinfo", "nightswatch", "exit", NULL};
int (*builtin_functions[]) (char **) = {
                                            &ls_execute, 
                                            &cd_execute, 
                                            &pwd_execute, 
                                            &echo_execute, 
                                            &pinfo_execute, 
                                            &nightswatch, 
                                            &exit_execute
                                        };