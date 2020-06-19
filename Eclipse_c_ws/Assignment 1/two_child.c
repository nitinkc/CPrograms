/*
 * two_child.c
 *
 *  Created on: Sep 23, 2013
 *      Author: nitin
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	pid_t child1,child2;

	child1 = fork();

	//if error occured
		if(child1 < 0){
			fprintf(stderr,"Child1 creation failed");
			return 1;
		}

		else if(child1 == 0){ //child process
			child2 = getpid();
			printf("child: child1 = %d\n", child1);
			printf("child: child2 = %d\n", child2);
		}

		else{ //parent process
			child2=getpid();
			printf("parent: child1 = %d\n", child1);
			printf("parent: child2 = %d\n", child2);
			wait(NULL);
		}
return 0;
}


