#include "builtin_func.h"
#include <string.h>

void nightwatch_execute()
{
	char * flush = malloc(sizeof(char)*max_sz);
	char * dest_status = malloc(sizeof(char)*max_sz);
	char * dest = malloc(sizeof(char)*max_sz);
	strcpy(dest, "/proc/");
	strcpy(dest_status, dest);
	strcat(dest_status, "/meminfo");
	readlink(dest, flush, max_sz-1);
	printf("Path: %s\n",flush);

	FILE * fp = fopen(dest_status, "r");
	int st = 0;
	size_t buff = max_sz;
	do
	{
	    if(getline(&dest, &buff, fp)==-1)
	    {	
	        perror("");
	        break;
	    }
	    st++;
	    if(st==17)
	      printf("%s",dest);
	}while(st -18<0);
	fclose(fp);
	free(dest);
	free(dest_status);
	free(flush);
}

int nightswatch(char **arg)
{
    int t = atoi(arg[2]);
    char ch = 'a';
    while (1)
    {   printf("Enter y to see it or q to exit\n");
        scanf("%c",&ch);
        getchar();
        if(ch=='q')
            break;
        nightwatch_execute();
        sleep(t);
    }
    return 1;
}