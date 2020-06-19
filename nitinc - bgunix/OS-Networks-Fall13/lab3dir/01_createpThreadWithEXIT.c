#include <stdio.h>
#include <pthread.h>

//int *status = (int*)malloc(sizeof(int)); //GLOBAL
int status;
void printMsg(char* msg) {
	printf("%s\n", msg);
	pthread_exit(&status); //CHANGE
}

int main() {
	pthread_t tID;
	char name[] = "Nitin";

	printf("creating a new thread\n");
	pthread_create(&tID, NULL, (void*)printMsg, name);
	printf("created thread %ld\n", tID);
	pthread_join(tID, &status); //CHANGE

	return 0;
}
