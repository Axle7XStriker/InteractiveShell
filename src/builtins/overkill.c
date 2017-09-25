#include "builtin_func.h"

int overkill_execute(char **args)
{
    int i;
    for (i=0; i<num_bg_process; i++)
    {
        if (bg_proc[i] != NULL)
        {
            if (kill(bg_proc[i]->pid, 9) != 0)
            {
                perror("shell");
            }
            else
            {
                sleep(1);
            }
        }
    }
    num_bg_process = 0;

    return 1;
}