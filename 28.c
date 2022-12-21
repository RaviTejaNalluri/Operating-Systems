#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
FILE *brieffptr;
FILE *detailfptr;

int main(int argc,char* argv[])
{
  //printf("Enter the no.of files you wannt to read from:");
  //int n;
  //scanf("%d",&n);
  FILE *fp;
  FILE *fptr;
  char c[100];
  char *args[4];
  char p;
  int i=1;
  //fp[0]= fopen("commands.txt","r");
  //fp[1]= fopen("commands1.txt","r");
  while(argv[i]!=NULL)
  {
   fp=fopen(argv[i],"r");
  
    if(fp==NULL)
    {
      printf("File Cannot be opened");
      exit(0);
    }
    else
    {
       
      while(fgets(c,100,fp)!=NULL)
      {
        
        c[strlen(c)-1]='\0';
        char* token=strtok(c, " ");
        if(strcmp(c,"quit")==0)
        {
        printf("%s\n",token);
        printf("done\n");
        break;
        }
        int count=0;
         fptr=fopen("List.txt","w");
       

       while(token!=NULL)
       {
        args[count]=token;
        count=count+1;
        printf("%s\n",token);
        token=strtok(NULL, " ");

        
       }
       args[count]=NULL;
       while ((p = fgetc(fp)) != EOF) 
       {
           fputc(p, fptr);
       }
     //fclose(fp); 
  
  fclose(fptr);
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
   fclose(fp);
   i=i+1;
   
 }
 

 
 int line_size = 300;
 char* line = malloc(line_size);
 char* line2 = malloc(line_size);
 printf("Welcome to interactive mode\n\n");
 while(1)
 {
   printf("Enter the command:");
   gets(line,line_size,stdin);
   strcpy(line2,line);
   if(strcmp(line,"STOP")==0)
   {
     printf("Bye");
     exit(1);
   }
   else if (strcmp(line,"History Brief")==0)
   {
    FILE *hb;
    hb=fopen("List.txt","r");
    char command[25];
    while(fgets(command,sizeof(command),hb)!=NULL)
    {
      printf("%s",command);

    } 
    fclose(hb);
   }
   else if (strcmp(line,"History Full")==0)
   {
    FILE *hf;
    hf=fopen("List.txt","r");
    char command[25];
    int count1=1;
    while(fgets(command,sizeof(command),hf)!=NULL)
    {
      printf("%d.%s",count1,command);
      count1+=1;
   } 
    fclose(hf);
   }
   else
   {
   	printf("Please enter the valid command:)\n");
   }
 }
 p=p+1;
}
void execute(char * file_name)
{
    FILE * filePointer; 
    filePointer = fopen(file_name,"r"); 
    char str1[100];
    
    
    while(fscanf(filePointer, "%[^\n]", str1)==1)
    {     
        pid_t pid;
        pid=fork();
        if(pid==0)//child process
        {
            
            char* args1[10];
           
            char *token3=strtok(str1," ");
            
            int i=0;
            while (token3!=NULL)
            {
                args1[i]=token3;
                i++;
                token3=strtok(NULL," ");
            }
            args1[i]=NULL;
            
            execvp(args1[0],args1); 
            exit(EXIT_SUCCESS);
        }
        else if(pid<0)
        {
            fprintf(stderr,"error in forking \n");
            return EXIT_FAILURE;
        }
        else
        {
            fscanf(filePointer, "%[^\n]", str1);
            char strt[100];
            strcpy(strt,str1);
            fprintf(detailfptr,"%s\n",str1);
            char *token=strtok(strt," ");
            fprintf(brieffptr,"%s\n",token);
            fseek(filePointer, SEEK_CUR, SEEK_SET+1);
            
           
            wait(NULL);
        }
    }

    fclose(filePointer);

}


