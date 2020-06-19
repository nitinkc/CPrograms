/*
name:charles curley
class:3270 4PM
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

int global_var[10];
int in=0;
int out=0;
bool full=false;
bool empty=false;
int done=0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Pro = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Con = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread_one(void *idPthread)     //producer
{
	int K;
	int NumItems =0;
	srand(time(NULL));
	NumItems = rand() % 901+100;
	for(K=0;K<NumItems;K++)
	{
		do
		{
			if(in=out)
			{
				full=false;
			}
		}while(full);
		pthread_mutex_lock(&Pro);
		pthread_mutex_lock(&lock);
		global_var[in]=rand() % 1000+1;
		pthread_mutex_unlock(&lock);
		pthread_mutex_unlock(&Pro);
		if(in<9)
		{
			in++;
			if(in=out)
			{
			full=true;
			}
		}
		else
			in=0;
	}
	done++;
	pthread_exit(NULL);
} 

void *thread_two(void *idPthread)    //consumer
{
	int K,temp;
	int min=0;
	int max=0;
	int avg=0;
	int count=0;
	do
	{
		do
		{
			if(out=in)
			{
				empty=false;
			}
		}while(empty);	
		pthread_mutex_lock(&Con);
		pthread_mutex_lock(&lock);
		temp=global_var[out];
		pthread_mutex_unlock(&lock);
		pthread_mutex_unlock(&Con);
		count++;
		avg+=temp;
		if(min>temp)
			min=temp;
		if(max<temp)
			max=temp;
		if(out<9)
		{
			out++;
			if(out=in)
			{
			empty=true;
			}
		}
		else
			out=0;
	
	}while(done!=5);
	avg=(avg/count);
	pthread_mutex_lock(&Con);
	printf("Min:%d", min);
	printf(" \n");
	printf("Max:%d", max);
	printf(" \n");
	printf("Avg:%d", avg);
	printf(" \n");
	printf("Num_Items:%d", count);
	printf(" \n");	
	pthread_mutex_unlock(&Con);
	pthread_exit(NULL);
}
int main()
{

	int k;
	pthread_t tID1;
	pthread_t tID2;
	pthread_create(&tID1, NULL, thread_one,&tID1);
	pthread_create(&tID1, NULL, thread_one,&tID1);
	pthread_create(&tID1, NULL, thread_one,&tID1);
	pthread_create(&tID1, NULL, thread_one,&tID1);
	pthread_create(&tID1, NULL, thread_one,&tID1);
	pthread_create(&tID2, NULL, thread_two,&tID2);
	pthread_create(&tID2, NULL, thread_two,&tID2);
	pthread_create(&tID2, NULL, thread_two,&tID2);

	pthread_join(tID1, NULL);
	pthread_join(tID2, NULL);
	return 0;
}