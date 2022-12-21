#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
   printf("\t\t\t\tUsing Pipes\n\n");
   FILE *fp;
   pid_t  pid;
   char c[100];
   char readbuf[100];
   int fd[2];

   fp=fopen(argv[1],"r");

   if(fp==NULL)
   {
     printf("Couldn't open file");
     exit(1);
   }
   else
   {
     while (fgets(c,100,fp)!=NULL)
     {
       c[strlen(c)-1]='\0';
       if(strcmp(c,"quit")==0)
       {
         printf("done\n");
         exit(0);
       }
      /*int count=0;
      int args[4];
      char*  token=strtok(c," ");
      while(token!=NULL)
      {
        args[count]=0;
        count=count+1;
        printf("%s\n",token);
        token=strtok(NULL," ");
      }
      args[count-1]=NULL;*/
      pipe(fd);
      if(pipe(fd)<0)
      {

        printf("Error");
      }
      pid=fork();
      if(pid<0)
      {
        printf("Forking failed");
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
        int count1=0;
        close(fd[1]);
        read(fd[0],readbuf,100);
        close(fd[0]);
        p=strtok(readbuf," ");
        while (p != NULL)
            {
                a[count1] = p;
                p= strtok (NULL, " ");
                count1 = count1 + 1;
            }
            a[count1]=NULL;
            /*printf("%s\n",args[0]);
            printf("%s\n",args[1]);
            printf("%s\n",args[2]);*/
            execvp(a[0], a);

      }
     }
   }

}
