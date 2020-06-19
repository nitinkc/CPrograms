#include <unistd.h>     
#include <sys/types.h> 
#include <errno.h>     
#include <stdio.h>     
#include <sys/wait.h>   
#include <stdlib.h>     
 
int main()
{
    pid_t pidA; 
    int randVal;    
    int status;    

pidA= fork();
    
    if (pidA >= 0) /* fork succeeded */
    {
        if (pidA == 0) /* fork() returns 0 to the child process */
        {
            printf("CHILD process!\n");
            printf("CHILD PID: %d\n", getpid());
            printf("CHILD parent's PID is: %d\n", getppid());
            printf("CHILD copy of pidA is: %d\n", pidA);
            printf("CHILD Sleeping for 1 second...\n");
            sleep(1); /* sleep for 1 second */
            randVal = rand()%1000;
	     printf("CHILD Process Random Value: %drandVal ");
            printf("CHILD: Goodbye!\n");    
            exit(randVal); /* child exits with user-provided return code */
        }
        else /* fork() returns new pid to the parent process */
        {
            printf("Parent process!\n");
            printf("Parent's PID: %d\n", getpid());
            printf("Praent's copy of pidA is %d\n", pidA);
            printf("PARENT waiting for the child to exit.\n");
            wait(&status); /* wait for child to exit, and store its status */
            printf("PARENT: Child's exit code is: %d\n", WEXITSTATUS(status));
            printf("PARENT: Goodbye!\n");             
            exit(0);  /* parent exits */       
        }
    }
    
	else
    {
        perror("fork"); 
        exit(0); 
    }
}
