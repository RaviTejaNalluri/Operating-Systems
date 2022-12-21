#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

int main(int argc,char *argv[])
{
FILE *f;
int i;
char s[20],c[20];

f=fopen(argv[1],"r");

if(f == NULL)
{printf("error");  
 exit(1);            
}

else
{
while(fgets(s,sizeof(s),f)!=NULL)
{int fd[2];
pid_t p;
pipe(fd);
p=fork();

if(p<0)
{
printf("Process creation failed!");
}

else if(p==0)
{printf("Child Process!\n");
close(fd[1]);
read(fd[0],c,sizeof(s));
printf("%s\n",c);
char *token;
int i=0;
token=strtok(s," ");
char *d[5];
while(token!=NULL)
{d[i]=token;
token=strtok(NULL," ");
i++;
}
d[i-1]=NULL;
execvp(d[0],d);

}


else if(p>0)
{

printf("Parent Process\n");
close(fd[0]);
write(fd[1],s,sizeof(s));

wait(NULL);
}
}
fclose(f);
}
}
