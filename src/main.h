#ifndef headers_and_declarations
#define headers_and_declarations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#endif

//#include "builtin_func.h"
#include "read_and_parse.h"
#include "check_background_process.h"
#include "execute.h"

const char *TOKEN_DELIMITER = " \t\n\r\a";
const char *CMD_DELIMITER = ";";

char home[sz];
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