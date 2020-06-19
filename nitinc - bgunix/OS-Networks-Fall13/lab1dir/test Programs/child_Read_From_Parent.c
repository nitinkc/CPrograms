/*
 * Galvin1.c
 *
 *  Created on: Sep 23, 2013
 *      Author: nitin
 */

//Child receiving data from Parent
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int var =0;
int main(void){
	int pipe1[2];
	pid_t child1;

	//creating the pipe
	if(pipe(pipe1) == -1){
		fprintf(stderr,"Pipe Failed");
		return 1;
	}

	//fork a child process
	child1 = fork();

	//if error occured
	if(child1 < 0){
		fprintf(stderr,"Child1 creation failed");
		return 1;
	}

	//Parent Process
	if(child1 > 0){
		close(pipe1[READ_END]);
		var = rand()%1000;
		printf("Parent var value is %d with PID as %d\n", var, getpid());
		write(pipe1[WRITE_END],&var,sizeof(var));
		close(pipe1[WRITE_END]);
	}
	//Child Process
	else{
		close(pipe1[WRITE_END]);
		read(pipe1[READ_END],&var, sizeof(var));
		printf("Child %d has read %d from Parent %d\n", getpid(),var, getppid());
	}
return 0;
}
