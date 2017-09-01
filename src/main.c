//#include "read_and_parse.h"
#include "main.h"

int main(int argc, char **argv)
{
	int status = 1;
	char *cmd_line;
	char **cmd_sequence, **cmd;

	//Initialize the shell
	pws = getpwuid(geteuid());
    char hostname[sz],result[sz];
    gethostname(hostname,sz);
    //char * line = NULL;
    //ssize_t buffsize = 0; 
    getcwd(home,sz);
    char curr_dir[sz];
    getcwd(curr_dir,sz);
    strcpy(home,curr_dir);
    int i=0,j=0;
    int len_home =strlen(home);
	//Run command execution loop
	while(status)
	{
		/*Display Prompt*/
        fflush(stdin);
        getcwd(curr_dir,sz);
        int len1=strlen(curr_dir);
        i=0;
        j=0;
        if(len1 <len_home)
        {
        	printf(ANSI_COLOR_GREEN	"<%s@%s>" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE	"%s" ANSI_COLOR_RESET "$ ",pws->pw_name,hostname, curr_dir);
        	
        }
        else
        {
        	j=0;
        	for(i=0;i<len_home;i++)
        	{
        		if(home[j]!=curr_dir[i])
        		{
        			break;
        		}
        		j++;
        	}
        	if(j==len_home)
        	{
        		result[0]='~';
        		for(i=j;i<len1;i++)
        		{
        			result[i-j+1]=curr_dir[i];

        		}
        		result[i-j+1]='\0';
        		printf(ANSI_COLOR_GREEN	"<%s@%s>" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE	"%s" ANSI_COLOR_RESET "$ ",pws->pw_name,hostname, result);

        	}
        	else
        	{
        	
        		printf(ANSI_COLOR_GREEN	"<%s@%s>" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE	"%s" ANSI_COLOR_RESET "$ ",pws->pw_name,hostname, curr_dir);
        	}
        }
        /*Read the command(s) from stdin*/
        //fflush(stdin);
        printf(" \n");
        cmd_line = read_cmd();
        // printf("gulshan1\n");
        // printf("%s\n",cmd_line);
        //fprintf(stdout, "%s", cmd_line);
		/*Parse the command(s) to get command(s) name and argument(s) required by that command*/
        cmd_sequence = parse_cmd(cmd_line, CMD_DELIMITER);
        
    	/*Execute the command(s)*/
        if (cmd_sequence != NULL)
		{
			for (i=0; ((cmd_sequence[i] != NULL) && status); i++)
			{
                cmd = parse_cmd(cmd_sequence[i], TOKEN_DELIMITER);
				int bg = is_background_process(cmd);
				//for (j=0; cmd[j] != NULL; j++)
				//	fprintf(stdout, "%s ", cmd[j]);
				//printf(": %d\n", bg);
				status = execute_cmd(cmd, bg);
				free(cmd);
			}
		}
		free(cmd_sequence);
		//free(cmd_line);
	}
	//Terminate the shell

	return 0;
}
