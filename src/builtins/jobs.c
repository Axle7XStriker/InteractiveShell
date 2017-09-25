#include "builtin_func.h"

int jobs_execute(char ** args)
{
    int i;
    for (i=0; i<num_bg_process; i++)
    {
        char proc_status[1000];
        if (bg_proc[i] != NULL)
        {
        /*    char * line = NULL;
            size_t len = 0;
            ssize_t read;
            char result[20];
            int pid= (bg_proc[i]->pid);
            sprintf(result,"%d" ,pid);
            char str[100];
            strcat(str,"/proc/");
            strcat(str, result);
            strcat(str,"/status");
            FILE * fp = fopen(str, "r");
            if (fp == NULL)
            {
                perror("error");
                return 0;
            }
            while ((read = getline(&line, &len, fp)) != -1) 
            {
                if(line[0]=='S' && line[1]=='t' && line[2]=='a' && line[3]=='t' && line[4]=='e')
                {
                    //printf("%s\n", line);
                    int i;
                    for (i=10; i<18; i++)
                        proc_status[i-10] = line[i];
                    proc_status[i] = '\0';
                    break;
                }	
            }
        
            fclose(fp);
            if (line)
                free(line);
        */    printf("[%d] \t%s[%d]\n", i+1, bg_proc[i]->cmd, bg_proc[i]->pid);
        }
    }
    return 1;
}