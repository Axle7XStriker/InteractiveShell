#include "builtin_func.h"
char proc_status[12];
int jobs_execute(char ** args)
{
    int i;
    for (i=0; i<num_bg_process; i++)
    {
        
        if (bg_proc[i] != NULL)
        {
            // char * line = NULL;
            // size_t len = 0;
            // ssize_t read;
            // char result[20];
            // int pid= (bg_proc[i]->pid);
            // sprintf(result,"%d" ,pid);
            // char str[100];
            // strcat(str,"/proc/");
            // strcat(str, result);
            // strcat(str,"/status");
            // FILE * fp = fopen(str, "r");
            // if (fp == NULL)
            // {
            //     perror("error");
            //     return 0;
            // }
            // while ((read = getline(&line, &len, fp)) != -1) 
            // {
            //     if(line[0]=='S' && line[1]=='t' && line[2]=='a' && line[3]=='t' && line[4]=='e')
            //     {
                     
            //          	int k=0;
            //          	for(k=10;k<=17;k++)
            //          	{
            //          		proc_status[k-10]=line[k];
            //          	}
            //             proc_status[9]='\0';
            //     }	
            // }
        
            printf("[%d] \t%s[%d]\n", i+1,bg_proc[i]->cmd, bg_proc[i]->pid);
            // fclose(fp);
            // if (line)
            // {
            //     free(line);
            // }

        }
    }
    return 1;
}