#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<readline/readline.h> 
#include<readline/history.h> 
#include<string.h>
#include<pwd.h>
#include<limits.h>
#include<signal.h>




char deviceName[100],currentWD[100];
char *username;


char *getusername()
{
 uid_t uid=geteuid();
 struct passwd *pw=getpwuid(uid);
 if(pw)
 {
  return pw->pw_name;
 }
 return "";
}




char* read_command()
{
	ssize_t bufferS = 0;
	char* command = NULL;
	if(getline(&command,&bufferS,stdin)==-1){
		printf("Cannot Read pls enter again.\n");//Cannot read the line
		return read_command();
	}
	
	return command;
}




int main(int argc,char** argv[])
{
  char shellWD[200];
  char *args;
  getcwd(currentWD,sizeof(currentWD));//To get the current working directory
  gethostname(deviceName,sizeof(deviceName));//To Get The System name
  username=getusername();
  /*while(1)
  {
     getcwd(shellWD,sizeof(shellWD));
     char *swd1=shellWD;
     if(strncmp(currentWD,shellWD,strlen(currentWD))==0)
     {
        swd1=replaceWord(shellWD,currentWD,"");
     }*/
     printf("%s@%s~%s>",username,deviceName,currentWD);
     args=read_command();
  /*if(strcmp("exit\n",args)==0)
	{
		printf("Exiting\n");
		free(args);
		return 1;
	}*/
       
} 

