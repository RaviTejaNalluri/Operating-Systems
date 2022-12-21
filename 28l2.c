#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
  FILE *fp;
  char c[100];
  fp=fopen(argv[1],"r");
  if(fp==NULL)
  {
    printf("Failed to open file");
    exit(1);
  }
  else
  {

    while(fgets(c,100,fp)!=NULL)
    {

      c[strlen(c)-1]='\0';
      char* token = strtok(c, " ");
      if(strcmp(c,"quit")==0)
      {
        printf("%s\n",token);
        printf("done\n");
        exit(0);
      }
      char *args[4];

      int count=0;
    while (token != NULL) {
        args[count]=token;
        count=count+1;
        printf("%s\n", token);
        token = strtok(NULL, " ");
     }
      args[count]=NULL;
      pid_t pid;
      pid=fork();
      if(pid==0)
      {
        /*int i=0;
        for(i=0;i<3;i++)
        {
          printf("%s\n",args[0]);
        }*/
        execvp(args[0],args);
      }
      else if(pid<0)
      {
        printf("Unable fork the child");
        
      }
      else
      {
        wait(NULL);
      }
    }
  }
  fclose(fp);

}
