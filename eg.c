#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
  char* msg1="Hello World 1";
  char* msg2="Hello world 2";
  char* msg3="Hello World 3";

  int MSGSIZE=13;
  int p[2],inbuf[MSGSIZE],i;
  if(pipe(p)<0)
  {
    exit(1);
  }
  write(p[1],msg1,MSGSIZE);
  write(p[1],msg2,MSGSIZE);
  write(p[1],msg3,MSGSIZE);

  for(i=0;i<3;i++)
  {
    read(p[0],inbuf,MSGSIZE);
    printf("%s\n",inbuf);
  }

}
