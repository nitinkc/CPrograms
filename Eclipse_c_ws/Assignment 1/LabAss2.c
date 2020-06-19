# include <stdio.h>
# include <pthread.h>
#include <boolean.h>

# define boundedBufferSize 10
# define FALSE 0
# define TRUE 1

void *Producer();
void *Consumer();

int boundedBufferIndex=0;
int in=0;
int out=0;
int empty=TRUE;
int full=TRUE;

int *boundedBuffer[boundedBufferSize];

pthread_cond_t boundedBuffer_Not_Full=PTHREAD_COND_INITIALIZER;
pthread_cond_t boundedBuffer_Not_Empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

void *Producer()
{
    for(;;)
    {
        pthread_mutex_lock(&lock);
        if(boundedBufferIndex==boundedBufferSize)
        {
            pthread_cond_wait(&boundedBuffer_Not_Full,&lock);
        }
        boundedBuffer[boundedBufferIndex++]='@';
        printf("Produce : %d \n",boundedBufferIndex);
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&boundedBuffer_Not_Empty);
    }

}

void *Consumer()
{
    for(;;)
    {
        pthread_mutex_lock(&lock);
        if(boundedBufferIndex==-1)
        {
            pthread_cond_wait(&boundedBuffer_Not_Empty,&lock);
        }
        printf("Consume : %d \n",boundedBufferIndex--);
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&boundedBuffer_Not_Full);
    }
}


int main()
{
    pthread_t ptid,ctid;

    boundedBuffer=(char *) malloc(sizeof(char) * boundedBufferSize);

    pthread_create(&ptid,NULL,Producer,NULL);
    pthread_create(&ctid,NULL,Consumer,NULL);

    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);


    return 0;
}

