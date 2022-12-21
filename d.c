#include <stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

int main(int argc,char* argv[])
{
FILE *f=fopen(argv[1],"r");//for reading file as an argument
char c[256];
if(f == NULL)
   {
      printf("Error!");   
      exit(1);             
   }else{
int count=0;

while(fgets(c,sizeof c,f)!=NULL){//for executing our commands in file
count=0;
c[strlen(c)-1]='\0';
printf("%s\n",c);
char* myargs[1000];
int pid;
if ((pid = fork()) < 0) {    
          printf(" ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {

	  char* token = strtok(c," ");
	while (token != NULL) { 
	myargs[count]=token;
	token = strtok(NULL," ");
	count++;
	}   
          if (execvp(myargs[0],myargs) < 0) {     
               printf("ERROR: exec failed\n");
               exit(1);
          }
     }else{
wait(NULL);
}
}
}

fclose(f);
} 
