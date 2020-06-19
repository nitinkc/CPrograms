/******************************************************************************
* DESCRIPTION:
*   Demonstration of shared memory.
* AUTHOR: Nitin K Chaurasia
* Date: Nov 17, 20130
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TOTAL_NUMBER_THREADS 5
int shared_global_var = 0;
/*DEMO FOR MULTITHREAD */
void *demoMultithread(void *threadid)
{
   long tid;
   tid = (long)threadid;//pointer to long type casting
   printf("MESSAGE FROM THE THREAD : Thread #%ld!\n", tid);
   //++shared_global_var;//THIS MAKES SURE ALL THE VALUES ARE PRINTING
   printf("THE VAL OF SHARED VAR from Thread Thread #%ld! is: %i\n", tid, shared_global_var);
   pthread_exit(NULL);
}

// threads are trying to print on Output, who ever gets the chance to print is printing
int main(int argc, char *argv[])
{
	/* VARIABLES*/
   pthread_t threads[TOTAL_NUMBER_THREADS]; //An array to keep the threads
   int pThread_return;
   long t;


   /* CREATING MULTIPLE THREADS OF SAME TYPE USING A LOOP */
   for(t=0;t<TOTAL_NUMBER_THREADS;t++){
     printf("In main: creating thread %ld\n", t);
     //Increment the Global variable before thread creation, to test the synchronisation problem
     ++shared_global_var;
     //Actual Thread Creation
     pThread_return = pthread_create(&threads[t],NULL,demoMultithread, (void *)t);
     if (pThread_return){
       printf("ERROR; return code from pthread_create() is %d\n", pThread_return);
       exit(-1);
       }
     }

   /* KILL THE THREADS IN THE END */
   pthread_exit(NULL);
}
