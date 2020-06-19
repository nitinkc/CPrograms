/*
 * NitinServer.c
 *
 *  Created on: Aug 12, 2013
 *      Author: nitin
 */
//SERVER Socket-->Bind-->Listen-->accept-->send/recv-->shutdown-->close
//CLIENT Socket-->connect-->send/recv-->shutdown-->close

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int a, char *v[])
{
	char sendBuff[22] //nitin kumar chaurasia 21 char + null char
	struct sockaddr_in serverAddress;
	//struct sockaddr* SAddCasting = (sockaddr *)serverAddress; //tried for typecasting
	int listenFd = socket(AF_INET,SOCK_STREAM,0);

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(5000);  //port number
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  //IP Address

	bind(listenFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); //Type casting happening in the middle parameter

	listen (listenFd,5); //5 pending connection requests allowed

	for(;;) //infinite loop for waiting
		{
		int connectFd = accept(listenFd, (struct sockaddr*)NULL, NULL) // Accepts Returns the socketId and address of client connecting to socket.
		read(connectFd, sendBuff, sizeof(sendBuff));
		close(connected);
		sleep(1);
		}
	return(4);
}

