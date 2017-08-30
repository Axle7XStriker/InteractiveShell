#include "builtin_func.h"

int pwd_execute(char ** arg)
{
	char *pwd_char =(char *)malloc((sizeof(char))*sz);
    if(getcwd(pwd_char,sz)==NULL)
        printf("command does not exist\n");
    else
    {
        printf("%s\n",pwd_char);
    }
    free(pwd_char);
    return 1;
}