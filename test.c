#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<readline/readline.h> 
#include<readline/history.h> 
#include<string.h>

void user()
{
  printf("\n\tShell starts here\n\n");
  char* username=getenv("USER");
  char* systemname=getenv("LOGIN");                        
  printf("%s@%s:~>\n\n\n",username,username);
 }
int input(char *str)
{
 
}

int main(int argc,char **argv[])
{
  user();
}

