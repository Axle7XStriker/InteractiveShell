#include "builtin_func.h"

int fg_execute(char ** args)
{

    int len = 0;
    while (args[len++] != NULL);
    if (len != 3)
    {
        fprintf(stderr, "Usage: fg <job number>\n");
        return 1;
	}
	int job_no = atoi(args[1]);
	if (bg_proc[job_no-1] != NULL)
	{
		if (kill(bg_proc[job_no-1]->pid, 18) != 0)
		{
			perror("shell");
			return 1;
		}
		else
		{
			int pid = (bg_proc[job_no-1] -> pid), status;
			bg_proc[job_no-1] = NULL;
			waitpid(pid, &status, WUNTRACED);
		}
	}
	else
	{
		fprintf(stderr, "shell: No job with the given job number exist\n");
	}
	return 1;
}

int bg_execute(char ** args)
{

    int len = 0;
    while (args[len++] != NULL);
    if (len != 3)
    {
        fprintf(stderr, "Usage: bg <job number>\n");
        return 1;
	}
	int job_no = atoi(args[1]);
	if (bg_proc[job_no-1] != NULL)
	{
		if (kill(bg_proc[job_no-1]->pid, 18) != 0)
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