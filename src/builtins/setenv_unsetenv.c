#include "builtin_func.h"

int setenv_execute (char **args)
{
    int len = 0;
    while (args[len] != NULL)
    {
        //printf("%s\n", args[len]);
        len++;
    }
    if (len == 1 || len > 3)
    {
        fprintf(stderr, "Usage: setenv var [value]\n");
        return 1;
    }
    if (args[2])
    {
        if (setenv(args[1], args[2], 1) == 0)
        {
            //printf("%s\n", getenv(args[1]));
            return 1;
        }
        else
        {
            perror("shell");
            //printf("there\n");
            return 1;
        }
    }
    else
    {
        char arg[] = "";
        if (setenv(args[1], arg, 1) == 0)
            return 1;
        else
            return 0;
    }
}


int unsetenv_execute (char **args)
{
    int len = 0;
    while (args[len] != NULL)
    {
        //printf("%s\n", args[len]);
        len++;
    }
    if (len == 1 || len > 2)
    {
        fprintf(stderr, "Usage: unsetenv var [value]\n");
        return 1;
    }
    if (unsetenv(args[1]) == 0)
        return 1;
    else
    {
        perror("shell");
        return 1;  
    }
}