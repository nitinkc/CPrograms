#include <stdio.h>
#include <stdlib.h>

int oopsDidISmashTheStack(void)
{
	printf("Yup, smashing the stack is fun!\n");
	exit(0);
}

int getUserInput(void)
{
	char buf[12];
	gets(buf);
	return(1);
}

int main(void)
{
	getUserInput();
	printf("Overflow failed, normal return\n");
	return(1);
}