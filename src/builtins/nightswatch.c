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
void nightwatch_execute_interrupt()
{
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	FILE * fp = fopen("/proc/interrupts", "r");
	if (fp == NULL)
    {
    	perror("error");
        return ;
    }
    while ((read = getline(&line, &len, fp)) != -1) {
    	
    	if(line[2]=='1' &&line[3]==':' && line[1]==' ')
    	{
    		printf("CPU Interrupt by Keyboard Controller i8042 with IRQ 1\n");
        	printf("%s\n", line);
        }
    }

    fclose(fp);
    if (line)
        free(line);
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
	if(arg[1]==NULL || arg[2]==NULL || arg[3]==NULL || (strcmp(arg[3],"dirty")!=0 && strcmp(arg[3],"interrupt")))
	{
		fprintf(stderr, "Usage [ nightswatch -n {time-value} {dirty or interrupt} ]\n");
		return 1;
	}
	int f_dirty=0;
	int f_interrupt=0;
	if(strcmp(arg[3],"dirty")==0)
	{
		f_dirty=1;
	}
	if(strcmp(arg[3],"interrupt")==0)
	{
		f_interrupt=1;
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
        	if(f_dirty==1)
        	{
        		nightwatch_execute();
        	}
        	if(f_interrupt==1)
        	{
        		nightwatch_execute_interrupt();
        	}
        	sleep(t);
        }
    }
    printf("\n");
    nonblock(NB_DISABLE);
    return 1;
}