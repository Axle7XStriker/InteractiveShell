#include "builtin_func.h"

int  pinfo_execute(char **arg)
{
	if(arg[1]==NULL)
	{
		char result[20];
		int pid= getpid();
		sprintf(result,"%d" ,pid);
		arg[1]=result;
		// printf("%s\n",arg[1]);
		pinfo_execute(arg);
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
	struct stat sb;
	if(stat(dest,&sb) < 0)
	{
		perror("error");
		return 1;
	}
	strcpy(dest_status, dest);
	strcat(dest, "/exe");
	strcat(dest_status, "/status");
	int ans = readlink(dest, flush, max_sz);
	int inside=0;
	if(ans <=0)
	{
		inside=1;
		fprintf(stderr,"Path: ");
		perror("error");
	}
	int flag=0;
	if(inside==0)
	{
		char *path_end =NULL; 
		path_end =  strrchr(flush,'/');
		
	
		if(path_end==NULL)
		{
			flag=1;
			printf("Path: \n");
		}
		++path_end;
		*path_end = '\0';
	}
	
	FILE * fp = fopen(dest_status, "r");
	if(fp==NULL)
	{
		perror("error");
		return 1;
	}
	if(flag==0 && inside==0)
		printf("Path: %s\n",flush);
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

	}while(st -48<0);
	fclose(fp);
	free(dest);
	free(dest_status);
	free(flush);
	return 1;

}