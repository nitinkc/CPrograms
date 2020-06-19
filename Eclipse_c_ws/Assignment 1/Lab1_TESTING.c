/*
 * Lab1_TESTING.c
 *
 *  Created on: Sep 21, 2013
 *      Author: nitin
 */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define READ_END 0
#define WRITE_END 1


int main(int argc, char *argv[]){
        pid_t child1, child2, pid;
        int pipe1[2],status, sendArray1[2],sendArray2[2];

        int seed1 = atoi(*argv[1]);
        int seed2 = atoi(*argv[2]);
        int numRandom = atoi(*argv[3]);

                //child1 created
        child1 = fork();
                        //if creation failed
                        if (child1 < 0) {
                        fprintf(stderr, "Fork Failed");
                        return 1;
                        }

                         // child1 processes being created
                        else if (child1 == 0) {
                        printf("Inside child1 with pid %d\n", getpid());
                        printf("The Parent pid is %d\n", getppid());
                         //Work of that particular child
                        //for(int
                        sendArray1[0] = rand()%1000;
                        sendArray1[1] = getpid();
                        close(pipe1[READ_END]);
                        write(pipe1[WRITE_END],sendArray1,sizeof(sendArray1)); //write into the Parent
                        fprintf(stdout, "written value from child 1 is: %d %d\n", sendArray1[0],sendArray1[1]);
                        close(pipe1[WRITE_END]);
                        exit(0);
                        }

        //Child2 created
        child2 = fork();
                        //if creation failed
                        if (child2 < 0) {
                        fprintf(stderr, "Fork Failed");
                        return 1;
                        }

                        // child2 processes being created
                        else if (child2 == 0) {
                        printf("\ninside child2 with pid %d", getpid());
                        printf("\nThe Parent pid is %d\n", getppid());
                        //Work of that particular child
                        //for(int
                        sendArray2[0] = rand()%1000;
                        close(pipe1[READ_END]);
                        write(pipe1[WRITE_END],sendArray2,sizeof(sendArray2)); //write into the Parent
                        fprintf(stdout, "written value from child 2 is: %d,\t %d \n", sendArray2[0],sendArray2[1]);
                        close(pipe1[WRITE_END]);
                        exit(0);
                        }

        // Parent Process...Wait for children to exit.
          pid = wait(&status);
          printf("\nParent Process\n");
          //sleep(1); //let the child read
          close(pipe1[WRITE_END]);
          read(pipe1[READ_END],sendArray1,sizeof(sendArray1));
          close(pipe1[READ_END]);
         // printf("\nMessage from child : \"%d,%d\"\n",sendArray2[0],sendArray1[1]);
         // printf("\nMessage from child : \"%d,%d\"\n",sendArray2[1],sendArray2[1]);
          printf("\nChild with PID %ld exited with status 0x%x.\n", (long)pid, status);

return 1;
}



