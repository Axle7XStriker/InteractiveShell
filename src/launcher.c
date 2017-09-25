#include "launcher.h"

void signal_handler(int sig)
{
    int status, wpid;
    wpid = waitpid(-1, &status, WNOHANG);
    if (wpid > 0)
    fprintf(stderr, "\n[%d]+ \tDone \texit status: %d", wpid, status);
}

int launch_cmd(char **cmd, int bg)
{
    int pid, status;
    signal(SIGCHLD, signal_handler);
    pid = fork();
    
    if(pid == 0)
    {
    	
        cmd=redirect(cmd);
        if (execvp(cmd[0], cmd) == -1)
            perror("shell");
        exit(EXIT_FAILURE);
        
    }
    else if (pid < 0)
    {
        perror("shell");
    }
    else
    {
        if (!bg)
        {
            do
            {
                waitpid(pid, &status, WUNTRACED);
            }while(!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        else
        {
            printf("[%d]\n", pid);
        }
    }
    return 1;
}