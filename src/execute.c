#include "execute.h"

int execute_cmd(char **cmd, int bg)
{
    int i;
    if (cmd == NULL || cmd[0] == NULL)
        return 1;
        
    for (i=0; builtins[i] != NULL; i++)
    {
        if (strcmp(cmd[0], builtins[i]) == 0)
        {
            //printf("here\n");
            return (*builtin_functions[i])(cmd);
        }
    }

    return launch_cmd(cmd, bg);
}