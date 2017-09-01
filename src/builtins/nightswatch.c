#include "builtin_func.h"
#include <string.h>


#define NB_DISABLE 0
#define NB_ENABLE 1
int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
void nonblock(int state)
{
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state==NB_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state==NB_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

}
void nightwatch_execute()
{
	char dirty[6]= {'D','i','r','t','y'};
	char * flush = malloc(sizeof(char)*max_sz);
	char * dest_status = malloc(sizeof(char)*max_sz);
	char * dest = malloc(sizeof(char)*max_sz);
	strcpy(dest, "/proc/");
	strcpy(dest_status, dest);
	strcat(dest_status, "/meminfo");
	readlink(dest, flush, max_sz-1);

	FILE * fp = fopen(dest_status, "r");
	int st = 0;
	size_t buff = max_sz;
	do
	{
	    if(getline(&dest, &buff, fp)==-1)
	    {	
	        perror("error in reading");
	        break;
	    }
	    st++;
	    if(dest[0]==dirty[0] && dest[3]==dirty[3] && dest[1]==dirty[1] && dest[2]==dirty[2] && dest[4]==dirty[4])
	      printf("%s",dest);
	}while(st -45<0);
	fclose(fp);
	free(dest);
	free(dest_status);
	free(flush);
}

int nightswatch(char **arg)
{
	if(arg[1]==NULL || arg[2]==NULL || arg[3]==NULL || strcmp(arg[3],"dirty")!=0)
	{
		fprintf(stderr, "Usage [ nightswatch -n {time-value} dirty ]\n");
		return 1;
	}
    int t = atoi(arg[2]);
    char c;
    int i=0;
    nonblock(NB_ENABLE);
    while (!i)
    {   
    	usleep(1);
        i=kbhit();
        if (i!=0)
        {
            c=fgetc(stdin);
            if (c=='q')
                i=1;
            else
                i=0;
        }
        if(c!='q')
        {
        	nightwatch_execute();
        	sleep(t);
        }
    }
    printf("\n");
    nonblock(NB_DISABLE);
    return 1;
}