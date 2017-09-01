#include "builtin_func.h"

int echo_execute(char **arg)
{
    int i=0,j=0;
    for(j=1;arg[j]!=NULL;j++)
    {
        i=0;
        while(1)
        {
            if(arg[j][i]=='\0')
            {
                break;
            }
            else{
                fprintf(stdout,"%c",arg[j][i]);
                i++;
            }
        }
        printf(" ");
    }
    printf("\n");
    return 1;
}