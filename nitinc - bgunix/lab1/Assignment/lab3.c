/*
 * LabAss2.c
 *
 *  Created on: Oct 13, 2013
 *      Author: nitin
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <errno.h>

#define S 10
#define TERMINATE -1
#define INITVALUE -44
#define times 20

/* THREAD FUNCTIONS */
void *producer(void *var);
void *consumer(void *var);

sem_t mutex;
pthread_mutex_t lock; //implementing locking mechanism to prevent ....
//int times = 1;

//BOUNDED BUFFER AND ITS COUNTER
typedef struct buffer{
	int b[S];
	int cnt;
}boundedBuffer;

//POINTERS TO BOUNDED BUFFERS
typedef struct buffProps{
	sem_t* In;
	sem_t* Out;
	boundedBuffer* bBuf;
}boundBuffProperties;

/*Buffer Functions*/

//INITIALIZATION
void init_boundBuff(boundedBuffer* bBuf){
	int i;
	bBuf->cnt = 0;
	for(i=0;i<S;i++){
		bBuf->b[i] = INITVALUE;
	}
}

void put_boundBuff(int i, boundedBuffer* bBuf){
	 bBuf->b[bBuf->cnt] = i;
	 printf("Producer: put buff %d cnt = %d\n", i, bBuf->cnt);
	 bBuf->cnt++;
	 if(bBuf->cnt == S){
		bBuf->cnt = 0;
	}
}

int get_boundBuff(boundedBuffer* bBuf){
	bBuf->cnt--;
	if(bBuf->cnt == -1){
		bBuf->cnt = S-1;
	}
	return bBuf->b[bBuf->cnt]; //catch the value in the consumer
}

//PRODUCER
void *producer(void *args){
	boundBuffProperties* bBuff_args = args;
	int i,num;
	srand(345);
	//times = rand()%1000;

	printf("Inside the Producer!\n");

	for(i=1;i<=times;i++){
		num = rand();
		sem_wait(bBuff_args->In);
		put_boundBuff(num,bBuff_args->bBuf);
		printf("Producer: produced %d %d\n", i,num);
		sem_post(bBuff_args->Out);
		sleep(1);
	}
	return NULL;
}
//CONSUMER
void *consumer(void *args){
	boundBuffProperties* bBuff_args = args;
	int i,j,v, tempBuff[times];
	int max = 0, min = 99999, avg=0;
	
	printf("Inside the Consumer!\n");

	for(i=0;i<times;i++){
		sem_wait(bBuff_args->Out);
		v = get_boundBuff(bBuff_args->bBuf);
		tempBuff[i] = v;
		printf("Consumer: Received %d\n",v);
		sem_post(bBuff_args->In);
		sleep(1);
	}

	//Finding Max and Min
	for(j=0;j<times;j++){
		avg = avg + tempBuff[j];
		if (tempBuff[j] > max)
	  		{
	  				max = tempBuff[j];
	  		}
	  		else if (tempBuff[j] < min)
	  		{
	  				min = tempBuff[j];
	  		}
		}
	avg = avg/times;
	printf("The maximum of all numbers is %d\n", max);
	printf("The minimum of all numbers is %d\n", min);
	printf("The average of all numbers is %d\n", avg);
	printf("The total count is %d\n", times);
	return NULL;
}

int main(int argc, char *argv[]){

	pthread_t producerThread,consumerThread;
	boundBuffProperties bBuff_args;
	boundedBuffer buffer;
	sem_t In,Out;

	char *message1 = "Producer";
	char *message2 = "Consumer";
	int retProducer, retConsumer;

	if(sem_init(&In,0,S)){
		perror("Failed to initialize In");
	}
	bBuff_args.In = &In;

	if(sem_init(&Out,0,0)){
		perror("Failed to initialize Out");
	}
	bBuff_args.Out = &Out;

	init_boundBuff(&buffer);
	bBuff_args.bBuf = &buffer;

	/*Thread Creation, and passing Producer and Consumer arguments*/

	//PRODUCER THREAD
	retProducer = pthread_create(&producerThread, NULL, producer, &bBuff_args);
	//CONSUMER THREAD
	retConsumer = pthread_create(&consumerThread, NULL, consumer, &bBuff_args);

	printf("Just before joining Thread\n");

	//WAIT FOR THE THREADS TO TERMINATE
	pthread_join(producerThread,NULL);
	pthread_join(consumerThread,NULL);

	sem_destroy(&In);
	sem_destroy(&Out);

	return (0);
}

