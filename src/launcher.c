#include "launcher.h"

void signal_handler(int sig)
{
    int status, wpid;
    wpid = waitpid(-1, &status, WNOHANG);
    if (wpid > 0)
    printf("[%d]+ \tDone \texit status: %d", wpid, status);
    BACKGROUND_PROCESS_COUNT--;
}

int launch_cmd(char **cmd, int bg)
{
    int pid, wpid, status;
    signal(SIGCHLD, signal_handler);
    pid = fork();
    
    if(pid == 0)
    {
        
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
                wpid = waitpid(pid, &status, WUNTRACED);
            }while(!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        else
        {
            BACKGROUND_PROCESS_COUNT++;
            printf("[%d] %d\n", BACKGROUND_PROCESS_COUNT, pid);
        }
    }
    return 1;
}