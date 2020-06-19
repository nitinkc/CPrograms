#include <stdio.h>
#include "myLib1.h"
#include "myLib2.h"

int main(int argc, char* argv[]){

	double v1,v2,m;
	int x,y, a;

	v1 = 5.2;
	v2 = 7.2;

	m = mean(v1,v2);

	x=5;
	x=6;

	a = add(v1,v2);

	printf("The mean of %3.2f and %3.2f is %3.2f\n", v1, v2, m);
	printf("The addition of %d and %d is %d\n", x, y, a);
	return 0;
}