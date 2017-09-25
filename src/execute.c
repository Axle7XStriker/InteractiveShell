#include "execute.h"
#include "piping.h"
int execute_cmd(char **cmd, int bg)
{
    int i;
    if (cmd == NULL || cmd[0] == NULL)
        return 1;

    int flag1=0,flag2=0;
    for(i=0;cmd[i]!=NULL;i++)
    {
        if(!(strncmp(cmd[i], "|" ,1)))
        {
            flag1=1;
            long int st = (long int) piping(cmd);   //ssize_t aka lon int i.e typecast to avoid warning
            return st;
            
        }
    }

    for(i=0;cmd[i]!=NULL;i++)
    {
        if(strncmp(cmd[i], ">" ,1)==0 || strncmp(cmd[i], "<" ,1)==0)
        {
            flag2=1;
        }
    }

    if (flag2 || flag1)
    {
        return launch_cmd(cmd,bg);
    }   

    for (i=0; builtins[i] != NULL; i++)
    {
        if (strcmp(cmd[0], builtins[i]) == 0)
        {
            return (*builtin_functions[i])(cmd);
        }
    }

    return launch_cmd(cmd, bg);
}