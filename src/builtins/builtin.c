#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <time.h>
#define sz 123
#define max_sz 1234
char home[sz];
struct passwd *pws;
int nightwatch_execute()
{
	// if(arg[0]==NULL)
	// {
	// 	fprintf(stderr, "Need argument [ Usage -n {time} <command (dirty, interrupt)> ]\n");
 //    	return 1;
	// }
	char * flush = malloc(sizeof(char)*max_sz);
	char * dest_status = malloc(sizeof(char)*max_sz);
	char * dest = malloc(sizeof(char)*max_sz);
	strcpy(dest, "/proc/");
	//strcat(dest, arg[1]);
	strcpy(dest_status, dest);
	// strcat(dest, "/exe");
	strcat(dest_status, "/meminfo");
	readlink(dest, flush, max_sz-1);
	printf("Path: %s\n",flush);

	FILE * fp = fopen(dest_status, "r");
	int st = 0;
	size_t buff = max_sz;
	do
	{
	    if(getline(&dest, &buff, fp)==-1)
	    {
	      	//printf("%s",dest);	
	        perror("");
	        break;
	    }
	    st++;
	    if(st==17)
	      printf("%s",dest);
	}while(st -18<0);
	fclose(fp);
	free(dest);
	free(dest_status);
	free(flush);
	return 1;
}
// int  pinfo_execute(char **arg)
// {
// 	if(arg[1]==NULL)
// 	{
// 		fprintf(stderr, "Need pid as argument\n");
//     	return 1;
// 	}
// 	char * flush = malloc(sizeof(char)*max_sz);
// 	char * dest_status = malloc(sizeof(char)*max_sz);
// 	char * dest = malloc(sizeof(char)*max_sz);
// 	strcpy(dest, "/proc/");
// 	strcat(dest, arg[1]);
// 	strcpy(dest_status, dest);
// 	strcat(dest, "/exe");
// 	strcat(dest_status, "/status");
// 	readlink(dest, flush, max_sz-1);
// 	printf("Path: %s\n",flush);

// 	FILE * fp = fopen(dest_status, "r");
// 	int st = 0;
// 	size_t buff = max_sz;
// 	do
// 	{
// 	    if(getline(&dest, &buff, fp)==-1)
// 	    {
// 	      	printf("%s",dest);	
// 	        perror("");
// 	        break;
// 	    }
// 	    st++;
// 	    if(st==2 || st==5 || st==17)
// 	      printf("%s",dest);
// 	}while(st -17<0);
// 	fclose(fp);
// 	free(dest);
// 	free(dest_status);
// 	free(flush);
// 	return 1;

// }
// void ls(char * str)
// {
//     DIR*p;
//     struct dirent *d;	
//     p=opendir(str);
//     if(p==NULL)
//     {
//         perror("Cannot find directory");
//         exit(-1);
//     }
//     while(d=readdir(p))
//     {

