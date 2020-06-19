#include <stdio.h>	
#include <pthread.h>	

#define TCOUNT 10
#define CONDITION_MET 12
int count = 0;	

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int  thread_ids[3] = {0,1,2};	

void B(int *idPthread)
{	
     pthread_mutex_lock(&lock);
     while (count <= CONDITION_MET) {
              pthread_cond_wait(&cond, &lock);
              printf("B(): Thread %d,Count is %d\n",*idPthread, count);
     }	
     pthread_mutex_unlock(&lock);
}	
void A(int *idPthread)
{	
	int i;
     for (i =0; i < TCOUNT; i++) {	
              pthread_mutex_lock(&lock);
              count++;	
              printf("A(): Thread %d, old count %d,new count %d\n", *idPthread, count - 1, count );
              if (count == CONDITION_MET)
                   pthread_cond_signal(&cond);
              pthread_mutex_unlock(&lock);
     }	
}

int	main(void)
{
     int      i;
     pthread_t threads[3];
     pthread_create(&threads[0],NULL,A, &thread_ids[0]);
     pthread_create(&threads[1],NULL,A, &thread_ids[1]);
     pthread_create(&threads[2],NULL,B, &thread_ids[2]);

     for (i = 0; i < 3; i++) {
    	 pthread_join(threads[i], NULL);
     }
     /* Cleanup the mutex */
         pthread_mutex_destroy(&lock);
     return 0;
}
