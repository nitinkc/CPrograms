#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1

int main(void)
{
   int status;
   int pipe1[2];
   int t1, t2, t3;
   pid_t child1,child2;

   printf("Before forking\n");
   printf("PARENT process pid is : %d\n",getpid());

   //creating the pipe
   	if(pipe(pipe1) == -1){
   		fprintf(stderr,"Pipe Failed");
   		return 1;
   	}

   //forking the first child
   	child1 = fork( );

   //if error occured
   	if(child1 < 0){
   		fprintf(stderr,"Child1 creation failed");
   		return 1;
   	}

   if (child1 == 0)//successful child1 creation
   {
	   printf("\n child just after forking1\n");
	   printf("Child1 process id is :%d\n",getpid());
	   printf("parent's pid is :%d\n",getppid());
	   t1 = rand()%1000;
       printf("The answer for t1 is: %d\n", t1);
   	   close(pipe1[READ_END]);
   	   write(pipe1[WRITE_END],&t1, sizeof(var));
   	   close(pipe1[WRITE_END]);
   	   exit(0);
   }
   else //if control goes to the Parent..Let them wait
   {
    wait(&status);
        printf("\nInside parent after forking1\n");
        printf("Parent process and pid is: %d\n",getpid());
   }

   //forking the second child
   child2 = fork( );

   //if error occured
   	if(child2 < 0){
   		fprintf(stderr,"Child1 creation failed");
   		return 1;
   	}

   if (child2 == 0) //successful child 2 creation
   {
	   printf("\nThis is child2 after forking2\n");
	   printf("Child2 process id is :%d\n",getpid());
	   printf("parent's pid is :%d\n",getppid());
	   t2 = rand()%1000;
	   printf("The answer for t2 is: %d\n", t2);
	   close(pipe1[READ_END]);
	   write(pipe1[WRITE_END],&var, sizeof(var));
	   close(pipe1[WRITE_END]);
	   //exit(0);
   }
   else //if control goes to the Parent....Let them wait
   {
    wait(&status);
        printf("\nInside Parent after forking2\n");
        printf("Parent process and pid is: %d\n",getpid());
   }

   printf("\n\nThe final answer for t1 is: %d\n", t1);
   printf("The final answer for t2 is: %d\n", t2);
}
