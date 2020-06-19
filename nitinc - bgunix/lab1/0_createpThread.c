#include <stdio.h>
#include <pthread.h>

//Function to be executed by the thread
void printMsg(char* msg) {
	printf("%s\n", msg);
}

int main() {
	pthread_t tID;
	char name[] = "Nitin";//parameter to the function
        //Thread with default attributes(NULL), 
        //and function with its parameter (name)

	pthread_create(&tID, NULL, (void*)printMsg, name);
	printf("created thread id is (tID) %ld\n", tID);
	pthread_join(tID, NULL);

	return 0;
}
