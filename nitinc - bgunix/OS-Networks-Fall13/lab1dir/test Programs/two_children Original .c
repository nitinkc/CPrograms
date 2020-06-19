/*
 * two_children.c
 *
 *  Created on: Sep 24, 2013
 *      Author: nitin
 */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define READ_END 0
#define WRITE_END 1


int main(void){
	pid_t child[2], pid;
	int pipe1[2],i,status, val;
	int n = 2;

	/* Start children. */
	for (i = 0; i < n; ++i) {
	  if ((child[i] = fork()) < 0) {
	    perror("fork");
	    abort();
	  }

	  //2 child processes being created
	  else if (child[i] == 0) {
	    printf("\ninside child %d with pid %d", i, getpid());
	    printf("\nThe Parent pid is %d\n", getppid());
		  //Work of that particular child
	    val = rand()%1000;
	    write(pipe1[WRITE_END],&val,sizeof(val)); //write into the Parent
	    exit(0);
	  }
	}

	/* Wait for children to exit. */

	while (n > 0) {
	  pid = wait(&status);
	  printf("\nParent Process\n");
	  sleep(1); //let the child read
	  read(pipe1[READ_END],&val,sizeof(val));
	  printf("\nParent Process\n");
	  printf("\nMessage from child : \"%d\"\n",val);
	  printf("\nChild with PID %ld exited with status 0x%x.\n", (long)pid, status);
	  --n;  //
	}
	return 1;
}



