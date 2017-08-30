#include "builtin_func.h"

int echo_execute(char **arg)
{
	//char argv[1000];
    int i=0;
    while(1)
    {
        if(arg[1][i]=='\0')
        {
            break;
        }
        else{
            fprintf(stdout,"%c",arg[1][i]);
            i++;
        }
    }
    printf("\n");
    return 1;
}