#include <stdio.h>	
#include <pthread.h>	

#define TCOUNT 10
#define WATCH_COUNT 12	
int count = 0;	

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int  thread_ids[3] = {0,1,2};	

void watch_count(int *idPthread)
{	
     pthread_mutex_lock(&lock);
     while (count <= WATCH_COUNT) {	
              pthread_cond_wait(&cond, &lock);
              printf("watch_count(): Thread %d,Count is %d\n",*idPthread, count);
     }	
     pthread_mutex_unlock(&lock);
}	
void inc_count(int *idPthread)
{	
	int i;
     for (i =0; i < TCOUNT; i++) {	
              pthread_mutex_lock(&lock);
              count++;	
              printf("inc_count(): Thread %d, old count %d,new count %d\n", *idPthread, count - 1, count );
              if (count == WATCH_COUNT)	
                   pthread_cond_signal(&cond);
              pthread_mutex_unlock(&lock);
     }	
}

int	main(void)
{
     int      i;
     pthread_t threads[3];
     pthread_create(&threads[0],NULL,inc_count, &thread_ids[0]);
     pthread_create(&threads[1],NULL,inc_count, &thread_ids[1]);
     pthread_create(&threads[2],NULL,watch_count, &thread_ids[2]);

     for (i = 0; i < 3; i++) {
    	 pthread_join(threads[i], NULL);
     }
     return 0;
}
