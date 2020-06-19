#include <stdio.h>
#include <pthread.h>

//int *status = (int*)malloc(sizeof(int)); //GLOBAL
int status;
void printMsg(char* msg) {
	printf("%s\n", msg);
	pthread_exit(&status); //CHANGE (explicit exit)
}

int main() {
	pthread_t tID;
	char name[] = "Nitin";

	pthread_create(&tID, NULL, (void*)printMsg, name);
	printf("created thread id(tID) %ld\n", tID);
	pthread_join(tID, status); //CHANGE (previous prog, status is NULL)

	return 0;
}
