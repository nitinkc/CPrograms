#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#define S 10
#define TERMINATE -1
#define INITVALUE -2
#define LOOP 10

/* GLOBAL VARIABLES*/
    /* Thread Variables */
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t Empty = PTHREAD_COND_INITIALIZER;
	pthread_cond_t Full = PTHREAD_COND_INITIALIZER;

    /* For Circular Buffer
     int *in,*out;
	int circBuffer[S];
	*/

	/* Testing LINEAR BUFFER, to implement synchrinisation */
	int count=0;
	int TEMPbuffer[S]; //Linear Buffer to avoid complexity

	void seeBuffer(){
		int iterator = 0;
		for (iterator = 0;iterator < S ;iterator ++){
			printf("B[%d] = %d  ",iterator,TEMPbuffer[iterator]);
		}
		printf("\n"); //just to change line
		}

/* THREAD FUNCTIONS */

//PRODUCER
void *producer(void){

    int loop,num;
    srand(rand());
           for(loop = 0;loop < LOOP;loop++) {
        	/*LOCKING THE CRITICAL SECTION*/
        	pthread_mutex_lock(&lock);
        	printf("Inside the Producer!\n");
        	while(count == S){
        		pthread_cond_wait(&Empty, &lock);//Conditional wait for the EMPTY SIGNAL
        	}
        	TEMPbuffer[count] = rand()%1000;//get rand value
        	printf("The value PRODUCED at TEMPbuffer[%d] = %d\n",count,TEMPbuffer[count]);
        	seeBuffer();
        	count++;
        	pthread_mutex_unlock(&lock); /*UNLOCKING THE CRITICAL SECTION*/
        	pthread_cond_signal(&Full);//Signal to the Consumer, saying that Buffer is FULL
           }
    return NULL;
}
//CONSUMER
void *consumer(void){

    int i,j,v, loop;
    int max = 0, min = 99999, avg=0;
    	for(loop = 0;loop < LOOP;loop++) {
    	pthread_mutex_lock(&lock);
    	printf("Inside the Consumer!\n");
    	while(count == 0)
    		pthread_cond_wait(&Full, &lock);
    	printf("the value CONSUMED at TEMPbuffer[%d] = %d\n",count-1, TEMPbuffer[count-1]);
    	seeBuffer();
    	count--;
    	pthread_mutex_unlock(&lock);
    	pthread_cond_signal(&Empty);
       }

    /*Finding MAX, MIN, AVG and COUNT
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
    return NULL; */
}

int main(int argc, char *argv[]){

    pthread_t producerThread,consumerThread;
    int producerID, consumerID;

//Routine for Bounded Buffer

    /*Thread Creation, and passing Producer and Consumer arguments*/

    //PRODUCER THREAD
    producerID = pthread_create(&producerThread, NULL, producer, NULL);
    //CONSUMER THREAD
    consumerID = pthread_create(&consumerThread, NULL, consumer, NULL);

    printf("Just before joining Thread\n");

    //WAIT FOR THE THREADS TO TERMINATE
    pthread_join(producerThread,NULL);
    pthread_join(consumerThread,NULL);

    /* Cleanup the mutex */
    pthread_mutex_destroy(&lock);
    return (0);
}
