//#include "read_and_parse.h"
#include "main.h"

int main(int argc, char **argv)
{
	int status = 1, i;
	char *cmd_line;
	char **cmd_sequence, **cmd;

	//Initialize the shell
	pws = getpwuid(geteuid());
    char hostname[sz];
    gethostname(hostname,sz);
    //char * line = NULL;
    //ssize_t buffsize = 0; 
    getcwd(home,sz);
    char curr_dir[10000];
    getcwd(curr_dir,sz);
    strcpy(home,curr_dir);

	//Run command execution loop
	while(status)
	{
		/*Display Prompt*/
        printf("<%s@%s>:~",pws->pw_name,hostname);
        /*Read the command(s) from stdin*/
        fflush(stdin);
        cmd_line = read_cmd();
        //fprintf(stdout, "%s", cmd_line);
		/*Parse the command(s) to get command(s) name and argument(s) required by that command*/
        cmd_sequence = parse_cmd(cmd_line, CMD_DELIMITER);
        
    	/*Execute the command(s)*/
        if (cmd_sequence != NULL)
		{
			for (i=0; ((cmd_sequence[i] != NULL) && status); i++)
			{
                cmd = parse_cmd(cmd_sequence[i], TOKEN_DELIMITER);
                int j;
				int bg = is_background_process(cmd);
				for (j=0; cmd[j] != NULL; j++)
					fprintf(stdout, "%s ", cmd[j]);
				printf(": %d\n", bg);
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
