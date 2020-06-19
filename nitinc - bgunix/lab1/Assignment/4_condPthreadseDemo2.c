#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE  5

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;
int count;
int buffer[MAX_SIZE];


void producer() {
   for(;;) {
	pthreads_mutex_lock(&lock);
	while(count == MAX_SIZE)
		pthread_cond_wait(&notFull, &lock);
	buffer[count] = rand();//get rand function
	printf("buffer[%d] = %d",count,buffer[count]);
	count++;
	pthread_cond_signal(&notEmpty);
	pthread_mutex_unlock(&lock);
   }
}	

void consumer() {
   for(;;) {
	pthread_mutex_lock(&lock);
	while(count == 0)
		pthread_cond_wait(&notEmpty, &lock);
	printf("the value consumed at buffer[%d] is %d",count-1, (buffer[count-1]));
	count--;
	pthread_cond_signal(&notFull);
	pthread_mutex_unlock(&lock);
   }
}

int main() {
   pthread_t p,c;
   count = 0;
   pthread_create(&p, NULL, (void*)producer, NULL);
   pthread_create(&c, NULL, (void*)consumer, NULL);

   pthread_join(p, NULL);
   pthread_join(p, NULL);
   return 0;
}
