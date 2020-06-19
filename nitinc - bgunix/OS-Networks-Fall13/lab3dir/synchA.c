#include <stdio.h>
#include <pthread.h>

#define S 10
#define TERMINATE -1
#define INITVALUE -2
#define SEED 478

/* GLOBAL VARIABLES*/
    /* Thread Variables */
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t Empty = PTHREAD_COND_INITIALIZER;
	pthread_cond_t Full = PTHREAD_COND_INITIALIZER;

	int count;
    /* Circular Buffer Declared */
	int in = 0;
	int out = 0; //Buffer Pointers
	int circBuffer[S];
	int producedItems;

	/* Subroutine Declaration */
	void insertCircBuffer(int);
	void seeCircBuffer(void);
	int removeCircBuffer(void);
	void *producer(void);
	void *consumer(void);
	void initCircBuffer();

int main(int argc, char *argv[]){

    pthread_t producerThread,consumerThread;
    int producerID, consumerID;

    /*Initializing the Circular Buffer*/
    initCircBuffer();

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

void initCircBuffer(){
	int i = 0;
	for (i=0;i<S;i++){
		circBuffer[i] = INITVALUE;
	}
	printf("Circular Buffer initialised\n");
	seeCircBuffer();
}

void seeCircBuffer(){
		int iterator;
		for (iterator = 0;iterator < S ;iterator ++){
			printf("B[%d]=%d ",iterator,circBuffer[iterator]);
		}
		printf("\n"); //just to change line
		}

void insertCircBuffer(int val){
	if(in == S){ //The last wasted Space
		in = 0;
	}
	circBuffer[in] = val;
	in ++;
}

int removeCircBuffer(void){
	int sendVal;
	if(out == S){ //The last wasted Space
			out = 0;
			initCircBuffer();
		}
		sendVal = circBuffer[out];
		out ++;
}
/* THREAD FUNCTIONS */

/*PRODUCER Function */
void *producer(void){

    int items,num,loop;
    srand(SEED);
    items = rand()%100;
    producedItems = items; //to tell consumer of total numbers of items produced

           for(loop = 0;loop < items;loop++) {
        	/*LOCKING THE CRITICAL SECTION*/
        	pthread_mutex_lock(&lock);
        	printf("Inside the Producer!\n");
        	if(in + 1 == out){
        		pthread_cond_wait(&Empty, &lock);//Conditional wait for the EMPTY SIGNAL
        	}
        	num = rand()%1000;
        	printf("The value PRODUCED = %d\n",num);
        	insertCircBuffer(num); //circBuffer[count] = ;//get rand value
        	seeCircBuffer();
        	/*UNLOCKING THE CRITICAL SECTION and then send signal,
        	 * so that critical section can be modified*/
        	pthread_mutex_unlock(&lock);
        	pthread_cond_signal(&Full);//Signal to the Consumer, saying that Buffer is FULL
           }
    return NULL;
}
/* CONSUMER Function */
void *consumer(void){

    int i,j,v, loop;
    int max = 0, min = 99999, avg=0;
    	for(loop = 0;loop < producedItems;loop++) {
    	pthread_mutex_lock(&lock);
    	printf("Inside the Consumer!\n");
    	if(out == in) //Not picking up from where IN is currently located (Assuming if in is pointing, it is not full)
    		pthread_cond_wait(&Full, &lock);
    	printf("the value CONSUMED at circBuffer[%d] = %d \n",out, circBuffer[out]);
    	removeCircBuffer(); //circBuffer[count] = ;//get rand value
    	seeCircBuffer();
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