//     	if(d->d_name[0]!='.')
//         	printf("%s\n",d->d_name);
//     }
// }
// void ls_a(char * str)
// {
// 	char ch[2];
// 	ch[0]='.'; ch[1]='\0';
//     DIR*p;
//     struct dirent *d;	
//     p=opendir(ch);
//     if(p==NULL)
//     {
//         perror("Cannot find directory");
//         exit(-1);
//     }
//     while(d=readdir(p))
//         printf("%s\n",d->d_name);
// }
// void ls_l(char * str, int flag)
// {
//     DIR*p;
//     struct dirent *dirp;
//     p=opendir(str);
//     while ((dirp = readdir(p)) != NULL)
//     {
//         struct stat fileStat;
//         stat(dirp->d_name,&fileStat);   
//         // printf("File Permissions: \t");
//         printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
//         printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
//         printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
//         printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
//         printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
//         printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
//         printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
//         printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
//         printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
//         printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
//         printf(" %ld ",fileStat.st_nlink);
//         printf(" %s ",pws->pw_name);
//         printf(" %ld",fileStat.st_size);
//         char date[20];
//         strftime(date, 20, "%b %d %R", localtime(&(fileStat.st_ctime)));
//         printf("  %s",date);
//         if(flag==2)
//         	printf(" %s\t",dirp->d_name);
//         else if(flag==1)
//         	if(dirp->d_name[0]!='.')
//         		printf(" %s\t",dirp->d_name);
//         // printf("\t%ld\n",fileStat.st_ino);
//         printf("\n");
//         // printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
//         // printf("\n\n");	        
// }
// int ls_execute(char **arg)
// {
// 	if(arg[1]==NULL)
// 	{
// 		char ch[2];
// 		ch[0]='.';
// 		ch[1]='\0';
// 		ls(ch);
// 		return 1;
// 	}
// 	else
// 	{
// 		char str[max_sz];
// 		str[0]='.';
// 		str[1]='\0';
// 		int i=0;
// 		int flag_a=0,flag_l=0.dir=0;
// 		int len=stelen(arg);
// 		for(int i=0;i<len;i++)
// 		{
// 			if(arg[i][0]=='-')
// 			{
// 				if(arg[i][1]=='a')
// 				{
// 					flag_a = 1;
// 				}
// 				else if(arg[i][1]=='l')
// 				{
// 					flag_l = 1;
// 				}
// 				else if((arg[i][1]=='a' && arg[i][2]=='l') || (arg[i][1]=='a' && arg[i][2]=='l'))
// 				{
// 					flag_a = 1;
// 					flag_l = 1;
// 				}
// 			}
// 			else if(arg[i][0]!='-' && arg[i]!=NULL)
// 			{
// 				dir=1;
// 				strcpy(str,arg[i]);
// 			}
// 		}
// 		if(flag_l==1)
// 		{
// 			if(dir==1 && flag_a==1)
// 			{
// 				ls_la(str,2);   
// 			}
// 			else if(dir==1 &&flag_a==0)
// 			{
// 				ls_l(str,1);
// 			}
// 			else if(dir==0 && flag_a==1)
// 			{
// 				ls_la(str,2);
// 			}
// 			else
// 			{
// 				ls_l(str,1) ; 
// 			}
// 		}
// 		else if(flag_a==1)
// 		{
// 			ls_a(str);
// 		}
// 		else 
// 		{
// 			ls(str);
// 		}
// 		return 1;
// 	}
// }
// int ls_check(char * argv)
// {
// 	if(argv[0]=='l' && argv[1]=='s')
// 		return 1;
// 	return 0;
// }
// int cd_execute(char **arg)
// {
// 	if(arg[1]==NULL)
// 	{
// 		if(chdir(home)!=0)
// 		{
// 			perror("error");
// 		}
// 		return 1;
// 	}
// 	else if(argv[1]=='~')
// 	{
// 		char * result = (char *)malloc(sizeof(char)*sz);
// 		strcpy(result,home);
// 		strcpy(result+strlen(result),argv+1);
// 		if(chdir(result)!=0)
// 		{
// 		 	perror("error");
// 		}
// 		free(result);
// 		return 1;
// 	}
// 	else
// 	{
// 		if(chdir(arg)!=0)
// 		{
// 			perror("error");
// 			return 1;
// 		}
// 	}
// }
// int cd_check(char * str)
// {
// 	if(str[0]=='c' && str[1]=='d')
// 		return 1;
// 	return 0;
// }
// int echo_print(char **arg)
// {
// 	//char argv[1000];
//     int i=0;
//     while(1)
//     {
//         if(argv[1][i]=='\0')
//         {
//             break;
//         }
//         else{
//             fprintf(stdout,"%c",argv[1][i]);
//             i++;
//         }
//     }
//     return 1;
// }
// int echo_check(char * str)
// {
// 	if(str[0]=='e' && str[1]=='c' && str[2]=='h' && str[3]=='o' )
// 		return 1;
// 	return 0;
// }
// void pwd(char ** arg)
// {
// 	char *pwd_char =(char *)malloc((sizeof(char))*sz);
//     if(getcwd(pwd_char,sz)==NULL)
//         printf("command does not exist\n");
//     else
//     {
//         printf("%s\n",pwd_char);
//     }
//     free(pwd_char);
//     return 1;
// }
// int pwd_check(char * line)
// {
//     if(line[0]=='p'&&line[1]=='w'&&line[2]=='d')
//         return 1;
//     return 0;
// }
int main(int argc,char **argv)
{
	pws = getpwuid(geteuid());
    char hostname[sz];
    gethostname(hostname,sz);
    char * line =NULL;
    ssize_t buffsize = 0; 
    getcwd(home,sz);
    char curr_dir[10000];
    getcwd(curr_dir,sz);
    strcpy(home,curr_dir);
    home[strlen(home)]='\0';
    // pwd(pws,hostname);
    while(1)
    {
        printf("<%s@%s>:~",pws->pw_name,hostname);
        //getline(&line,&buffsize,stdin);
        nightwatch_execute();
        sleep(3);
    }
    return 0;
}