#include <stdio.h>
#include <pthread.h>

void printMsg(char* msg) {
	printf("%s\n", msg);
}

int main() {
	pthread_t tID;
	char name[] = "Nitin";
	printf("creating a new thread\n");
	pthread_create(&tID, NULL, (void*)printMsg, name);
	printf("created thread %ld\n", tID);
	pthread_join(tID, NULL);

	return 0;
}
