#include "builtin_func.h"

int cd_execute(char **arg)
{
	if(arg[1]==NULL)
	{
		if(chdir(home)!=0)
		{
			perror("error");
		}
		return 1;
	}
	else if(arg[1]=='~')
	{
		char * result = (char *)malloc(sizeof(char)*sz);
		strcpy(result,home);
		strcpy(result+strlen(result),arg+1);
		if(chdir(result)!=0)
		{
		 	perror("error");
		}
		free(result);
		return 1;
	}
	else
	{
		if(chdir(arg[1])!=0)
		{
			perror("error");
			return 1;
		}
	}
}