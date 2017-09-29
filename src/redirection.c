#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>

int check[4];
int fd[4];
int count1 =0;
char **redirect (char ** cmd)
{

	char *in = (char *) malloc(100*sizeof(char));
	char *out = (char *) malloc(100*sizeof(char));
	char *outdir =(char *) malloc(100*sizeof(char));


	char *q = cmd[0];
	while(q!=NULL)
	{

		if (strncmp(q,"<",1)==0)
		{
			cmd[count1]=NULL;
			check[0] =1;
			strcpy(in,cmd[count1+1]);
		}

		if((strncmp(q,">",1)==0))
		{
			cmd[count1]=NULL;
			check[1]=1;
			strcpy(out,cmd[count1+1]);
		}

		if(strncmp(q,">>",2)==0)
		{
			cmd[count1]=NULL;
			check[2]=1;
			strcpy(outdir,cmd[count1+1]);
		}
		count1++;
		q = cmd[count1];
	}


	if( check[0]==0 && check[1]==0 &&  check[2]==0)
		return cmd;


	if(check[0]==1)
	{

		*(fd+0) = open(in, O_RDONLY,0);

	
		if(*(fd+0) < 0)
		{
			perror("Input file cannot be opened");
			exit(0);
		}

		dup2(*(fd+0),0);
		close(*(fd+0));
	}

	if(check[1]==1)
	{

		*(fd+1) = open (out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(*(fd+1)<0)
		{
			perror("Unable to open output file");
			exit(0);
		}

		dup2(*(fd+1),1);
		close(*(fd+1));
	}

	if(check[2]==1)
	{

		*(fd+2) = open (outdir, O_WRONLY | O_CREAT | O_APPEND , 0644);
		if(*(fd+2)<0)
		{
			perror("Unable to open the output file");
			exit(0);
		}

		dup2(*(fd+2),1);
		close(*(fd+2));
	}

	return cmd;
}
