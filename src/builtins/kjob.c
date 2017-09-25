#include "builtin_func.h"

int kjob_execute(char **args)
{
    int len = 0;
    while (args[len++] != NULL);
    if (len != 4)
    {
        fprintf(stderr, "Usage: kjob <job number> <signal number>\n");
        return 1;
    }
    int job_no = atoi(args[1]);
    int signal_no = atoi(args[2]);
    if (bg_proc[job_no-1] != NULL)
    {
        if (kill(bg_proc[job_no-1]->pid, signal_no) != 0)
        {
            perror("shell");
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "shell: No job with the given job number exist\n");
    }

    return 1;
}