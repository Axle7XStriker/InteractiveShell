#include "launcher.h"

void SIGCHLD_signal_handler(int sig)
{
    int status, wpid;
    wpid = waitpid(-1, &status, WNOHANG);
    int proc_no = 0;
    while (proc_no < num_bg_process)
    {
        if ((bg_proc[proc_no] == NULL) || ((bg_proc[proc_no]->pid) != wpid))
            proc_no++;
        else 
            break;
    }
    if (wpid > 0)
    {
        fprintf(stderr, "\n[%d]+ %s\tDone \texit status: %d\n", wpid, bg_proc[proc_no]->cmd, status);
        bg_proc[proc_no] = NULL;
    }
}

void SIGTSTP_signal_handler(int sig)
{
    if (kill(current_running_child_pid, 19) != 0)
    {
        perror("shell");
    }
    bg_proc[num_bg_process] = (background_process *)malloc(sizeof(background_process));
    bg_proc[num_bg_process] -> pid = current_running_child_pid;
    char proc_addr[100] = "/proc/";
    char spid[10];
    sprintf(spid, "%d", current_running_child_pid);
    strcat(proc_addr, spid);
    strcat(proc_addr, "/cmdline");
    int read_fd = open(proc_addr, O_RDONLY); 
    char cmd_name[1000];
    read(read_fd, cmd_name, 1000);
    strcpy(bg_proc[num_bg_process]->cmd, cmd_name);
    num_bg_process++;
    printf("\n[%d]+ Stopped \t%s\n", num_bg_process, cmd_name);
}

int launch_cmd(char **cmd, int bg)
{
    int pid, status;
    signal(SIGCHLD, SIGCHLD_signal_handler);
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
            current_running_child_pid = pid;
            signal(SIGTSTP, SIGTSTP_signal_handler);
            //do
            //{
                waitpid(pid, &status, WUNTRACED);
            //}while(!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        else
        {
            bg_proc[num_bg_process] = (background_process *)malloc(sizeof(background_process));
            bg_proc[num_bg_process] -> pid = pid;
            strcpy(bg_proc[num_bg_process] -> cmd, cmd[0]);
            num_bg_process++;
            printf("[%d]\n", pid);
        }
    }
    return 1;
}