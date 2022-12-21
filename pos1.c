#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
   
   FILE *ptr;
   pid_t  pid;
   char c[100];
   char cmd[100];
   int fd[2];

   ptr=fopen(argv[1],"r");

   if(ptr==NULL)
   {
     printf("file not found");
     exit(1);
   }
   else
   {
     while (fgets(c,100,ptr)!=NULL)
     {
       c[strlen(c)-1]='\0';
       if(strcmp(c,"quit")==0)
       {
         printf("done\n");
         exit(0);
       }
     
      pipe(fd);
      if(pipe(fd)<0)
      {

        printf("Error");
      }
      pid=fork();
      if(pid<0)
      {
        printf("Failed");
        exit(1);
      }
      else if(pid>0)
      {
        close(fd[0]);
        write(fd[1],c,sizeof(c));
        close(fd[1]);
        wait(NULL);
      }
      else
      {
         
        char* p;
        char* a[4];
        int args=0;
        close(fd[1]);
        read(fd[0],cmd,100);
        close(fd[0]);
        p=strtok(cmd," ");
        while (p != NULL)
            {
                a[args] = p;
                p= strtok (NULL, " ");
                args = args + 1;
            }
            a[args]=NULL;
            execvp(a[0], a);

      }
     }
   }

}

