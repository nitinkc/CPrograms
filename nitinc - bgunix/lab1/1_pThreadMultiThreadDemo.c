/******************************************************************************
* DESCRIPTION:
*   Demonstration of multithreading, thread creation and
*   termination.
*   THREAD CREATION IS INDEPENDENT OF THREAD EXECUTION
* AUTHOR: Nitin K Chaurasia
* Date: Feb 04, 2015
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_NUMBER_THREADS 10

/*DEMO: THREAD CREATION IS INDEPENDENT OF THREAD EXECUTION */
void *demoMultithread(void *threadid)
{
   long tid;
   tid = (long)threadid;//pointer to long type casting
   printf("MESSAGE FROM THE THREAD : Thread #%ld!\n", tid);
   pthread_exit(NULL);
}

void main()
{
	/* VARIABLES*/
   pthread_t threads[TOTAL_NUMBER_THREADS]; //An array to keep the threads
   int pThread_return;
   long t;

   /* CREATING MULTIPLE THREADS OF SAME TYPE USING A LOOP */
   for(t=0;t<TOTAL_NUMBER_THREADS;t++){
     printf("In main: creating thread %ld\n", t);
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
