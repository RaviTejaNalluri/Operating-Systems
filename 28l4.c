#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUMBER_OF_ENTRIES 10
#define NUMBER_OF_SEQUENCES 50//for number of page table entries


struct pte
{
	int page_frame_number;
	int valid_bit:1;
	int present_bit:1;
	int dirty_bit:1;
}p[NUMBER_OF_ENTRIES];



double unravel(int *ptr)
{
	clock_t start;
	clock_t end;
    double cpu_time_used=0, temp_timer=0;
    
	int iterator,array[16],number,VPN,factor,a[14],it,i,temp,counter=0;
	for(iterator = 0; iterator<16;array[iterator]=0,iterator++);
	for(i=0; i<NUMBER_OF_SEQUENCES;i++)
	{
		printf("%3d VPN: ",i);
		number = *ptr;
		VPN=0;
		factor = 32;
		for(iterator=0;iterator<16;iterator++)    
    	{    
        	array[iterator]=number%2;
        	if(iterator<6)
        	{
        		printf("%d",array[iterator]);
        		VPN = VPN + array[iterator]*factor;
        		factor = factor/2;  
        	}
        	number=number/2;    
    	}
    	printf(" %2d ",VPN);
    	temp = p[VPN].page_frame_number;
    	start = clock();
    	
    		counter++;
    		printf("  FN: ");
    		printf("%5d ", temp);
    		for(it=0;it<14;it++)    
			{    
				a[it]=temp%2;    
				temp=temp/2;    
			}
			for(it=it-1;it>=0;it--)     
				printf("%d",a[it]);   
			printf(" OFFSET: ");
			for(it=6;it<16;it++)
			printf("%d",array[it]);
    		printf("\n");
    		ptr++;
    		end = clock();
    		temp_timer = ((double) (end - start)) / CLOCKS_PER_SEC;
    		cpu_time_used+=temp_timer;
    	
    } 
    return cpu_time_used/counter;
}

void binarynumber()//for generating addresses
{
	time_t t;
	srand((unsigned) time(&t));
    int i;

	for(i=0;i<NUMBER_OF_ENTRIES;i++)
	{
		p[i].valid_bit = (rand()%(2));
	    p[i].present_bit = (rand()%(2));
		p[i].dirty_bit = (rand()%(2));
	}
}

void PFNS()//generating Page frame numbers
{
	time_t t;
	srand((unsigned) time(&t));
	int i; 
	int a[100]; 
	int PFN; 
	int count = 1;
	for(i=0; i<100; a[i]=0, i++);
	for(i=0; i<NUMBER_OF_ENTRIES; i++)
	{
		PFN = (rand()%(150));
		while(count)
        {
            if(a[PFN]!=0)
                PFN = (rand() % (150));
                else
                {
	                a[PFN]=a[PFN]+1;
                    p[i].page_frame_number = PFN;
                    count = 0;
                }
        }
        count = 1;
	}
}

void VPN(int *ptr)//finding virtual page number 
{
	time_t t;
	srand((unsigned) time(&t));
	int i;
	int a[100]; 
	int v; 
	
	int flag = 1;
	for(i=0; i<100; a[i]=0, i++);
	for(i=0; i<NUMBER_OF_SEQUENCES; i++)
	{
		v = (rand()%(120));
		while(flag)
        {
            if(a[v]!=0)
                v = (rand() % (120));
                else
                {
	                a[v]+=1;
                    *ptr = v;
                    flag = 0;
                }
        }
        flag = 1;
        ptr++;
	}
}


int main()
{
	int trail;
	
	int virtual_address_spaces[NUMBER_OF_SEQUENCES],iterator;
	double time = 0;
	
    
	printf("Enter The no.of page tables you want to run:");
    scanf("%d",&trail);
	for(iterator = 0; iterator<trail; iterator++)
	{
		PFNS();
		binarynumber();
		VPN(virtual_address_spaces);
		time+= unravel(virtual_address_spaces);
	}
	printf("time taken to access bits: %lf\n",time/trail);
	return 0;
}