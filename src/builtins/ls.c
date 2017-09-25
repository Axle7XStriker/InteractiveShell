#include "builtin_func.h"

void ls(char * str)
{
    DIR*p;
    struct dirent *d;	
    p=opendir(str);
    if(p==NULL)
    {
        perror("Cannot find directory");
        exit(-1);
    }
    while((d=readdir(p)))
    {

    	if(d->d_name[0]!='.')
        	printf("%s\n",d->d_name);
    }
}
void ls_a(char * str)
{
	DIR *p;
    struct dirent *d;	
    p=opendir(str);
    if(p==NULL)
    {
        perror("Cannot find directory");
        exit(-1);
    }
    while((d=readdir(p)))
        printf("%s\n",d->d_name);
}
void ls_l(char * str, int flag)
{
    DIR*p =NULL;
    struct dirent *dirp =NULL;
    p=opendir(str);
    while ((dirp = readdir(p)) != NULL)
    {
    	char convert[1024];
    	sprintf(convert, "%s/%s", str, dirp->d_name);
        struct stat fileStat;
        stat(convert,&fileStat);   
        if(flag==2)
        {
	        printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	        printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	        printf(" %lu",fileStat.st_nlink);
	        printf(" %s ",pws->pw_name);
	        printf(" %s ",pws->pw_name);
	        printf(" %ld",fileStat.st_size);
	        char date[20];
	        strftime(date, 20, "%b %d %R", localtime(&(fileStat.st_ctime)));
	        printf("  %s",date);
	        printf(" %s\t",dirp->d_name);
			printf("\n");
	    }
        else if(dirp->d_name[0]!='.')
        {
        	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	        printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	        printf(" %lu ",fileStat.st_nlink);
	        printf(" %s ",pws->pw_name);
	        struct group *grp;
	        grp=getgrgid(fileStat.st_gid);
	        printf(" %s ",grp->gr_name);
	        printf(" %ld",fileStat.st_size);
	        char date[20];
	        strftime(date, 20, "%b %d %R", localtime(&(fileStat.st_ctime)));
	        printf("  %s",date);
	        printf(" %s\t",dirp->d_name);
			printf("\n");
        }
	}
}
int ls_execute(char **arg)
{
	// printf("%s %s\n",arg[1],arg[2]);
	if(arg[1]==NULL)
	{
		char ch[2];
		ch[0]='.';
		ch[1]='\0';
		ls(ch);
		return 1;
	}
	else
	{
		char str[max_sz];
		int i=0;
		int flag_a=0,flag_l=0,dir=0;
		for(i=1;arg[i]!=NULL;i++)
		{
			if(arg[i][0]=='-')
			{
				if((arg[i][1]=='a' && arg[i][2]=='l') || (arg[i][1]=='l' && arg[i][2]=='a'))
				{
					flag_a = 1;
					flag_l = 1;
				}
				if(arg[i][1]=='a')
				{
					flag_a = 1;
				}
				else if(arg[i][1]=='l')
				{
					flag_l = 1;
				}
				
			}
			else if(arg[i][0]!='-' && arg[i]!=NULL)
			{
				struct stat sb;
				if(stat(arg[i],&sb) < 0)
				{
					perror("error");
					return 1;
				}
				dir=1;
				strcpy(str,arg[i]);
			}
		}
		if(flag_l==1)
		{
			if(dir==1 && flag_a==1)
			{
				ls_l(str,2);   
			}
			else if(dir==1 &&flag_a==0)
			{
				ls_l(str,1);
			}
			else if(dir==0 && flag_a==1)
			{
				str[0]='.';
				str[1]='\0';
				ls_l(str,2);
			}
			else
			{
				str[0]='.';
				str[1]='\0';
				ls_l(str,1) ; 
			}
		}
		else if(flag_a==1)
		{
			if(dir==0)
			{
				str[0]='.';
				str[1]='\0';
				ls_a(str);
			}
			else if(dir==1)
			{
				ls_a(str);
			}
		}
		else 
		{
			if(dir==0)
			{
				str[0]='.';
				str[1]='\0';
				ls(str);
			}
			else if(dir==1)
			{
				ls(str);
			}
		}
		return 1;
	}
}