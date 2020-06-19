/*
 * Lab1_TESTING.c
 *
 *  Created on: Sep 21, 2013
 *      Author: nitin
 */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define READ_END 0
#define WRITE_END 1

/***************Declaration, Initialisation, Reading the Command line Arguments and Pipe creation..............................*/
int main(int argc, char *argv[]){
	pid_t  child1, child2,pid; //to be used at the time of comparision and segregation
	int pipe1[2],status;
	int bufChild1[2],bufChild2[2];//to be used to hold pid and random number generated
	int seed1, seed2, numRandom,i,j,k,l;
	/*	Initializing the maxChild1 and minChild2 (in case if only one Random number is generated)*/
	int maxChild1 = 0, minChild1 = 1234, maxChild2=0, minChild2=1234;
	int Array1[2];//to be used to hold the values (pid and random number) at the time of reading by the parent

	//Reading the Command Line Arguments into the Local Variables
	if(argc > 4)
	{
		printf("input only 3 command line arguments\n");
		exit(0);
	}

	//Reading the Command line arguments
	seed1 = atoi(argv[1]);
	seed2 = atoi(argv[2]);
	numRandom = atoi(argv[3]);

	//Creating 1 Pipe 
	if (pipe(pipe1))
	         {
	           fprintf (stderr, "Pipe failed.\n");
	           return EXIT_FAILURE;
	         }

	//******************************child1 created*******************************************
	child1 = fork();
			//if creation failed
			if (child1 < 0) {
			fprintf(stderr, "Fork Failed");
			return 1;
			}

			 // child1 process being created
			else if (child1 == 0) {
				printf("\nInside child 1 with pid %d.The Parent pid is %d\n\n", getppid(), getpid());
				srand(seed1);
				close(pipe1[READ_END]);
				bufChild1[0] = getpid();

				//Work of child1
				for (i=0;i<numRandom;i++)
				{
					bufChild1[1] = rand()%1000;
					//to be used at the time of comparision
					fprintf(stdout, "written value from child 1 is: %d and Pid is %d\n", bufChild1[1],bufChild1[0]);
					write(pipe1[WRITE_END],bufChild1,sizeof(bufChild1)); //write into the Parent
				} 
				
				close(pipe1[WRITE_END]);
				// usleep(1000);
				exit(0);
			}
	
	//*************************************Child2 created************************************************
	child2 = fork();
			//if creation failed
			if (child2 < 0) {
			fprintf(stderr, "Fork Failed");
			return 1;
			}

			// child2 processes being created
			else if (child2 == 0) {
			printf("\nInside child2 with pid %d. The Parent pid is %d\n\n", getpid(), getppid());
			close(pipe1[READ_END]);
			srand(seed2); //returns void
			//Work of child2
			for (j=0;j<numRandom;j++)
				{    
					bufChild2[1] = rand()%1000;
					bufChild2[0] = getpid();
					fprintf(stdout, "written value from child 2 is: %d and Pid is %d\n", bufChild2[1],bufChild2[0]);
					write(pipe1[WRITE_END],bufChild2,sizeof(bufChild2)); //write into the Parent

				}
			
			close(pipe1[WRITE_END]);
			// usleep(1000);
			exit(0);
		}

	  //******************************* Parent Process****************************************************
	  //Wait for children to exit.
	  pid = wait(&status);
	  printf("Parent Process\n");

	  //Reading from Children
	  close(pipe1[WRITE_END]);

	  for (k=0;k<(2*numRandom);k++)
	  {
		 read(pipe1[READ_END],Array1,sizeof(Array1));
	  	 printf("Received the value %d from child with Pid %d \n",Array1[1],Array1[0]);
		 			//Finding Maximum and Minimum in child 1
		 printf("TESTING1");
					if(Array1[0] == child1)
					{
						printf("TESTING2");
	  				  	if (Array1[l] > maxChild1)
	  						{
	  							 maxChild1 = Array1[l];
	  						}
	  						else if (Array1[l] < minChild1)
	  						{
	  							 minChild1 = Array1[l];
	  						}
					}

					//Finding Maximum and Minimum in child 2
					
					else if (Array1[0] == child2)
					{
	  				  	if (Array1[l] > maxChild2)
	  						{
	  							 maxChild2 = Array1[l];
	  						}
	  						else if (Array1[l] < minChild2)
	  						{
	  							 minChild2 = Array1[l];
	  						}
					}
	  }
	  printf ("Parent: Child ID:%d minimum number received is %d, and maximum is %d\n", child1,minChild1,maxChild1);
	  printf ("Parent: Child ID:%d minimum number received is %d, and maximum is %d\n", child2,minChild2,maxChild2);
	  //Finding the overall minimum
	  if(minChild1<minChild2)
			printf ("Parent: The minimum of all numbers received is %d\n",minChild1);
	  else
		  printf("Parent: The minimum of all numbers received is %d\n",minChild2);
	  //Finding the overall maximum
	  if(maxChild1>maxChild2)
		  printf ("Parent: The maximum of all numbers received is %d\n",maxChild1);
	  else
		  printf ("Parent: The maximum of all numbers received is %d\n",minChild2);

	  close(pipe1[READ_END]);
return (1);
}
