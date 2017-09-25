#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include "redirection.h"


int piping (char ** args)
{

    int pipe1[2], pipe2[2];
    int i=0,j=0,k=0,flag=0 ,count1=0;

    pid_t pid;
    char *sym[100];
    char ** redrr;
    int itr=0;
    for(itr=0;args[itr]!=NULL;itr++)
    {
        if(strncmp(args[itr], "|",1)==0)
        {
            count1++;
        }
    }
    count1++;

    for(j=0;args[j]!=NULL &&  flag!=1;)
    {

        k = 0;
        while((strncmp(args[j],"|",1)!=0))
        {

            sym[k++]=args[j++];
            if(args[j]== NULL)
            {
                flag = 1;
                break;
            }
        }
        j++;
        sym[k] = NULL;

        if (i%2)
        {
            pipe(pipe1);
        }
        else 
        {
            pipe(pipe2);
        }
        pid = fork();
        if(pid < 0)
        {
            perror("Process is not forked");
        }
        if (pid == 0)
        {
            
            redrr= redirect(sym);
            if (!i)
            {
                dup2(pipe2[1],1);

            }
            else if (i==(count1-1) && count1%2 ==0)
            {
                dup2(pipe2[0],0);
            }
            else if(i==(count1 -1) && count1%2==1)
            {
                dup2(pipe1[0],0);
            }
            else  if(i%2==1)
            {
                 dup2(pipe2[0],0);
                 dup2(pipe1[1],1);
            }
            else if (i%2==0)
            {
                dup2(pipe1[0],0);
                dup2(pipe2[1],1);
            }
            if (execvp(redrr[0],redrr) < 0 )
            {
                kill(getpid(),SIGTERM);
            }
        }
        if(!i)
        {
            close(pipe2[1]);
        }
        else if(i==(count1-1) && (i%2)==1)
        {
            close(pipe1[0]);
        }
        else if(i==(count1-1) && (i%2)==0)
        {
            close(pipe2[0]);
        }
        else if((i%2)==1)
        {
           close(pipe2[0]);
          close(pipe1[1]); 
        }
        else if (i%2==0)
        {
            close(pipe1[0]);
            close(pipe2[1]);
        }
        waitpid(pid,NULL,0);
        i++;
    }
    return 1;
}
