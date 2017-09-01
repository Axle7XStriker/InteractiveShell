#include "builtin_func.h"

int cd_execute(char **arg)
{
	if(arg[1]!=NULL && arg[1][0]!='-')
	{
		getcwd(previous,sz);
	}
	if(arg[1]==NULL)
	{
		getcwd(previous,sz);
		if(chdir(home)!=0)
		{
			perror("error");
		}
		getcwd(current,sz);
		return 1;
	}
	else if(arg[1][0]=='-')
	{
		if(chdir(previous)!=0)
		{
			perror("error");
		}
		strcpy(linklist,previous);
		strcpy(previous,current);
		strcpy(current,linklist);
		//printf("%s\n",previous);
		return 1;
	}
	else if(arg[1][0]=='~')
	{
		getcwd(previous,sz);
		char * result = (char *)malloc(sizeof(char)*sz);
		strcpy(result,home);
		strcpy(result+strlen(result),arg[1]+1);
		if(chdir(result)!=0)
		{
		 	perror("error");
		}
		getcwd(current,sz);
		free(result);
		return 1;
	}
	else
	{
		getcwd(previous,sz);
		if(chdir(arg[1])!=0)
		{
			perror("error");
		}
		getcwd(current,sz);
		return 1;
	}
	return 1;
}