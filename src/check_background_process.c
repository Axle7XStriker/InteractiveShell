#include "check_background_process.h"

int is_background_process(char **cmd)
{
    if (cmd == NULL || cmd[0] == NULL)
        return 0;
    int i, j;
    int l = strlen(cmd[0]);
    if (cmd[0][l-1] == '&')
    {
        cmd[0][l-1] = '\0';
        return 1;
    }
    for (i=1; cmd[i] != NULL; i++)
    {
        if (strcmp(cmd[i], "&") == 0)
        {
            cmd[i] = NULL;
            return 1;
        }
        for (j=0; cmd[i][j] != '\0'; j++)
        {
            if (cmd[i][j] == '&')
            {
                //cmd[i][j] = cmd[i][j+1];   
                cmd[i][j] = '\0';
                return 1;
            }
        } 
    }
    return 0;
}