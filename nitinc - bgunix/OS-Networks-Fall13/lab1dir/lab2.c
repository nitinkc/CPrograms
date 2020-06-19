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

void *producer(void *var);
void *consumer(void *var);


sem_t mutex;
pthread_mutex_t lock; //implementing locking mechanism to prevent ....
//int times = 1;

typedef struct buffer{
	int b[S];
	int cnt;
}boundedBuffer;

typedef struct pcVariables{
	sem_t* empty;
	sem_t* full;
	boundedBuffer* bBuf;
}proCon_var;

/*Buffer Functions*/
void init_boundBuff(boundedBuffer* bBuf){
	int i;
	bBuf->cnt = 0;
	for(i=0;i<S;i++){
		bBuf->b[i] = INITVALUE;
	}
}

void put_boundBuff(int i, boundedBuffer* bBuf){
	 bBuf->b[bBuf->cnt] = i;
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


void *producer(void *args){
	proCon_var* thread_args = args;
	int i;
	srand(345);
	//times = rand()%1000;

	printf("Inside the Producer!\n");

	for(i=1;i<=times;i++){
		sem_wait(thread_args->empty);
		put_boundBuff(i,thread_args->bBuf);
		printf("Producer: produced %d\n", i);
		sem_post(thread_args->full);
		sleep(1);
	}
	return NULL;
}

void *consumer(void *args){
	proCon_var* thread_args = args;
	int i,j,v, tempBuff[times];
	int max = 0, min = 32767, avg=0;
	
	printf("Inside the Consumer!\n");

	for(i=0;i<times;i++){
		sem_wait(thread_args->full);
		v = get_boundBuff(thread_args->bBuf);
		tempBuff[i] = v;
		printf("Consumer: Received %d\n",v);
		sem_post(thread_args->empty);
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
	printf("The minimum of all numbers is %d\n", max);
	printf("The average of all numbers is %d\n", avg);
	printf("The total count is %d\n", times);
	return NULL;
}


int main(int argc, char *argv[]){

	pthread_t producerThread,consumerThread;
	proCon_var thread_args;
	boundedBuffer buffer;
	sem_t empty,full;

	char *message1 = "Producer";
	char *message2 = "Consumer";
	int retProducer, retConsumer;

	if(!sem_init(&empty,0,S)){
		perror("Failed to initialize empty");
	}
	thread_args.empty = &empty;

	if(!sem_init(&full,0,0)){
		perror("Failed to initialize full");
	}
	thread_args.full = &full;

	init_boundBuff(&buffer);
	thread_args.bBuf = &buffer;

	retProducer = pthread_create(&producerThread, NULL, producer, &thread_args);
	retConsumer = pthread_create(&consumerThread, NULL, consumer, &thread_args);

	printf("Just before joining Thread\n");

	pthread_join(producerThread,NULL);
	pthread_join(consumerThread,NULL);

	sem_destroy(&empty);
	sem_destroy(&full);

	return (0);
}

