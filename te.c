#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
  FILE *fp[2];
  char c[100];
  char *args[4];
  char str[20];
  int i=0;
  argv[1]= "commands.txt";
  argv[2]= "commands1.txt";
  for(i=0;i<2;i++)
  { 
   fp[i]=fopen(argv[i+1],"r");
    if(fp[i]==NULL)
    {
      printf("File Cannot be opened");
      exit(0);
    }
    else
    {
      while(fgets(c,100,fp[i])!=NULL)
      {
        c[strlen(c)-1]='\0';
        char* token=strtok(c, " ");
        if(strcmp(c,"quit")==0)
        {
        printf("%s\n",token);
        printf("done\n");
        exit(0);
        }
        int count=0;
    
       while(token!=NULL)
       {
        args[count]=token;
        count=count+1;
        printf("%s\n",token);
        token=strtok(NULL, " ");
       }
       args[count]=NULL;
       pid_t pid;
       pid=fork();
       if(pid==0)
       {
        execvp(args[0],args);
       }
       else
       {
        wait(NULL);
       }
 
    }
   }
  fclose(fp[i]); 
 }
  /*char str[20];
  printf("Enter the command:");
  scanf("%[^\n]%*c",str);
  char p[100];
  if(strcmp(str,"history brief")==0)
  {
   for(i=0;i<2;i++)
   {
    fp[i]=fopen(argv[i+1],"r");
    while(fgets(p,100,fp[i])!=NULL)
    {
     printf("%s\n",p);
    }
   }
   fclose(fp[i]);
  }*/
}
