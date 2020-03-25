
/*
To compile use 

gcc os_project.c -o output -pthread 

because else it will show exception that -pthread is not initiaized
*/                                                     

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define MIN_PID 100
#define MAX_PID 1000

int process_status[900];//declaring the array to store status of the processes.


int allocate_pid()
{
int k;
for(k=0;k<MAX_PID-MIN_PID;k++)
	{
	if(process_status[k]==0)//checking for the status of the PID if empty the thread can be assigned other-wise not.
		{
		process_status[k]=1;//making status of the PID as 1 (i.e, Occupied).
		return (k+MIN_PID);//returnig the PID for the thread.
		}
	}
	return -1;
}


void release_pid(int pid)
{
process_status[pid]=0;
}


void *func(void *e)
{
int z,t;
z=allocate_pid();//calling function to assign PID's to the threads.

if(z==-1)//checking if PID is assigned or not.
	{
	printf("PROCESS COULD NOT BE ASSIGNED WITH A PROCESS I.D\n ");
	}
else
	{
	printf("PID :%d ASSIGNED SUCCESFULLY TO THE THRAED\n",z);

	t=rand()%10;//getting random time from the rand function for sleep of the thread.

	printf("PID :%d IS ENTERING SLEEP FOR TIME :%d\n",z,t);

	sleep(t);//making the thread go to sleep(i.e, a way for it to pretend doing some work).

	printf("PID :%d HAS COMPLETED SLEEP \n",z);

	release_pid(z);//releasing the thread after waking from the sleep from release_pid function.

	printf("PID :%d HAS BEEN RELEASED\n",z);
	}
pthread_exit(NULL);
}

int allocate_map()
{
int i,size;
size=MAX_PID-MIN_PID;
for(i=0;i<size;i++)
	{
	process_status[i]=0;
	}
if(process_status[size-1]==0)
{return 1;}
else 
{return -1;}

}

int main()
{
int n,check,g=0,i,j;
printf("****___PROGRAM STARTS___****\n\n\n");
printf("ENTER THE DESIRED NUMBER OF THREADS  : ");//asking the user to give the number of threads he/she wants.
scanf("%d",&n);
check=allocate_map();//calling function which would initialize the status array.

if(check==1)//checking whether array is initialized or not.
	{
	printf("\n$$$$__ARRAY OF PROCESS STATUS IS INITIALIZED__$$$$\n\n\n");

	pthread_t q[n];//declaring thread 
	for(j=0;j<n;j++)
	{
	if((pthread_create(&q[j],NULL,func,NULL))!=0)//creating threads and checking if thread is assigned a pid or not.
	{
	g++;
	printf("THREAD :%d COULD NOT BE ASSIGNED WITH A PROCESS I.D\n\n",j);
	}
	}
	for(i=0;i<n;i++)
	{
	pthread_join(q[i],NULL);//joining all the created threads.
	}
	printf("Total Number of Threads Desired by the User :%d\n\n",n);
	printf("Number Of Threads Created :%d\n\n",n-g);
	}
else if(check==-1)
printf("@@@___PROCESS STATUS ARRAY COULD NOT BE INITIALIZED___@@@\n\n\n");


printf("@@@@____END OF PROGRAM____@@@@\n");
}

