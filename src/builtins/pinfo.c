#include "builtin_func.h"

int  pinfo_execute(char **arg)
{
	if(arg[1]==NULL)
	{
		fprintf(stderr, "usage: pinfo [<valid pid>]\n");
    	return 1;
	}
	char state[6]={'S','t','a','t','e'};
	char id[4]={'P','i','d'};
	char peak1[7]={'V','m','P','e','a','k'};
	char peak2[7]= {'V','m','S','i','z','e'};
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
	        perror("error");
	        break;
	    }
	    st++;
	    if(dest[0]==id[0] && dest[1]==id[1] && dest[2]==id[2])
	    	printf("%s",dest);
	    if(dest[0]==state[0] && dest[1]==state[1] && dest[2]==state[2] && dest[3]==state[3] && dest[4]==state[4])
	    	printf("%s",dest);
	    if(dest[0]==peak1[0] && dest[1]==peak1[1] && dest[2]==peak1[2] && dest[3]==peak1[3] && dest[4]==peak1[4] && dest[5]==peak1[5])
	    	printf("%s",dest);
	    if(dest[0]==peak2[0] && dest[1]==peak2[1] && dest[2]==peak2[2] && dest[3]==peak2[3] && dest[4]==peak2[4] && dest[5]==peak2[5])
	    	printf("%s",dest);
	    // if(st==2 || st==5 || st==17)
	      // printf("%s",dest);

	}while(st -48<0);
	fclose(fp);
	free(dest);
	free(dest_status);
	free(flush);
	return 1;

}