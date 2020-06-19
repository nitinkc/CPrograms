#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
int n;
char integer[4];                  // buffer
int val;
   char str[20];
   
strcpy(integer, "7323");
		n = atoi(integer);
		printf("Received ACK = %d\n", n);	
   
   strcpy(str, "98993489");
   val = atoi(str);
   printf("String value = %s, Int value = %d\n", str, val);

   strcpy(str, "tutorialspoint.com");
   val = atoi(str);
   printf("String value = %s, Int value = %d\n", str, val);

   return(0);
	}