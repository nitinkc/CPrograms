/*
 * between_Child_Parent.c
 *
 *  Created on: Sep 24, 2013
 *      Author: nitin
 */

#include<stdio.h>
#include<unistd.h>

#define READ_END 0
#define WRITE_END 1


int main(void)
{
    int pipe1[2],count,i;
    pid_t child1, child2;
    char a[20];

    pipe(pipe1);

    //creating the pipe
       	if(pipe(pipe1) == -1){
       		fprintf(stderr,"Pipe Failed");
       		return 1;
       	}

       	//Forking the First Child
       	child1 = fork();

       	//if error occured
       	if(child1 < 0){
       		fprintf(stderr,"Child1 creation failed");
       		return 1;
       	}

    if(child1==0) //Child1 Process
    {
    	printf("\nChild process\n");
    	read(pipe1[READ_END],a,sizeof(a));
        printf("Message from parent : \"%s\"\n",a);
        printf("Message to parent process : ");
        scanf("%s",a);
        write(pipe1[WRITE_END],a,sizeof(a));
    }
    else //Parent Process
    {
        printf("\nParent Process\n");
        printf("Enter the message to child process : ");
        scanf("%s",a);
        write(pipe1[WRITE_END],a,sizeof(a));
        sleep(1); //let the child read
        read(pipe1[READ_END],a,sizeof(a));
        printf("\nParent Process\n\n");
        printf("Message from child : \"%s\"\n",a);
    }
    return 1;
}