#include <STDIO.H>

int main(){
	char buffer[8];
	//sprintf(buffer, "NITIN KUMAR CHAURASIA");
	printf("%s\n",buffer);
	//sprintf(buffer, "PRASHANT");
	printf("%s\n", buffer);
	snprintf(buffer, sizeof(buffer),"dflsbfsbv,bsvsbfdsbfldbf");
	printf("%s\n", buffer);
}
