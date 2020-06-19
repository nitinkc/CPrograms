#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	/* Variables */
	int sock;
	struct sockaddr_in server;
	int mysock;
	char buff[999];
	int rval;


	/* Create Socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);  //TCP IP Socket family
	if(sock < 0){
		perror("Socket creation failed");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5000);

	/* Call Bind */
	if(bind(sock, (struct sockaddr *)&server, sizeof(server))){
		perror("Bind Failure");
		exit(1);
	}

	/* Listen */
	listen(sock,5); //upto 5 connection

	/* Accept */
	do{
		mysock = accept(sock, (struct sockaddr *) 0,0);
		if(mysock == -1){
			perror("accept failed");
		}
		else{
			memset(buff, 0, sizeof(buff));
			if((rval = recv(mysock, buff, sizeof(buff), 0)) < 0)
				perror("reading stream message error");
			else if (rval == 0)
				printf("Ending connection\n");
			else
				printf("MSG: %s\n", buff);
				
		 printf("Got the message (rval = %d)\n", rval);
		}
} while(1);

return 0;
}
