#include "builtin_func.h"

int  pinfo_execute(char **arg)
{
	if(arg[1]==NULL)
	{
		fprintf(stderr, "usage: pinfo [<valid pid>]\n");
    	return 1;
	}
	char * flush = malloc(sizeof(char)*max_sz);
	char * dest_status = malloc(sizeof(char)*max_sz);
	char * dest = malloc(sizeof(char)*max_sz);
	strcpy(dest, "/proc/");
	strcat(dest, arg[1]);
	strcpy(dest_status, dest);
	strcat(dest, "/exe");
	strcat(dest_status, "/status");
	readlink(dest, flush, max_sz-1);
	printf("Path: %s\n",flush);

	FILE * fp = fopen(dest_status, "r");
	int st = 0;
	size_t buff = max_sz;
	do
	{
	    if(getline(&dest, &buff, fp)==-1)
	    {
	      	printf("%s",dest);	
	        perror("");
	        break;
	    }
	    st++;
	    if(st==2 || st==5 || st==17)
	      printf("%s",dest);
	}while(st -17<0);
	fclose(fp);
	free(dest);
	free(dest_status);
	free(flush);
	return 1;

}